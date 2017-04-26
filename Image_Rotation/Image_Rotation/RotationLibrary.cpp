#include "RotationLibrary.h"


#pragma region  function preparation

bool IsInTheBoundary(int i, int j) {
	if (i < 0 || i >= IMAGE_HEIGHT || j < 0 || j >= IMAGE_WIDTH)
		return false;
	else
		return true;
}

void HandleExceedBoundaryPosition(int &i, int &j)
{
	i = std::max(0, i);
	i = std::min(i,IMAGE_HEIGHT-1);

	j = std::max(0,j);
	j = std::min(j,IMAGE_WIDTH-1);
}


//from destination to source (destination => center_vector => rotation)
cv::Mat GetOriginalMappingPosition(int x, int y, cv::Mat rotated_matrix, cv::Mat center_vector = (cv::Mat_<MathType>(2, 1) << 0, 0))
{
	cv::Mat vector = (cv::Mat_<MathType>(2, 1) << x - center_vector.at<MathType>(0, 0), y - center_vector.at<MathType>(1, 0));
	cv::Mat rotated_position = (cv::Mat_<MathType>(2, 1) << 0, 0);
	rotated_position = rotated_matrix * vector;
	return rotated_position;
}

#pragma endregion


cv::Mat	RotateImage(cv::Mat original, MathType angle, FuncType type) {

	angle = -angle / 180.0 * PI;

	cv::Mat rotated_image(IMAGE_HEIGHT, IMAGE_WIDTH ,IMAGE_TYPE);

	cv::Mat rotated_matrix = (cv::Mat_<MathType>(2, 2) << cos(angle), -sin(angle), sin(angle), cos(angle));

	cv::Mat original_center = (cv::Mat_<MathType>(2, 1) << IMAGE_HEIGHT / 2,  IMAGE_WIDTH / 2);
	original_center = rotated_matrix * original_center;
	cv::Mat center_vector = (cv::Mat_<MathType>(2, 1) << (IMAGE_HEIGHT / 2 - original_center.at<MathType>(0, 0)), (IMAGE_WIDTH / 2 - original_center.at<MathType>(1, 0)));

	rotated_matrix = (cv::Mat_<MathType>(2, 2) << cos(angle), sin(angle), -sin(angle), cos(angle));

	for (int i = 0; i < rotated_image.rows; i++)
	{
		for (int j = 0; j < rotated_image.cols; j++)
		{
			cv::Mat mapping_position = GetOriginalMappingPosition(i, j, rotated_matrix, center_vector);
			
			if (type == Nearst)
			{
				rotated_image.at<cv::Vec3b>(i, j) = GetColorNearst(original,mapping_position);
			}
			else if (type == Bilinear)
			{
				rotated_image.at<cv::Vec3b>(i, j) = GetColorBilinear(original, mapping_position);
			}
			else if (type == Bicubic)
			{
				rotated_image.at<cv::Vec3b>(i, j) =  GetColorBicubic(original, mapping_position);
			}
		}
	}
	return rotated_image;
}


cv::Vec3b GetColorNearst(cv::Mat original_image, cv::Mat mapping_position)
{
	int mapping_i = mapping_position.at<MathType>(0, 0);
	int mapping_j = mapping_position.at<MathType>(1, 0);

	if (!IsInTheBoundary(mapping_i,mapping_j))
		return color_black.at<cv::Vec3b>(0, 0);
	else
		return original_image.at<cv::Vec3b>(mapping_i, mapping_j);

}

