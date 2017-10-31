#include "CircleDetector.h"

CircleDetector::CircleDetector()
{
}
CircleDetector::~CircleDetector()
{
}

void CallbackForSlider(int threshold, void *userData)
{
	bool &flag = *(static_cast<bool*>(userData));
	flag = true;
	return;
}


void CircleDetector::findAndShowCircles(Mat &img) {
	Mat copy, gray;
	img.copyTo(copy);

	cvtColor(copy, gray, CV_BGR2GRAY);
	GaussianBlur(gray, gray, Size(0, 0), 2, 2);

	namedWindow("Obtained Circles", CV_WINDOW_NORMAL);
	int threshold_lower = 50, threshold_upper = 100; bool change = true;

	//Results Vector
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

	//TODO: Utilizando o primero circulo em vector<Vec3f> circles, fazer crop � imagem que estiver no copy, guardar em img, e mostrar aqui 

	int startX = (circles[0][0] - circles[0][2]), startY = (circles[0][1] - circles[0][2]), totalsize = (2 * circles[0][2]);

	Mat ROI(img, Rect(startX, startY, totalsize, totalsize));

	Mat croppedImage;

	// Copy the data into new matrix
	ROI.copyTo(croppedImage);

	Mat croppedGrayscale;
	cvtColor(croppedImage, croppedGrayscale, CV_BGR2GRAY);

	// Canny edge detection
	Mat croppedEdges;
	Canny(croppedGrayscale, croppedEdges, 200, 250, 3);

	Mat copy1;
	vector<Vec4i> lines;
	int line_threshold = 50, max_gap = 10;
	int clockCenter_y = croppedImage.size().height / 2;
	int clockCenter_x = croppedImage.size().width / 2;
	bool change1 = true;

	namedWindow("Obtained Lines", CV_WINDOW_NORMAL);
	int desiredWidth = 640, desiredheight = 480;
	resizeWindow("Obtained Lines", desiredWidth, desiredheight);
	for (;;) {
		if (change1) {
			createTrackbar("Threshhold", "Obtained Lines", &line_threshold, 80, CallbackForSlider, &change1);
			createTrackbar("Maximum Gap", "Obtained Lines", &max_gap, 15, CallbackForSlider, &change1);

			croppedImage.copyTo(copy1);

			/// Apply the Hough Transform to find the lines
			HoughLinesP(
				croppedEdges, //input Mat
				lines, //output array with format (x1,y1,x2,y2)
				1, //leave as 1
				(CV_PI / 180), //leave as it is 
				line_threshold, // accumulator threshold parameter. Only those lines are returned that get enough votes ( >\texttt{threshold} ).
				30, // minimum line length. Line segments shorter than that are rejected.
				max_gap); // maximum allowed gap between points on the same line to link them.


			//eliminates unnecessary lines
			for (int i = lines.size() - 1; i >= 0; i--) {
				//sees if the line have at least 1 of the points in the center of the image
				if (((lines[i][0] >= (clockCenter_x*0.85)) && (lines[i][0] <= (clockCenter_x*1.15)) &&	//x1
					(lines[i][1] >= (clockCenter_y*0.85)) && (lines[i][1] <= (clockCenter_y*1.15))) ||	//y1
					((lines[i][2] >= (clockCenter_x*0.85)) && (lines[i][2] <= (clockCenter_x*1.15)) &&	//x2
					(lines[i][3] >= (clockCenter_y*0.85)) && (lines[i][3] <= (clockCenter_y*1.15)))) {	//y2
																										//keep line
					continue;
				}
				else {
					lines.erase(lines.begin() + i);
				}
			}
			
			///draw all lines
			for (int i = 0; i < lines.size(); i++) {
				line(copy1, Point(lines[i][0], lines[i][1]),
					Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
			}
			change = false;
		}

		/// Show your results
		imshow("Obtained Lines", copy1);

		if (cvWaitKey(10) == VK_SPACE)
			break;
	}
	destroyWindow("Obtained Lines");



	/*namedWindow("Hough Circle Result", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Result", copy); //Deve mostrar img depois de cropped, n�o copy.

	namedWindow("Cropped+lines", 1);
	imshow("Cropped+lines", croppedImage);*/
	
	return;
}

