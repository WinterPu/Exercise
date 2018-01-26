#include <iostream>
#include <fstream>
#include <cstdio>
#include "MVSearchLib.h"

void WritePGMImage(std::string path, cv::Mat data) {

	//https://docs.opencv.org/3.0-beta/modules/imgcodecs/doc/reading_and_writing_images.html
	
	std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PXM_BINARY);
	compression_params.push_back(1);

#pragma region  This Part: I try to solve the  opencv_world320.dll Access Violation
	//the problem is the same as:
	//English Description Version: http://answers.opencv.org/question/73889/access-violation-when-using-imwrite-to-save-an-imagemat/
	//Chinese Description Version: http://bbs.csdn.net/topics/391843419?page=1


	// I thought:
	// ==> Imwrite --> PGM does not support to generate the file (when the same name file exists)


	// However, it still has the problem:

	////delete the same name file
	///*
	//If you want to delete file:
	//You must close it first:
	//Otherwise, it will cause [Permission Denied]
	////https://stackoverflow.com/questions/20237676/permission-denied-when-deleting-file-created-successfully-by-fopen

	//Error Info stored in [perror]
	//*/
	//std::fstream file_checker(path);
	//if (file_checker.is_open())
	//{
	//	file_checker.close();
	//	if (!std::remove(path.c_str()));
	//		std::perror("Error Info:");
	//}
	//else 
	//	file_checker.close();


	//try {
	//	cv::imwrite(path, data, compression_params);
	//}
	//catch (cv::Exception&e) {
	//	const char* err_msg = e.what();
	//	std::cout << "exception caught: " << err_msg << std::endl;
	//}
#pragma endregion
	cv::imwrite(path, data, compression_params);
}


int main() {

	std::string ref_image_name = "Reference Image.pgm";
	std::string tar_image_name = "Target Image.pgm";
	std::string path_name = "C:/Users/Winter Pu/Desktop/Frames/";
	cv::Mat reference_image;
	cv::Mat target_image;

	reference_image = cv::imread(path_name + ref_image_name, cv::IMREAD_GRAYSCALE);
	target_image = cv::imread(path_name + tar_image_name, cv::IMREAD_GRAYSCALE);

	if (!reference_image.data || ! target_image.data)
	{
		std::cout << "Image Open Error! Please Check The Image Path!" << std::endl;
		return -1;
	}

	std::cout << std::endl << std::endl;

	Predictor predictor(16,15,reference_image,target_image);
	predictor.Predict(Predictor::SEQUENTIAL_SEARCH);
	std::cout << "Sequential Search:" << std::endl;
	std::cout << "Total Consuming Time:" << predictor.GetMethodConsumingTime()<<std::endl;
	std::cout << "SNR Value:" << predictor.GetSNRValue()<< std::endl << std::endl << std::endl;
	cv::Mat image_sequential_search = predictor.GetPredictedImage().clone();
	cv::imshow("Sequential Search Image", image_sequential_search);
	
	std::string final_image_name01 = "Sequential Search Image.pgm";
	std::string final_path01 = path_name + final_image_name01;
	WritePGMImage(final_path01, image_sequential_search);


/////////////////////////////////////////////////////////////////////////////////


	predictor.Predict(Predictor::LOGARITHM_2D_SEARCH);
	std::cout << "2D Logarithm Search:" << std::endl;
	std::cout << "Total Consuming Time:" << predictor.GetMethodConsumingTime() << std::endl;
	std::cout << "SNR Value:" << predictor.GetSNRValue() << std::endl;
	cv::Mat image_2Dlogarithm = predictor.GetPredictedImage().clone();
	cv::imshow("2D Logarithm Search Image", image_2Dlogarithm);
	std::string final_image_name02 = "2D Logarithm Search Image.pgm";
	std::string final_path02 = path_name + final_image_name02;
	WritePGMImage(final_path02, image_2Dlogarithm);

	cv::imshow("Reference Image", reference_image);
	cv::imshow("Target Image", target_image);

	cv::waitKey();
	return 0;
}