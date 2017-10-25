#include "CircleDetector.h"

CircleDetector::CircleDetector()
{
}
CircleDetector::~CircleDetector()
{
}

void CircleDetector::findAndShowCircles(Mat &img)
{
	Mat src, gray;
	img.copyTo(src);
	cvtColor(src, gray, CV_BGR2GRAY);

	//GaussianBlur(gray, gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows / 16, 100, 100, 0, 0);

	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	/// Show your results
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);

	return;
}
