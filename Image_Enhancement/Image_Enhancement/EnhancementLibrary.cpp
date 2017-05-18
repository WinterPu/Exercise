#include "EnhancementLibrary.h"

#pragma region  General Functions Preparation

int ControlColorValueLimitation(int color_value)
{
	color_value = std::max(color_value, 0);
	color_value = std::min(color_value, 255);
	return color_value;
}

BGRHistogramArray<int> GetPDF(cv::Mat image)
{
	//PDF
	BGRHistogramArray<int> image_bgr_pdf;

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int b_value = (int)(image.at<cv::Vec3b>(i, j)[0]);
			image_bgr_pdf.b_array[b_value]++;

			int g_value = (int)(image.at<cv::Vec3b>(i, j)[1]);
			image_bgr_pdf.g_array[g_value]++;

			int r_value = (int)(image.at<cv::Vec3b>(i, j)[2]);
			image_bgr_pdf.r_array[r_value]++;
		}
	}
	return image_bgr_pdf;
}

template<typename T1,typename T2>
void  GenerateCDFFromPDF(T1* pdf_array,T2* cdf_array)
{
	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
			cdf_array[0] = pdf_array[0];
		else
			cdf_array[i] = cdf_array[i - 1] + pdf_array[i];
	}
}


BGRHistogramArray<int> GetCDF(BGRHistogramArray<int> image_pdf)
{
	BGRHistogramArray<int> cdf_array;

	GenerateCDFFromPDF(image_pdf.b_array, cdf_array.b_array);
	GenerateCDFFromPDF(image_pdf.g_array, cdf_array.g_array);
	GenerateCDFFromPDF(image_pdf.r_array, cdf_array.r_array);

	return cdf_array;
}

BGRHistogramArray<float> GetCDF(BGRHistogramArray<int> image_pdf, int total_pixels_count)
{

	BGRHistogramArray<float> pdf_array;
	BGRHistogramArray<float> cdf_array;

	//change to probability cdf
	for (int i = 0; i < 256; i++) {
		pdf_array.b_array[i] = (float)image_pdf.b_array[i] / (float)total_pixels_count;
		pdf_array.g_array[i] = (float)image_pdf.g_array[i] / (float)total_pixels_count;
		pdf_array.r_array[i] = (float)image_pdf.r_array[i] / (float)total_pixels_count;
	}

	GenerateCDFFromPDF(pdf_array.b_array, cdf_array.b_array);
	GenerateCDFFromPDF(pdf_array.g_array, cdf_array.g_array);
	GenerateCDFFromPDF(pdf_array.r_array, cdf_array.r_array);

	return cdf_array;
}


void GetGrayImagePDF(cv::Mat original,int* pdf_array) {

	cv::Mat enhanced_image = original.clone();

	for (int i = 0; i < enhanced_image.rows; i++)
	{
		for (int j = 0; j < enhanced_image.cols; j++)
		{
			int gray_value = (int)(enhanced_image.at<uchar>(i, j));
			pdf_array[gray_value]++;
		}
	}
}

void GetGrayImageCDF(cv::Mat original,float* cdf_array) {

	int image_pdf[256] = { 0 }; 
	GetGrayImagePDF(original,image_pdf);

	float pdf_array[256] = { 0 };

	float total = original.rows * original.cols;
	for (int i = 0; i < 256; i++)
		pdf_array[i] = (float)image_pdf[i] / total;

	//CDF
	GenerateCDFFromPDF(pdf_array, cdf_array);
}
#pragma endregion


//Power Law
int PowerLawFunction(int gray_level)
{
	int c = POWERLAW_C;
	float gamma = POWERLAW_GAMMA;

	int result = (int)(c * pow(gray_level, gamma));

	return  ControlColorValueLimitation(result);
}

