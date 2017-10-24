#include "ImageRetrieve.h"

namespace ImageRetrieve {

	bool check_file(string filepath) {
		struct stat buffer;
		return (stat(filepath.c_str(), &buffer) == 0);
	}

	Mat getImage(string filepath) {
		if (!check_file(filepath)) {
			cerr << "ERROR: File doesn't exist!\n";
			if (filepath != DEFAULT_PATH) {
				cout << "do you wish to use the default path? (y/n)\n>" << DEFAULT_PATH << endl;
				string choice;  cin >> choice;
				if (choice == "y" || choice == "yes")
					return getImage();
			}
			exit(-1);
		}
		Mat img = imread(filepath);
		if (!img.data) {
			cerr << "ERROR: Image reading.\n";
			exit(-1);
		}
		return img;
	}
	Mat getImage() {
		Mat img = imread(DEFAULT_PATH);
		if (!img.data) {
			cerr << "ERROR: Image reading.\n";
			exit(-1);
		}
		return img;
	}

	void input_choice(Mat &img) {
		string choice;

		cout << "This program can either use the system camera or a given file to read the time.\n"
			<< "You may provide the image filepath as an argument, or do it now.\n\n"
			<< "Would you like to provide a file path? (y/n)\n";
		cin >> choice;

		if (choice == "y" || choice == "yes") {
			cout << "Please write down the image's filepath:\n";
			cin >> choice;
			img = getImage(choice);
		}
		else if (choice == "n" || choice == "no") {
			getCapture(img);
		}
		else {
			cout << "aborting...\n";
			exit(1);
		}
		return;
	}

	void getCapture(Mat &img) {
		cout << "\nThe system's camera will now be used to take a snapshot.\n"
			<< "Position the clock in front of the camera and then\n"
			<< "with the window focused, press any key to take the snapshot\n";

		VideoCapture capture;
		Mat frame;
		namedWindow("camera", 1);
		bool record_flag = true;


		if (!capture.open(0)) {
			cout << "Capture from camera didn't work" << endl;
			exit(1);
		}

		if (capture.isOpened()) {
			while (record_flag) {
				capture >> frame; // get a new frame from camera
				imshow("camera", frame);
				if (waitKey(30) >= 0)
					record_flag = false;
			}
			
			for (int i = 1; i < 500; i++) {
				string path = DEFAULT_CAPTURE_PATH + "Capture" + to_string(i) + ".bmp";
				if (!check_file(path)) {
					if (imwrite(path, frame))
						cout << "Image capture saved to: " << path << endl;
					else
						cerr << "Error saving image - check if the folder "<< DEFAULT_CAPTURE_PATH << " exists\n";
					i = 500;
				}
			}
			

			destroyWindow("camera");
			img = frame;
		}
		else {
			cerr << "Something as gone wrong while attempting to record\n";
			exit(1);
		}

		return;
	}
}
