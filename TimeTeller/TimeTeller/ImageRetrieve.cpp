#include "ImageRetrieve.h"

bool check_file(string filepath) {
	struct stat buffer;
	return (stat(filepath.c_str(), &buffer) == 0);
}

Mat getImage(string filepath) {
	if(!check_file(filepath)) {
		cerr << "ERROR: File doesn't exist!\n";
		exit(-1);
	}

	Mat img;
	img = imread(filepath);
	if (!img.data)	{
		cerr << "ERROR: Image reading.\n";
		exit(-1);
	}

	return img;
}

/*
int input_choice() {
	Mat img;
	string choice;

	cout << "This program can either use the system's camera or a given file to read the time.\n"
		<< "You may provide the image filepath as an argument, or do it now.\n\n"
		<< "Would you like to provide a file path? (y/n)\n";
	cin >> choice;

	if (choice == "y" || choice == "yes") {
		cout << "File\n";
		return 1;
	}
	else if (choice == "n" || choice == "no") {
		cout << "Camera\n";
		return 2;
	}
	else {
		cout << "aborting...\n";
		exit(-1);
	}

}
Mat getImage(int choice) {
	Mat img;
	return img;

}
*/
