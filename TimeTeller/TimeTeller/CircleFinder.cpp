#include "CircleFinder.h"

CircleFinder::CircleFinder()
{
}
CircleFinder::~CircleFinder()
{
}

void static CallbackForSlider(int threshold, void *userData)
{
	bool &flag = *(static_cast<bool*>(userData));
	flag = true;
	return;
}


void CircleFinder::findAndShowCircles(Mat &img, Mat &crop) {
	Mat copy, gray;
	img.copyTo(copy);

	cvtColor(copy, gray, CV_BGR2GRAY);
	GaussianBlur(gray, gray, Size(0, 0), 2, 2);

	namedWindow("Obtained Circles", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO);
	int threshold_lower = 50, threshold_upper = 100; bool change = true;

	//Found Circles Vector
	vector<Vec3f> circles;

	for (;;) {
		if (change) {
			if (threshold_upper < threshold_lower)
				threshold_lower = threshold_upper;

			createTrackbar("Upper Bound", "Obtained Circles", &threshold_upper, 255, CallbackForSlider, &change);
			createTrackbar("Lower Bound", "Obtained Circles", &threshold_lower, threshold_upper, CallbackForSlider, &change);

			img.copyTo(copy);
			/// Apply the Hough Transform to find the circles
			HoughCircles(
				gray, //input array
				circles, //output array
				CV_HOUGH_GRADIENT, //see see cv::HoughModes. (the only implemented method is HOUGH_GRADIENT)
				1, //dp, resolution, leave as 1
				gray.rows / 8,  // change this value to detect circles with different distances to each other
				threshold_upper, threshold_lower, //higher and lower threshold passed to the internal canny detector (The smaller the second is the more false circles may be detected.)
				0, 0); //change the last two parameters (min_radius & max_radius) to detect larger circles

			/// Draw the circles detected
			for (size_t i = 0; i < circles.size(); i++) {
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);
				// circle center
				circle(copy, center, 3, Scalar(0, 255, 0), -1, 8, 0);
				// circle outline
				circle(copy, center, radius, Scalar(0, 0, 255), 3, 8, 0);
			}
			change = false;
		}

		/// Show your results
		imshow("Obtained Circles", copy);

		if (cvWaitKey(10) == VK_SPACE)
			break;
	}
	destroyWindow("Obtained Circles");


	//Utilizando o primero circulo em vector<Vec3f> circles, fazer crop à imagem que estiver no copy, guardar em img, e mostrar aqui 
	img.copyTo(copy); 
	int startX = (circles[0][0] - circles[0][2]), startY = (circles[0][1] - circles[0][2]), totalsize = (2 * circles[0][2]);
	Mat ROI(copy, Rect(startX, startY, totalsize, totalsize));

	// Copy the data into results matrix
	ROI.copyTo(crop);

	return;
}

