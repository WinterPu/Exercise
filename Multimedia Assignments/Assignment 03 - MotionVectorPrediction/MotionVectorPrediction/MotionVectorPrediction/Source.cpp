#include <iostream>
#include "MVSearchLib.h"

int main() {

	std::string ref_image_name = "reference.pgm";
	std::string tar_image_name = "target.pgm";
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

	Predictor predictor(16,15,reference_image,target_image);
	predictor.Predict(Predictor::SEQUENTIAL_SEARCH);
	std::cout << " Sequential Search:" << std::endl;
	std::cout << " Total Consuming Time:" << predictor.GetMethodConsumingTime()<<std::endl;
	std::cout << " SNR Value:" << predictor.GetSNRValue()<< std::endl << std::endl << std::endl;
	cv::imshow("Sequential Search Image", predictor.GetPredictedImage());



	predictor.Predict(Predictor::LOGARITHM_2D_SEARCH);
	std::cout << " 2D Logarithm Search:" << std::endl;
	std::cout << " Total Consuming Time:" << predictor.GetMethodConsumingTime() << std::endl;
	std::cout << " SNR Value:" << predictor.GetSNRValue() << std::endl;
	cv::imshow(" 2D Logarithm Search Image", predictor.GetPredictedImage());



	cv::imshow("Reference Image", reference_image);
	cv::imshow("Target Image", target_image);

	cv::waitKey();
	return 0;
}