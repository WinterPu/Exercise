#pragma once
#ifndef DITHERINGLIB_H
#define DITHERINGLIB_H

#include <opencv2\opencv.hpp>
#include <cmath>
#include <iostream>
#define MAX_VALUE 99999999

#define FIRST_LEVEL 51
#define SECOND_LEVEL 101
#define THIRD_LEVEL 151
#define FORTH_LEVEL 201

extern int order[4][2];


#define N 4
extern int order_matrix[4][4];

cv::Mat GenerateGrayLevelImage(cv::Mat original_image);
cv::Mat GenerateDitheredImage_A1(cv::Mat gray_level_image);
cv::Mat GenerateDitheredImage_A2(cv::Mat gray_level_image);

#endif
