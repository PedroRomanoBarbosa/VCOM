#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include "Time.h"
using namespace std;
using namespace cv;

int main_TimeTester()
{
	Time t = Time();

	for (float i = -35; i < 35; i++) {
		t.setTime(i, i);
		cout << i << "," << i << " - " << t.sayTime() << endl;
	}

	cout << "======================" << endl;

	for (float i = -365; i < -355; i++) {
		t.setTime(i, i);
		cout << i << "," << i << " - " << t.sayTime() << endl;
	}

	cout << "======================" << endl;

	for (float i = 355; i < 365; i++) {
		t.setTime(i, i);
		cout << i << "," << i << " - " << t.sayTime() << endl;
	}	


	waitKey(0);
	return 0;
}