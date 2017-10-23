#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include "ImageRetrieve.h"
#include "Time.h"
using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{
	Mat img;

	if (argc == 2) {
		img = getImage(argv[1]);
	} else {
		cout << "No arguments";
		return 1;
	}

	cout << "Image Loaded.";
	imshow("Original Image", img);

	waitKey(0);
	return 0;
}