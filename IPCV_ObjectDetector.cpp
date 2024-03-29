#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <stdio.h>
#include <map>
#include <iostream>


#include "stdafx.h"
#include "FaceDetector.h"
#include "DartboardDetector.h"

using namespace cv;
using namespace std;

void wrongInputOption();

void runFaceDetector(Mat img_orig, string img_name);

void runDartboardDetector(Mat img_orig, string img_name);

int main(int argc, const char** argv) {

	// checking if command line argument has been passed or not
	if (argv[1]) {

		// initializing img_name using command line argument
		string img_name = argv[1];

		// initializing the original image
		Mat img_orig = imread(img_name, CV_LOAD_IMAGE_UNCHANGED);

		cout << "Hello World!" << endl;
		cout << "Welcome to the OpenCV Object Detector." << endl;
		cout << "Authors:" << endl;
		cout << "1.Anmol Krishan Sachdeva - as17611" << endl;
		cout << "2.James Thompsett - jt17982" << endl << endl;
		cout << "Choose a task to perform from the options given below:" << endl;
		cout << "1. Run Face Detector on " << img_name << endl;
		cout << "2. Run Dartboard Detector on " << img_name << endl;

		// taking the option as input
		int option;
		cin >> option;

		switch (option) {
		case 1:
			// runs the face detector
			runFaceDetector(img_orig, img_name);
			break;
		case 2:
			// runs the dartboard detector
			runDartboardDetector(img_orig, img_name);
			break;
		default:
			wrongInputOption();
		}
		getchar();
	}
	else {
		cout << "No command line argument passed." << endl;
		cout << "Hit Enter key to exit." << endl;
		getchar();
		exit(1);
	}
	
	getchar();
	return 0;
}

void runFaceDetector(Mat img_orig, string img_name) {
	FaceDetector fd(img_orig, img_name);
}

void runDartboardDetector(Mat img_orig, string img_name) {
	DartboardDetector fd(img_orig, img_name);
}

void wrongInputOption() {
	cout << "Wrong input provided." << endl;
	cout << "Hit Enter key to exit." << endl;
}

//#include "Hough_Circle.h"

//here goes hough lines space
//#include "hough.h"
//
//std::string img_path;
//int threshold = 0;
//
//const char* CW_IMG_ORIGINAL = "Result";
//const char* CW_IMG_EDGE = "Canny Edge Detection";
//const char* CW_ACCUMULATOR = "Accumulator";
//
//void doTransform(std::string, int threshold);
//
//int main(int argc, const char** argv) {
//	
//	img_path = argv[1];
//
//	cv::namedWindow(CW_IMG_ORIGINAL, cv::WINDOW_AUTOSIZE);
//	cv::namedWindow(CW_IMG_EDGE, cv::WINDOW_AUTOSIZE);
//	cv::namedWindow(CW_ACCUMULATOR, cv::WINDOW_AUTOSIZE);
//
//	cvMoveWindow(CW_IMG_ORIGINAL, 10, 10);
//	cvMoveWindow(CW_IMG_EDGE, 680, 10);
//	cvMoveWindow(CW_ACCUMULATOR, 1350, 10);
//
//	doTransform(img_path, threshold);
//
//	return 0;
//}
//
//
//
//void doTransform(std::string file_path, int threshold)
//{
//	cv::Mat img_edge;
//	cv::Mat img_blur;
//
//	cv::Mat img_ori = cv::imread(file_path, 1);
//	cv::blur(img_ori, img_blur, cv::Size(5, 5));
//	cv::Canny(img_blur, img_edge, 100, 150, 3);
//
//	int w = img_edge.cols;
//	int h = img_edge.rows;
//
//	//performHoughLineTransform
//	keymolen::Hough hough;
//	hough.performHoughLineTransform(img_edge.data, w, h);
//
//
//
//	if (threshold == 0)
//		threshold = w>h ? w / 4 : h / 4;
//
//	while (1)
//	{
//		cv::Mat img_res = img_ori.clone();
//
//		//Search the accumulator
//		std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines = hough.GetLines(threshold);
//
//		//Draw the results
//		std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > >::iterator it;
//		for (it = lines.begin(); it != lines.end(); it++)
//		{
//			cv::line(img_res, cv::Point(it->first.first, it->first.second), cv::Point(it->second.first, it->second.second), cv::Scalar(0, 0, 255), 2, 8);
//		}
//
//		//Visualize all
//		int aw, ah, maxa;
//		aw = ah = maxa = 0;
//		const unsigned int* accu = hough.getAccum(&aw, &ah);
//
//		for (int p = 0; p<(ah*aw); p++)
//		{
//			if ((int)accu[p] > maxa)
//				maxa = accu[p];
//		}
//		double contrast = 1.0;
//		double coef = 255.0 / (double)maxa * contrast;
//
//		cv::Mat img_accu(ah, aw, CV_8UC3);
//		for (int p = 0; p<(ah*aw); p++)
//		{
//			unsigned char c = (double)accu[p] * coef < 255.0 ? (double)accu[p] * coef : 255.0;
//			img_accu.data[(p * 3) + 0] = 255;
//			img_accu.data[(p * 3) + 1] = 255 - c;
//			img_accu.data[(p * 3) + 2] = 255 - c;
//		}
//
//
//		cv::imshow(CW_IMG_ORIGINAL, img_res);
//		cv::imshow(CW_IMG_EDGE, img_edge);
//		cv::imshow(CW_ACCUMULATOR, img_accu);
//
//		char c = cv::waitKey(360000);
//		if (c == '+')
//			threshold += 5;
//		if (c == '-')
//			threshold -= 5;
//		if (c == 27)
//			break;
//	}
//}
//

////here goes hough circle space
//int main()
//{
//	// We predefine a radius, so our parameter space is 2D
//	int radius = 24;
//
//	IplImage* img = cvLoadImage("img.png", 0);			// The original image
//	IplImage* edges = cvCreateImage(cvGetSize(img), 32, 1);		// Only edges
//	IplImage* imgHough = cvCreateImage(cvGetSize(img), 8, 1);	// The accumulator cells
//
//																// Ensure the accumulator cells are all zeroes out
//	cvZero(imgHough);
//
//	// Detect edges in the image
//	cvSobel(img, edges, 1, 1);
//
//	// Display the detected edges
//	cvNamedWindow("test1");
//	cvShowImage("test1", edges);
//
//	// Uncomment to save edges to a file
//	//cvSaveImage("C:\\circle_edges.jpg", edges);
//
//	// Loop through each pixel
//	for (int x = 0; x<img->width; x++)
//	{
//		for (int y = 0; y<img->height; y++)
//		{
//			// Check if the current pixel is an edge
//			int value = cvGetReal2D(edges, y, x);
//			if (value == 0) continue;
//
//			// If it is an edge, generate its circle in the parameter space
//			for (int theta = 0; theta<360; theta++)
//			{
//				int a = x + radius*cos(theta*3.1412 / 180);
//				int b = y + radius*sin(theta*3.1412 / 180);
//
//				// Outside the image? Skip onto the next pixel
//				if (a<0 || a >= img->width || b<0 || b >= img->height) continue;
//
//				value = cvGetReal2D(imgHough, b, a);
//				cvSetReal2D(imgHough, b, a, value + 1);
//			}
//		}
//	}
//
//	// Display the parameter space
//	cvNamedWindow("test");
//	cvShowImage("test", imgHough);
//
//	// Uncomment to save to a file
//	//cvSaveImage("C:\\hough_circle.jpg", imgHough);
//	cvWaitKey(0);
//
//	return 0;
//}
