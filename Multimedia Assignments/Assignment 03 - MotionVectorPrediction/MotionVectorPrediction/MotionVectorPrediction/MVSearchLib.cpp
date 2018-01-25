#include "MVSearchLib.h"

Predictor::Predictor(int N, int P, cv::Mat ref, cv::Mat tar)
{
	if (Init(N, P, ref, tar))
		status = DATA_READY;
	else
		status = DATA_ERROR;
}

bool Predictor::Init(int N, int P, cv::Mat ref_image, cv::Mat tar_image)
{
	status = DATA_ERROR;
	
	if (!CheckData(N,P,ref_image,tar_image))
		return false;
	this->N = N;
	this->P = P;
	mv_list.clear();
	consuming_time = 0;
	snr_value = 0;
	ref = ref_image;
	tar = tar_image;
	rows = ref.rows;
	cols = ref.cols;
	status = DATA_READY;
	return true;
}

double  Predictor::MAD(int x, int y, int i, int j) {

	double result = 0;
	for (int k = 0; k < N; k++)
	{
		for (int l = 0; l < N; l++) {
			result += abs((double)tar.at<uchar>(x + k, y + l)-(double)ref.at<uchar>(x + i + k, y + j + l));
		}
	}
	result /= (N * N);
	return result;
}



MotionVector Predictor::SequentialSearch(int x, int y) {

	double min_mad = MAX_VALUE;
	MotionVector motionvector;
	for (int i = -P; i <= P; i++)
	{
		for (int j = -P; j <= P; j++)
		{
			if (!CheckBoundary(x, y) || !CheckBoundary(x + i, y + j))
				continue;

			double current_mad = MAD(x,y,i,j);
			if (current_mad < min_mad)
			{
				min_mad = current_mad;
				motionvector.u = i;
				motionvector.v = j;
			}
		}
	}
	return motionvector;
}

MotionVector Predictor::Logarithm2DSearch(int x, int y)
{
	double min_mad = MAX_VALUE;
	MotionVector motionvector;
	
	bool last = false;
	int offset = ceil(P / 2.0);
	MotionVector directions[9] = { {0,0},{0,-1},{0,1},{-1,0},{-1,-1},{-1,1},{1,0},{1,-1},{1,1} };
	
	while (!last)
	{
		for (int i = 0; i < 9; i++)
		{
			int displacement_i = directions[i].u * offset;
			int displacement_j = directions[i].v * offset;

			if (!CheckBoundary(x, y) || !CheckBoundary(x + displacement_i, y + displacement_j))
				continue;

			double current_mad = MAD(x, y, displacement_i, displacement_j);
			if (current_mad < min_mad)
			{
				min_mad = current_mad;
				motionvector.u = displacement_i;
				motionvector.v = displacement_j;
			}
		}
		if (offset == 1)
			last = true;
		offset = ceil(offset / 2.0);
	}

	return motionvector;
}

bool Predictor::CheckBoundary(int x, int y)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols)
		return false;
	if ((rows - x) < N || (cols - y) < N)
		return false;

	return true;
}

void Predictor::FindMotionVectors(SearchMethod mode)
{
	mv_list.clear();
	//(x,y) the origin (upper -left corner) of each macroblock
	for (int x = 0; x < rows; x += N)
	{
		for (int y = 0; y < cols; y += N)
		{
			MotionVector mv;
			if (mode == SEQUENTIAL_SEARCH)
				mv = SequentialSearch(x, y);
			else if (mode == LOGARITHM_2D_SEARCH)
				mv = Logarithm2DSearch(x, y);
			mv_list.push_back(mv);
		}
	}
}

void Predictor::ReconstructImage()
{
	predicted.create(rows,cols, cv::IMREAD_GRAYSCALE);
	int count = 0;
	for (int x = 0; x < rows; x += N)
	{
		for (int y = 0; y < cols; y += N)
		{
			int ref_x = x + mv_list[count].u;
			int ref_y = y + mv_list[count].v;
			count++;
	
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					predicted.at<uchar>(x + i, y + j) =(int)ref.at<uchar>(ref_x+i, ref_y+j);
				}
			}
		}
	}
}

void Predictor::Predict(SearchMethod mode) {

clock_t start_time = clock();
	
	FindMotionVectors(mode);

clock_t end_time = clock();
consuming_time = ((double )(end_time - start_time) / (double)CLOCKS_PER_SEC )* 1000.0;
	
	
	ReconstructImage();
	status = PREDICTION_DONE;

	CalcSNR();
}




double Predictor::CalcSNR() {
	if (!CheckPredictorStatus(PREDICTION_DONE))
		return -1;

	int m = predicted.rows;
	int n = predicted.cols;

	//check num digits
	long double numerator = 0;
	long double denominator = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) {
			numerator += (long double)pow((int)predicted.at<uchar>(i, j), 2);
			denominator += (long double)pow(((int)tar.at<uchar>(i, j) - (int)predicted.at<uchar>(i, j)), 2);
		}
	}

	snr_value = numerator / denominator;
	return snr_value;
}



bool Predictor::CheckData(int N, int P, cv::Mat ref_image, cv::Mat tar_image)
{

	if (!ref_image.data || !tar_image.data)
	{
		std::cout << "[Data Empty] ref or tar is empty" << std::endl;
		return false;
	}

	if (ref_image.rows != tar_image.rows || ref_image.cols != tar_image.cols)
	{
		std::cout << "[Frame Size Match Error] ref's size and tar's size don't match" << std::endl;
		return false;
	}

	int num_rows = ref_image.rows;
	int num_cols = ref_image.cols;

	if (num_rows % N != 0 || num_cols % N != 0)
	{
		std::cout << "[N -- Error] num pixels in the macroblock" << std::endl;
		return false;
	}

	if (N > num_rows || N >num_cols || P > num_cols || P > num_rows)
	{
		std::cout << "[N] or [P] too large" << std::endl;
		return false;
	}
	return true;
}

bool Predictor::CheckPredictorStatus(Status requirement)
{
#pragma region Available Part
	if (requirement == status)
		return true;

	if (requirement == DATA_READY && status == PREDICTION_DONE)
		return true;
#pragma endregion


	if (requirement == PREDICTION_DONE || status == DATA_READY)
	{
		std::cout << "Prediction hasn't done" << std::endl;
		return false;
	}
	else {
		std::cout << "Data [N,P,ref_image,target_image] not ready" << std::endl;
		return false;
	}
}