cv::Mat DoPowerLawTransformation(cv::Mat original)
{
	cv::Mat enhanced_image = original.clone();
	for (int i = 0; i < enhanced_image.rows; i++)
	{
		for (int j = 0; j < enhanced_image.cols; j++)
		{

#if ENABLE_MODE_GRAY_ONLY
			// imread - grayscale
			int gray_value = (int)(enhanced_image.at<uchar>(i, j));
			enhanced_image.at<uchar>(i, j) = (uchar)(PowerLawFunction(gray_value));

#else
			int b = (int)(enhanced_image.at<cv::Vec3b>(i, j)[0]);
			enhanced_image.at<cv::Vec3b>(i, j)[0] = (int)(PowerLawFunction(b));
			int g = (int)(enhanced_image.at<cv::Vec3b>(i, j)[1]);
			enhanced_image.at<cv::Vec3b>(i, j)[1] = (int)(PowerLawFunction(g));
			int r = (int)(enhanced_image.at<cv::Vec3b>(i, j)[2]);
			enhanced_image.at<cv::Vec3b>(i, j)[2] = (int)(PowerLawFunction(r));
#endif // ENABLE_MODE_GRAY_ONLY
		}
	}
	return enhanced_image;
}



#pragma region  Histogram Equalization Function Preparation

int HistogramMatchingFunction(int gray_level, int* cdf_array, int cdf_fmin, int rows, int cols, int L)
{
	//notice that div: float / float  not int / int
	int result = round((float)(cdf_array[gray_level] - cdf_fmin) / (float)(rows *cols - cdf_fmin) *  (float)(L - 1));
	return  ControlColorValueLimitation(result);
}

int FindCDFFMin(int * cdf_array){
	int cdf_fmin = MAX_VALUE;
	for (int i = 0; i < 256; i++)
	{
		if (cdf_array[i] != 0 && cdf_fmin > cdf_array[i])
		{
			cdf_fmin = cdf_array[i];
			break;
		}
	}
	return cdf_fmin;
}

#pragma endregion


#pragma region Histogram Matching Preparation


void MatchEachPixel(float * eq_original_cdf, float * eq_ref_cdf, int * mapset)
{
	float diff_array[256][256];

	for (int i = 0; i<256; i++)
		for (int j = 0; j < 256; j++)
			diff_array[i][j] = abs(eq_original_cdf[i] - eq_ref_cdf[j]);

	for (int i = 0; i < 256; i++)
	{
		int index = 0;
		float min_value = diff_array[i][index];
		for (int j = 1; j < 256; j++)
		{
			if (min_value > diff_array[i][j])
			{
				min_value = diff_array[i][j];
				index = j;
			}
		}

		mapset[i] = index;
	}
}
#pragma endregion



#if ENABLE_MODE_GRAY_ONLY


#pragma region  IMREAD_GRAYSCALE

//not use function just for present the algorithm
cv::Mat DoHistogramEqulization(cv::Mat original)
{
	cv::Mat enhanced_image = original.clone();

	//PDF
	int pdf_array[256] = { 0 };
	for (int i = 0; i < enhanced_image.rows; i++)
	{
		for (int j = 0; j < enhanced_image.cols; j++)
		{
			int gray_value = (int)(enhanced_image.at<uchar>(i, j));
			pdf_array[gray_value]++;
		}
	}

	//CDF
	int cdf_array[256] = { 0 };
	GenerateCDFFromPDF(pdf_array,cdf_array);


	//preparation
	int cdf_fmin = FindCDFFMin(cdf_array);
	int M = enhanced_image.rows;
	int N = enhanced_image.cols;

	int L = 256;

	for (int i = 0; i < enhanced_image.rows; i++)
	{
		for (int j = 0; j < enhanced_image.cols; j++)
		{
			int gray_value = (int)(enhanced_image.at<uchar>(i, j));
			enhanced_image.at<uchar>(i, j) = (uchar)(HistogramMatchingFunction(gray_value, cdf_array, cdf_fmin, M, N, L));
		}
	}
	return enhanced_image;
}

void DoHistogramMatching(cv::Mat original_image, cv::Mat reference_image,int* image_mapset)
{
	//original image does histogram equlization
	cv::Mat eq_original_image = DoHistogramEqulization(original_image);
	//Get CDF
	float eq_original_cdf[256] = {0};
	GetGrayImageCDF(original_image, eq_original_cdf);


	//reference image does histogram equlization
	cv::Mat eq_ref_image = DoHistogramEqulization(reference_image);
	//Get CDF
	float eq_ref_cdf[256] = { 0 };
	GetGrayImageCDF(reference_image,eq_ref_cdf);

	MatchEachPixel(eq_original_cdf, eq_ref_cdf, image_mapset);
}

