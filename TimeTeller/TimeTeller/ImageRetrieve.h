#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <sys/stat.h>
using namespace std;
using namespace cv;


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


int input_choice();
Mat getCapture();
Mat getImage(int choice);