/*
	
y2	11  (R1)  12

y1	21  (R2)  22

	x1		  x2
*/
cv::Vec3b GetColorBilinear(cv::Mat original_image, cv::Mat mapping_position)
{
	MathType i = mapping_position.at<MathType>(0, 0);
	MathType j = mapping_position.at<MathType>(1, 0);

	if (!IsInTheBoundary(i, j))
		return color_black.at<cv::Vec3b>(0, 0);

	int x1 = (int)floor(i);	
	int x2 = (int)ceil(i);
	int y1 = (int)floor(j);
	int y2 = (int)ceil(j);
	HandleExceedBoundaryPosition(x1,y1);
	HandleExceedBoundaryPosition(x2,y2);

	cv::Mat color(1, 1, CV_8UC3);
	for (int k = 0; k < 3; k++)
	{
		MathType R1 = GetLinearInterpolationValue(x1,x2, i, original_image.at<cv::Vec3b>(x1, y1)[k], original_image.at<cv::Vec3b>(x2, y1)[k]);
		MathType R2 = GetLinearInterpolationValue(x1,x2,i,original_image.at<cv::Vec3b>(x1,y2)[k], original_image.at<cv::Vec3b>(x2, y2)[k]);
	
		int color_channel_value = (int)(GetLinearInterpolationValue(y1,y2,j,R1,R2));

		color_channel_value = std::max(0, color_channel_value);
		color_channel_value = std::min(color_channel_value, 255);
		color.at<cv::Vec3b>(0, 0)[k] = color_channel_value;
	}
	return color.at<cv::Vec3b>(0, 0);
}

cv::Vec3b GetColorBicubic(cv::Mat original_image, cv::Mat mapping_position)
{
	MathType i = mapping_position.at<MathType>(0, 0);
	MathType j = mapping_position.at<MathType>(1, 0);
	
	if (!IsInTheBoundary(i, j))
		return color_black.at<cv::Vec3b>(0,0);
	
	MathType u = i - MathType((int)i);
	MathType v = j - MathType((int)j);

	cv::Mat A = (cv::Mat_<MathType>(1, 4) << S(u + 1), S(u + 0), S(u - 1), S(u - 2));	
	cv::Mat C = (cv::Mat_<MathType>(4, 1) << S(v + 1), S(v + 0), S(v - 1), S(v - 2));

	cv::Mat color(1,1, IMAGE_TYPE);
	for (int k = 0; k < 3; k++)
	{

		cv::Mat B = (cv::Mat_<MathType>(4, 4) << 
			F(i-1, j - 1, original_image)[k], F(i-1, j, original_image)[k], F(i-1, j+1, original_image)[k], F(i-1, j+2, original_image)[k],
			F(i, j - 1, original_image)[k], F(i, j, original_image)[k], F(i, j + 1, original_image)[k], F(i, j + 2, original_image)[k],
			F(i+1, j - 1, original_image)[k], F(i+1, j, original_image)[k], F(i+1, j + 1, original_image)[k], F(i+1, j + 2, original_image)[k],
			F(i+2, j - 1, original_image)[k], F(i+2, j, original_image)[k], F(i+2, j + 1, original_image)[k], F(i+2, j + 2, original_image)[k]);

		cv::Mat tmp = A*B*C;
		int color_channel_value = (int)(tmp.at<MathType>(0,0));

		color_channel_value = std::max(0, color_channel_value);
		color_channel_value = std::min(color_channel_value, 255);
		color.at<cv::Vec3b>(0, 0)[k] = color_channel_value;
	}
	return color.at<cv::Vec3b>(0, 0);
}

#pragma region ForBilinearInterpolation

MathType GetLinearInterpolationValue(MathType x1, MathType x2, MathType x, MathType q1, MathType q2)
{
	if (x1 == x2)
		return q1;

	return ((x2 - x) / (x2 - x1) *q1 + (x - x1) / (x2 - x1)*q2);
}
#pragma endregion

#pragma region ForBicubicInterpolation


//get the color at(i, j)
cv::Vec3b F(int i, int j, cv::Mat original_image)
{
	HandleExceedBoundaryPosition(i, j);
	return original_image.at<cv::Vec3b>(i, j);
}


MathType S(MathType x)
{
	MathType tmp = fabs(x);
	if (tmp >= 0 && tmp < 1)
		return 1 - 2 * tmp * tmp + tmp * tmp *tmp;
	else if (tmp >= 1 && tmp < 2)
		return 4 - 8 * tmp + 5 * tmp * tmp - tmp * tmp *tmp;
	else
		return 0;
}

#pragma endregion
