#include "ImageRetrieve.h"

bool check_file(string filepath) {
	struct stat buffer;
	return (stat(filepath.c_str(), &buffer) == 0);
}

Mat getImage(string filepath) {
	if(!check_file(filepath)) {
		cerr << "ERROR: File doesn't exist!\n";
		if (filepath != DEFAULT_PATH) {
			cout << "do you wish to use the default path? (y/n)\n>"<< DEFAULT_PATH << endl;
			string choice;  cin >> choice;
			if (choice == "y" || choice == "yes")
				return getImage();		
		}
		exit(-1);
	}
	Mat img = imread(filepath);
	if (!img.data)	{
		cerr << "ERROR: Image reading.\n";
		exit(-1);
	}
	return img;
}
Mat getImage() {
	Mat img= imread(DEFAULT_PATH);
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
		cout << "Camera\n";
		exit(1);
	}
	else {
		cout << "aborting...\n";
		exit(1);
	}
	return;
} 