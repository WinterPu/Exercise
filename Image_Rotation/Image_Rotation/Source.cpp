#include <iostream>
#include <string>
#include "RotationLibrary.h"
int main() {

	std::string image_name = "C:/Users/Winter Pu/Desktop/Image_Processing HW/512x512bb.jpg";
	cv::Mat original_image;
	original_image = cv::imread(image_name.c_str(), CV_LOAD_IMAGE_COLOR);

	cv::Mat rotated_image_nearst(IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_TYPE);
	cv::Mat rotated_image_bilinear(IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_TYPE);
	cv::Mat rotated_image_bicubic( IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_TYPE);
	

	rotated_image_nearst = RotateImage(original_image,30,Nearst);
	rotated_image_bilinear = RotateImage(original_image, 30, Bilinear);
	rotated_image_bicubic = RotateImage(original_image, 30, Bicubic);


	cv::imwrite("C:/Users/Winter Pu/Desktop/rotation_nearst.jpg", rotated_image_nearst);
	cv::imwrite("C:/Users/Winter Pu/Desktop/rotation_bilinear.jpg", rotated_image_bilinear);
	cv::imwrite("C:/Users/Winter Pu/Desktop/rotation_bicubic.jpg", rotated_image_bicubic);

	cv::imshow("Nearst", rotated_image_nearst);
	cv::imshow("Bilinear", rotated_image_bilinear);
	cv::imshow("Bicubic", rotated_image_bicubic);

	//follow imshow to give time to show an image
	cv::waitKey();
	return 0;
}
