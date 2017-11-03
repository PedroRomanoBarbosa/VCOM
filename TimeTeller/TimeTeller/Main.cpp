#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include "ImageRetrieve.h"
#include "Time.h"
#include "CircleFinder.h"
#include "LineFinder.h"
using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{
	Mat img, crop, point;

	if (argc == 2) {
		img = ImageRetrieve::getImage(argv[1]);
	} else {
		ImageRetrieve::input_choice(img);
	}

	cout << "Image Loaded.\n";
	namedWindow("Original Image", 1);
	imshow("Original Image", img);

	cout << "Detecting Circles...\n";
	CircleFinder::findAndShowCircles(img, crop);

	namedWindow("Cropped Image", 1);
	imshow("Cropped Image", crop);


	LineFinder::organizeMe(crop, point);



	//TODO: Detectar os ponteiros na imagem. Recomendo o Line Hough transform

	//TODO: Usando as linhas dos ponteiros, descobrir os angulos
	/*
		float angulo_h = ????(img); 
		float angulo_m = ????(img);
	*/

	//TODO: Passar esses angulos à função sayTime
	/*
		Time t = Time(angulo_h, angulo_m);
		cout << "A hora indicada é " << t.sayTime() << endl;
	*/

	waitKey(0);
	return 0;
}