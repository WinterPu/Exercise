#pragma once
#ifndef  ROTATIONLIBRARY_H
#define	 ROTATIONLIBRARY_H

#include <opencv2\opencv.hpp>
#include <cmath>

#define PI 3.141592653589793

//including this head file many times will cause the global variables are defined repeatedly
//define with extern in the head file
//declare in the cpp file
//in other files, you can just use them
extern int original_boundary_height;
extern int original_boundary_width;

enum FuncType {
	Nearst,
	Bilinear,
	Bicubic
};

#define IMAGE_TYPE CV_8UC3
typedef float MathType;

const cv::Mat color_black = (cv::Mat_<cv::Vec3b>(1, 1) << cv::Vec3b(0, 0, 0));


bool IsInTheBoundary(int i,int j);
void HandleExceedBoundaryPosition(int &i,int &j );
cv::Mat GetOriginalMappingPosition(int x, int y, cv::Mat rotated_matrix, cv::Mat center_vector);
void DoImagePadding(int & height, int & width);

cv::Mat	RotateImage(cv::Mat original, MathType angle, FuncType type);

cv::Vec3b GetColorNearst(cv::Mat original_image, cv::Mat mapping_position);
cv::Vec3b GetColorBilinear(cv::Mat original_image, cv::Mat mapping_position);
cv::Vec3b GetColorBicubic(cv::Mat original_image, cv::Mat mapping_position);


MathType GetLinearInterpolationValue(MathType x1, MathType x2, MathType x, MathType q1, MathType q2);
//function S
MathType S(MathType x);
cv::Vec3b F(int i, int j, cv::Mat original_image);
#endif // ! ROTATIONLIBRARY_H
