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


	//Pedir uma imgem ao utilizador
	if (argc == 2) {
		img = ImageRetrieve::getImage(argv[1]);
	} else {
		ImageRetrieve::input_choice(img);
	} 
	cout << "Image Loaded.\n";
	// resultado
	namedWindow("Original Image", 1);
	imshow("Original Image", img);

	//Detectar circulo na frente do relógio
	cout << "Finding clock's face...\n";
	CircleFinder::findAndShowCircles(img, crop);
	// resultado
	namedWindow("Cropped Image", 1);
	imshow("Cropped Image", crop);

	//Detectar os ponteiros na imagem e obter Angulos.
	vector<float> angles;
	cout << "Finding clock's pointers...\n";
	LineFinder::findPointersAndAngles(crop, point, angles);
	// resultado
	namedWindow("Pointers Image", 1);
	imshow("Pointers Image", point);

	cout << "\nAngle for hours: " << angles[0] << endl;
	cout << "Angle for minutes: " << angles[1] << endl;
	if(angles.size() == 3) cout << "Angle for seconds: " << angles[2] << endl;

	//Passar esses angulos à função sayTime
	LineFinder::sayTime(angles);

	//Time Class
	Time t = Time(); 
	t.setTime(angles);
	cout << "The displayed time is " << t.sayTime() << endl;

	waitKey(0);
	return 0;
}