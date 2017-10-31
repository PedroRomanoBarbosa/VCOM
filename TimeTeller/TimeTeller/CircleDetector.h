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


void CallbackForSlider(int threshold, void *userData);

class CircleDetector
{
public:
	CircleDetector();
	~CircleDetector();
	void static findAndShowCircles(Mat &img);
};

