#include <iostream>
#include "EnhancementLibrary.h"

//Practice:
//1. Power Law Transmation
//2. Histogram Equalization 
//3. Histogram Matching

int main() {

	std::string image_name = "Original.jpg";
	std::string path_name = "C:/Users/Winter Pu/Desktop/Image_Enhancement/";
	cv::Mat original_image;

#if ENABLE_MODE_GRAY_ONLY
	original_image = cv::imread(path_name + image_name,	cv::IMREAD_GRAYSCALE);
#else
	original_image = cv::imread(path_name + image_name, CV_LOAD_IMAGE_COLOR);
#endif


	if (!original_image.data)
	{
		std::cout << "Image Open Error! Please Check The Image Path!" << std::endl;
		return -1;
	}

	//power law's parameters =>please come to head file [POWERLAW_C] [POWERLAW_GAMMA]
 	cv::Mat enhanced_image_powerlaw = DoPowerLawTransformation(original_image);
	cv::Mat enhanced_image_histogramequalization = DoHistogramEqulization(original_image);

	//http://docs.opencv.org/2.4/modules/imgproc/doc/histograms.html?highlight=equalizehist
	//cv::Mat enhanced_image_histogramequalization = original_image.clone();
	//cv::equalizeHist(original_image,enhanced_image_histogramequalization);
	cv::Mat enhanced_image_histogrammatching = GenerateHistogramMatchingImage(original_image, enhanced_image_histogramequalization);



	cv::imwrite(path_name + "PowerLaw "+ image_name,enhanced_image_powerlaw);
	cv::imwrite(path_name + "HistogramEqualization "+image_name, enhanced_image_histogramequalization);
	cv::imwrite(path_name + "HistogramMatching "+image_name, enhanced_image_histogrammatching);

	
	cv::imshow("Original Image", original_image);
	cv::imshow("Power Law", enhanced_image_powerlaw);
	cv::imshow("Histogram Equalization",enhanced_image_histogramequalization);
	cv::imshow("Histogram Matching",enhanced_image_histogrammatching);


	//follow imshow to give time to show an image
	cv::waitKey();
	return 0;
}