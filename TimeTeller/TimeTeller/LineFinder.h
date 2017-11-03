#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv/cv.h>
#include <math.h>
#include <algorithm> 
using namespace std;
using namespace cv;
#define VK_ESCAPE 27
#define VK_SPACE 32

class LineFinder
{
public:
	LineFinder();
	~LineFinder();
	void static organizeMe(Mat &crop, Mat &point);
};

