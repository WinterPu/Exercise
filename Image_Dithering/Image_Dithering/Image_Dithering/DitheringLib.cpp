#include "DitheringLib.h"

int order[4][2] = { { 0,0 },{ 1,1 },{ 0,1},{ 1,0} };

#if MODIFY_FLAG
//-- modified-1
//int order_matrix[4][4] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
//-- modified-2
int order_matrix[4][4] = { 15,7,6,11,2,4,13,9,0,12,1,5,8,3,10,14};
#else 
int order_matrix[4][4] = { 0,8,2,10,12,4,14,6,3,11,1,9,15,7,13,5 };
#endif

cv::Mat GenerateGrayLevelImage(cv::Mat original_image) {

	cv::Mat gray_level_image(original_image.rows,original_image.cols,CV_8UC1);
	for (int i = 0; i < original_image.rows; i++)
		for (int j = 0; j < original_image.cols; j++)
			gray_level_image.at<uchar>(i, j) = (original_image.at<cv::Vec3b>(i, j)[0] + original_image.at<cv::Vec3b>(i, j)[1] + original_image.at<cv::Vec3b>(i, j)[2]) / 3.0;
		return gray_level_image;
}


cv::Mat GenerateDitheredImage_A1(cv::Mat gray_level_image) {

	cv::Mat dithered_image(gray_level_image.rows*2, gray_level_image.cols*2, CV_8U);

	for (int i = 0; i < dithered_image.rows; i++)
	{
		for (int j = 0; j < dithered_image.cols; j++)
			dithered_image.at<uchar>(i, j) = 0;
	}


	for (int i = 0; i < gray_level_image.rows; i++)
	{
		for (int j = 0; j < gray_level_image.cols; j++)
		{

			int gray_value = gray_level_image.at<uchar>(i, j);
			int order_value = -1;
			if (FIRST_LEVEL <= gray_value && gray_value < SECOND_LEVEL)
				order_value = 0;
			else if (gray_value >= SECOND_LEVEL && gray_value < THIRD_LEVEL)
				order_value = 1;
			else if (gray_value >= THIRD_LEVEL && gray_value < FORTH_LEVEL)
				order_value = 2;
			else if (gray_value >= FORTH_LEVEL)
				order_value = 3;

			for (; order_value >= 0; order_value--)
				dithered_image.at<uchar>(2 * i + order[order_value][0], 2 * j + order[order_value][1]) = 255;
		}

	}
	


	return dithered_image;
}


cv::Mat GenerateDitheredImage_A2(cv::Mat gray_level_image) {

	cv::Mat dithered_image(gray_level_image.rows, gray_level_image.cols, CV_8U);
	for (int i = 0; i < gray_level_image.rows; i++)
	{
		for (int j = 0; j < gray_level_image.cols; j++)
		{
			int x = i % N;
			int y = j % N;

			if (gray_level_image.at<uchar>(i, j) / 16.0 >= (float)order_matrix[x][y])
				dithered_image.at<uchar>(i, j) = 255;
			else 
				dithered_image.at<uchar>(i, j) = 0;
		}
	}

	return  dithered_image;
}