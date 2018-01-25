#pragma once
#ifndef MVSEARCHLIB_H
#define MVSEARCHLIB_H

#include <opencv2/opencv.hpp>
#include <cmath>
#include <ctime>
#define MAX_VALUE 999999999999


struct MotionVector {
	int u;
	int v;

	MotionVector() :u(0), v(0) {}
	MotionVector(int v_u, int v_v) {
		u = v_u;
		v = v_v;
	}
};


class Predictor {
public:
	//Predictor Status
	static const enum Status { DATA_ERROR,DATA_READY,PREDICTION_DONE};
	static const enum SearchMethod { SEQUENTIAL_SEARCH, LOGARITHM_2D_SEARCH };
#pragma region InitPart 
	Predictor(int N,int P,cv::Mat ref, cv::Mat tar);
	//[N] -->  num pixels in the macroblock
	//[P] -->  search windows (2P-1, 2P+1)
	// true --- init successfully
	// false --- fail to init
	bool Init(int N, int P, cv::Mat ref_image, cv::Mat tar_image);
	// true --- data available
	// false --- data is not available
	bool CheckData(int N, int P, cv::Mat ref_image, cv::Mat tar_image);
#pragma endregion

	void Predict(SearchMethod mode = SEQUENTIAL_SEARCH);
	
	inline cv::Mat GetPredictedImage() { return predicted; }
	inline long GetMethodConsumingTime() { return consuming_time; }
	inline double GetSNRValue() { return snr_value; }

protected:
	bool CheckPredictorStatus(Status requirement);

	//[x,y] the origin of the current macroblock (-- upper left corner)
	//[i,j] the displacements
	double MAD(int x, int y, int i, int j);
	double CalcSNR();
	MotionVector SequentialSearch(int x, int y);
	MotionVector Logarithm2DSearch(int x, int y);
	bool CheckBoundary(int x,int y);

	void FindMotionVectors(SearchMethod mode = SEQUENTIAL_SEARCH);
	void ReconstructImage();

private:
	Status status;

	int N; // num pixels in the macroblock
	int P; // search windows (2P-1, 2P+1)
	cv::Mat ref;
	cv::Mat tar;
	int rows;
	int cols;

	cv::Mat predicted;
	long consuming_time;//ms
	double snr_value;
	
	std::vector<MotionVector> mv_list;
};

#endif 