cv::Mat GenerateHistogramMatchingImage(cv::Mat original, cv::Mat reference)
{
	int image_mapset[256] = { 0 };
	DoHistogramMatching(original, reference,image_mapset);
	
	cv::Mat enhanced_image = original.clone();

	for (int i = 0; i < enhanced_image.rows; i++)
	{
		for (int j = 0; j < enhanced_image.cols; j++)
		{
			int gray_value = (int)(enhanced_image.at<uchar>(i, j));
			enhanced_image.at<uchar>(i, j) = (uchar)(image_mapset[gray_value]);
		}
	}
	return enhanced_image;
}
#pragma endregion

#else
cv::Mat DoHistogramEqulization(cv::Mat original)
{
	cv::Mat enhanced_image = original.clone();

	//PDF
	BGRHistogramArray<int> pdf_array = GetPDF(enhanced_image);

	//CDF
	BGRHistogramArray<int> cdf_array = GetCDF(pdf_array);

	
	//preparation
	int cdf_fmin_b = FindCDFFMin(cdf_array.b_array);
	int cdf_fmin_g = FindCDFFMin(cdf_array.g_array);
	int cdf_fmin_r = FindCDFFMin(cdf_array.r_array);

	int M = enhanced_image.rows;
	int N = enhanced_image.cols;

	int L = 256;

	//process
	for (int i = 0; i < enhanced_image.rows; i++)
	{
		for (int j = 0; j < enhanced_image.cols; j++)
		{
			int b = (int)(enhanced_image.at<cv::Vec3b>(i, j)[0]);
			enhanced_image.at<cv::Vec3b>(i, j)[0] = (int)(HistogramMatchingFunction(b,cdf_array.b_array,cdf_fmin_b,M,N,L));
			int g = (int)(enhanced_image.at<cv::Vec3b>(i, j)[1]);
			enhanced_image.at<cv::Vec3b>(i, j)[1] = (int)(HistogramMatchingFunction(g, cdf_array.g_array, cdf_fmin_g, M, N, L));
			int r = (int)(enhanced_image.at<cv::Vec3b>(i, j)[2]);
			enhanced_image.at<cv::Vec3b>(i, j)[2] = (int)(HistogramMatchingFunction(r, cdf_array.r_array, cdf_fmin_r, M, N, L));
		}
	}
	return enhanced_image;
}


BGRHistogramArray<int>  DoHistogramMatching(cv::Mat original_image, cv::Mat reference_image)
{
	//original image does histogram equlization
	cv::Mat eq_original_image = DoHistogramEqulization(original_image);
	//Get CDF
	BGRHistogramArray<float> eq_original_cdf =  GetImageCDF(original_image);


	//reference image does histogram equlization
	cv::Mat eq_ref_image = DoHistogramEqulization(reference_image);
	//Get CDF
	BGRHistogramArray<float> eq_ref_cdf = GetImageCDF(reference_image);


	BGRHistogramArray<int> image_mapset;

	MatchEachPixel(eq_original_cdf.b_array, eq_ref_cdf.b_array, image_mapset.b_array);
	MatchEachPixel(eq_original_cdf.g_array, eq_ref_cdf.g_array, image_mapset.g_array);
	MatchEachPixel(eq_original_cdf.r_array, eq_ref_cdf.r_array, image_mapset.r_array);

	return image_mapset;
}


cv::Mat GenerateHistogramMatchingImage(cv::Mat original, cv::Mat reference)
{
	BGRHistogramArray<int>  image_mapset = DoHistogramMatching(original,reference);

	cv::Mat enhanced_image = original.clone();

	for (int i = 0; i < enhanced_image.rows; i++)
	{
		for (int j = 0; j < enhanced_image.cols; j++)
		{
			int b = (int)(enhanced_image.at<cv::Vec3b>(i, j)[0]);
			enhanced_image.at<cv::Vec3b>(i, j)[0] = (int)(image_mapset.b_array[b]);
			int g = (int)(enhanced_image.at<cv::Vec3b>(i, j)[1]);
			enhanced_image.at<cv::Vec3b>(i, j)[1] = (int)(image_mapset.g_array[g]);
			int r = (int)(enhanced_image.at<cv::Vec3b>(i, j)[2]);
			enhanced_image.at<cv::Vec3b>(i, j)[2] = (int)(image_mapset.r_array[r]);
		}
	}
	return enhanced_image;
}

#endif // ENABLE_MODE_GRAY_ONLY





