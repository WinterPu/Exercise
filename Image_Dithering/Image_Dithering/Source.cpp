#include <iostream>
#include "DitheringLib.h"


int main() {

	std::string image_name = "Original.jpg";
	std::string path_name = "C:/Users/Winter Pu/Desktop/Image_Dithering/";
	cv::Mat original_image;

	original_image = cv::imread(path_name + image_name, CV_LOAD_IMAGE_COLOR);

	
	if (!original_image.data)
	{
		std::cout << "Image Open Error! Please Check The Image Path!" << std::endl;
		return -1;
	}


	cv::Mat gray_level_image = GenerateGrayLevelImage(original_image);
	cv::Mat dithered_image_01 = GenerateDitheredImage_A1(gray_level_image);
	cv::Mat dithered_image_02 = GenerateDitheredImage_A2(gray_level_image);

	cv::imwrite(path_name + "Gray Level Image " +image_name, gray_level_image);
	cv::imwrite(path_name + "Dithered Image 01 " + image_name, dithered_image_01);
	cv::imwrite(path_name + "Dithered Image 02 " + image_name, dithered_image_02);
	
	cv::imshow("Original Image", original_image);
	cv::imshow("Gray Level", gray_level_image);
	cv::imshow("Dithered Image01", dithered_image_01);
	cv::imshow("Dithered Image02", dithered_image_02);


	//follow imshow to give time to show an image
	cv::waitKey();
	return 0;
}