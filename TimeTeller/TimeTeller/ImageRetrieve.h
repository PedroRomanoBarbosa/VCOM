#pragma once
#include <iostream>
#include "opencv2/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <sys/stat.h>
using namespace std;
using namespace cv;

namespace ImageRetrieve {

	const static string DEFAULT_PATH = "data/images/basic_round.jpg";
	const static string DEFAULT_CAPTURE_PATH = "data/capture/";

	/**
	Check if a file exists before opening
	Adapted from https://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing
	*/
	bool check_file(string filename);

	/**
	Attempts to open an image fie and read its contents

	@param filepath The location of the image
	@return The Mat data of the image.
	*/
	Mat getImage(string filepath);

	/**
	Attempts to open an image on the default location. "data/images/basic_square.jpg"

	@return The Mat data of the image.
	*/
	Mat getImage();

	/**
	Atempts to use the camera to get a picture taken.

	@param img The Mat space where the image will be stored
	*/
	void getCapture(Mat &img);

	/**
	Provides the user with a choice of how to retreve an image.

	@param img The Mat space where the image will be stored
	*/
	void input_choice(Mat &img);
}

