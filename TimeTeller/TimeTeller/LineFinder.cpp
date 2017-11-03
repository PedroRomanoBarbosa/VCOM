#include "LineFinder.h"



LineFinder::LineFinder()
{
}
LineFinder::~LineFinder()
{
}

//Used to compare lines length
struct linelength {
	bool operator() (Vec4i line1, Vec4i line2) {
		float length1 = sqrt((line1[2] - line1[0])*(line1[2] - line1[0]) + (line1[3] - line1[1])*(line1[3] - line1[1]));
		float length2 = sqrt((line2[2] - line2[0])*(line2[2] - line2[0]) + (line2[3] - line2[1])*(line2[3] - line2[1]));
		return (length1 < length2);
	}
} mylinelength;

void static CallbackForSlider(int threshold, void *userData)
{
	bool &flag = *(static_cast<bool*>(userData));
	flag = true;
	return;
}

double distancePoint(Point p1, Point p2) {

	double x1 = p1.x;
	double y1 = p1.y;
	double x2 = p2.x;
	double y2 = p2.y;

	double x = x1 - x2;
	double y = y1 - y2;

	// Calculating Euclidean distance
	double dist;
	dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);

	return dist;
}

float ReturnAngle(Vec4i line1, Vec4i line2) {
	//line format is (x1,y1,x2,y2)
	float angle1 = atan2(line1[3] - line1[1], line1[2] - line1[0]);
	float angle2 = atan2(line2[3] - line2[1], line2[2] - line2[0]);
	float result = (angle2 - angle1) * 180 / CV_PI;

	if (result<0)
		result += 360;

	return result;
}

void LineFinder::findPointersAndAngles(Mat &crop, Mat &point, vector<float> &angles) {
	Mat croppedImage;
	crop.copyTo(croppedImage);

	Mat croppedGrayscale;
	cvtColor(croppedImage, croppedGrayscale, CV_BGR2GRAY);

	// Canny edge detection
	Mat croppedEdges;
	Canny(croppedGrayscale, croppedEdges, 200, 250, 3);

	Mat copy;
	vector<Vec4i> lines;
	int line_threshold = 50, max_gap = 10;
	int clockCenter_y = croppedImage.size().height / 2;
	int clockCenter_x = croppedImage.size().width / 2;
	bool change = true;

	namedWindow("Obtained Lines", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO);
	int desiredWidth = 640, desiredheight = 480;
	float angle;
	resizeWindow("Obtained Lines", desiredWidth, desiredheight);

	cout << "Change threshold values until hours' line is red, minutes green and seconds blue" << endl;

	for (;;) {
		if (change) {
			createTrackbar("Threshhold", "Obtained Lines", &line_threshold, 80, CallbackForSlider, &change);
			createTrackbar("Maximum Gap", "Obtained Lines", &max_gap, 15, CallbackForSlider, &change);

			croppedImage.copyTo(copy);

			/// Apply the Hough Transform to find the lines
			HoughLinesP(
				croppedEdges, //input Mat
				lines, //output array with format (x1,y1,x2,y2)
				1, //leave as 1
				(CV_PI / 180), //leave as it is 
				line_threshold, // accumulator threshold parameter. Only those lines are returned that get enough votes ( >\texttt{threshold} ).
				30, // minimum line length. Line segments shorter than that are rejected.
				max_gap); // maximum allowed gap between points on the same line to link them.


						  //eliminates lines not in the center
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

			//eliminates lines duplicates
			for (int i = lines.size() - 1; i >= 0; i--) {
				for (int j = 0; j < i; j++) {
					angle = ReturnAngle(lines[i], lines[j]);
					if (angle < 5 || angle > 355) {
						lines.erase(lines.begin() + i);
						break;
					}
				}
			}

			//sort lines by lines length
			std::sort(lines.begin(), lines.end(), mylinelength);

			///draw all lines

			if (lines.size() == 2) {
				line(copy, Point(lines[0][0], lines[0][1]),
					Point(lines[0][2], lines[0][3]), Scalar(0, 0, 255), 3, 8);
				line(copy, Point(lines[1][0], lines[1][1]),
					Point(lines[1][2], lines[1][3]), Scalar(0, 255, 0), 3, 8);
			}
			else if (lines.size() == 3) {
				line(copy, Point(lines[0][0], lines[0][1]),
					Point(lines[0][2], lines[0][3]), Scalar(0, 0, 255), 3, 8);
				line(copy, Point(lines[1][0], lines[1][1]),
					Point(lines[1][2], lines[1][3]), Scalar(0, 255, 0), 3, 8);
				line(copy, Point(lines[2][0], lines[2][1]),
					Point(lines[2][2], lines[2][3]), Scalar(255, 0, 0), 3, 8);
			}
			else {
				for (int i = 0; i < lines.size(); i++) {
					line(copy, Point(lines[i][0], lines[i][1]),
						Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
				}
			}

			change = false;
		}

		/// Show your results
		imshow("Obtained Lines", copy);

		if (cvWaitKey(10) == VK_SPACE) {
			if (lines.size() == 2 || lines.size() == 3)
				break;
			else
				cout << "Number of lines found invalid, please try to change the threshold" << endl;
		}

	}
	destroyWindow("Obtained Lines");


	//guardar imagem dos pointeiros na matriz point
	copy.copyTo(point);



	// Finds the angles of the lines with vertical
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		Point pt1 = Point(l[0], l[1]);
		Point pt2 = Point(l[2], l[3]);

		Point distantPoint;
		if (distancePoint(Point(clockCenter_x, clockCenter_y), pt1) > distancePoint(Point(clockCenter_x, clockCenter_y), pt2))
			distantPoint = Point(pt1.x - clockCenter_x, pt1.y - clockCenter_y);
		else
			distantPoint = Point(pt2.x - clockCenter_x, pt2.y - clockCenter_y);

		double radAngle = atan2(distantPoint.y, distantPoint.x) + atan2(1, 0);
		double degreeAngle = (radAngle * 360) / (2 * CV_PI);
		if (degreeAngle < 0)
			degreeAngle += 360;

		angles.push_back(degreeAngle);
	}

	return;
}

void LineFinder::sayTime(vector<float> angles) {
	///Calculate time
	int horas, minutos, segundos;
	if (angles.size() == 2) {
		//horas
		horas = angles[0] / (360 / 12);
		//minutos
		minutos = angles[1] / (360 / 60);

		std::cout << "time: " << horas << "h " << minutos << "m " << std::endl << std::endl;

	}
	else if (angles.size() == 3) {

		//horas
		horas = angles[0] / (360 / 12);
		//minutos
		minutos = angles[1] / (360 / 60);
		//segundos
		segundos = angles[2] / (360 / 60);

		std::cout << "time: " << horas << "h " << minutos << "m " << segundos << "s " << std::endl << std::endl;
	}

}