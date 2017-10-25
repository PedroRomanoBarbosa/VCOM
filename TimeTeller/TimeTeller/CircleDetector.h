#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;


class CircleDetector
{
public:
	CircleDetector();
	~CircleDetector();
	void static findAndShowCircles(Mat &img);
};

