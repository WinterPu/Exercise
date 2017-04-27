#include <iostream>
#include <string>
#include <ctime>
#include "RotationLibrary.h"

int main() {

	std::string image_name = "S.jpg";
	std::string path_name = "C:/Users/Winter Pu/Desktop/Image Processing/";
	cv::Mat original_image;
	original_image = cv::imread(path_name + image_name, CV_LOAD_IMAGE_COLOR);
	
	if (!original_image.data)
	{
		std::cout << "Image Open Error! Please Check The Image Path!" << std::endl;
		return -1;
	}
	else {
		original_boundary_height = original_image.rows;
		original_boundary_width = original_image.cols;
	}

	cv::Mat rotated_image_nearst;
	cv::Mat rotated_image_bilinear;
	cv::Mat rotated_image_bicubic;

	rotated_image_nearst = RotateImage(original_image, 30, Nearst);
	rotated_image_bilinear = RotateImage(original_image, 30, Bilinear);
	rotated_image_bicubic = RotateImage(original_image, 30, Bicubic);
	
#pragma region Time Comparasion

	//clock_t start_time01 = clock();
	//rotated_image_nearst = RotateImage(original_image,30,Nearst);
	//clock_t end_time01 = clock();
	//
	//clock_t start_time02 = clock();
	//rotated_image_bilinear = RotateImage(original_image, 30, Bilinear);
	//clock_t end_time02 = clock();

	//clock_t start_time03 = clock();
	//rotated_image_bicubic = RotateImage(original_image, 30, Bicubic);
	//clock_t end_time03 = clock();

	//std::cout <<"Nearst Time:"<< static_cast<double>(end_time01 - start_time01) / CLOCKS_PER_SEC * 1000 << std::endl;
	//std::cout <<"Bilinear Time:"<< static_cast<double>(end_time02 - start_time02) / CLOCKS_PER_SEC * 1000 << std::endl;
	//std::cout <<"Bicubic Time"<< static_cast<double>(end_time03 - start_time03) / CLOCKS_PER_SEC * 1000 << std::endl;

#pragma endregion	

	cv::imwrite(path_name+"nearst_"+image_name, rotated_image_nearst);
	cv::imwrite(path_name + "bilinear_" + image_name, rotated_image_bilinear);
	cv::imwrite(path_name + "bicubic_" + image_name, rotated_image_bicubic);

	cv::imshow("Nearst", rotated_image_nearst);
	cv::imshow("Bilinear", rotated_image_bilinear);
	cv::imshow("Bicubic", rotated_image_bicubic);

	//follow imshow to give time to show an image
	cv::waitKey();
	return 0;
}
