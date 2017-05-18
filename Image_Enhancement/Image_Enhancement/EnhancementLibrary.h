#pragma once
#ifndef ENHANCEMENTLIBRARY_H
#define ENHANCEMENTLIBRARY_H

#include <opencv2\opencv.hpp>
#include <cmath>
#include <iostream>
#define MAX_VALUE 99999999

#define POWERLAW_C 1
#define POWERLAW_GAMMA 1.1

#define ENABLE_MODE_GRAY_ONLY 0

// name rule
//eq = histogram equalized

template <class TemplateType>
struct BGRHistogramArray {
	TemplateType b_array[256];
	TemplateType g_array[256];
	TemplateType r_array[256];
	BGRHistogramArray() {
		memset(b_array,0,(256*sizeof(TemplateType)));
		memset(g_array, 0, (256 * sizeof(TemplateType)));
		memset(r_array, 0, (256 * sizeof(TemplateType)));
	}
};


#pragma region General Functions Preparation

int ControlColorValueLimitation(int color_value);

BGRHistogramArray<int> GetPDF(cv::Mat image);

// get CDF with probability
BGRHistogramArray<int> GetCDF(BGRHistogramArray<int> image_pdf);

// get pesudo CDF with pixel color value's   --number count---
BGRHistogramArray<float> GetCDF(BGRHistogramArray<int> image_pdf,int total_pixels_count);
inline BGRHistogramArray<float> GetImageCDF(cv::Mat image) { return GetCDF(GetPDF(image), image.rows * image.cols); }

//image read in gray level
void GetGrayImagePDF(cv::Mat original,int * pdf_array);
void GetGrayImageCDF(cv::Mat original,float* cdf_array);

#pragma endregion



//Power Law
int PowerLawFunction(int gray_level);
cv::Mat DoPowerLawTransformation(cv::Mat original);


//Histogram Equalization
//reference:https://zh.wikipedia.org/wiki/%E7%9B%B4%E6%96%B9%E5%9B%BE%E5%9D%87%E8%A1%A1%E5%8C%96
int FindCDFFMin(int * cdf_array);
int HistogramMatchingFunction(int gray_level,int* cdf_array,int cdf_fmin,int rows,int cols,int L);
cv::Mat DoHistogramEqulization(cv::Mat original);




//http://fourier.eng.hmc.edu/e161/lectures/contrast_transform/node3.html
//Histogram Matching
void MatchEachPixel(float* eq_original_cdf, float* eq_ref_cdf, int* mapset);
cv::Mat GenerateHistogramMatchingImage(cv::Mat original, cv::Mat reference);
#if !ENABLE_MODE_GRAY_ONLY 
BGRHistogramArray<int> DoHistogramMatching(cv::Mat original_image, cv::Mat reference_image);
#else 
void DoHistogramMatching(cv::Mat original_image, cv::Mat reference_image,int*  image_mapset);
#endif


#endif // ! ENHANCEMENTLIBRARY_H