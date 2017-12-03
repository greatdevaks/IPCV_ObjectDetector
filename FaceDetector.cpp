#pragma once
#include "stdafx.h"
#include "FaceDetector.h"
#include "FaceDetector_GroundTruthInitializer.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include "F1Score.h"
#include <regex>
#include <sstream>

using namespace cv;
using namespace std;

CascadeClassifier cascade_faces;

FaceDetector::FaceDetector(Mat img_orig, string img_name)
{
	// getting the image number from image name
	string img_num_str = regex_replace(img_name, regex(R"([^0-9])"), "");
	stringstream geek(img_num_str);
	int img_num;
	geek >> img_num;

	// initializing the ground truths for face detector
	FaceDetector_GroundTruthInitializer fd_gti;

	// fetching ground truths for the current image
	vector<Rect> gtvec_current_img = fd_gti.groundtruth_faces[img_num];

	cascade_name = "face_detector_cascade.xml";
	loadCascadeXML();
	Mat img_res = detectFacesAndDisplayResult(img_orig, gtvec_current_img, img_num);

	// saving the result image
	imwrite("detected.jpg", img_res);
	cout << "Result image is saved as detected.jpg." << endl;
}


FaceDetector::~FaceDetector()
{
}

int FaceDetector::loadCascadeXML() {
	if (!cascade_faces.load(cascade_name)) {
		cout << "--(!) Error loading face_detector_cascade.xml" << endl;
		return -1;
	}
}

Mat FaceDetector::detectFacesAndDisplayResult(Mat img_orig, vector<Rect> gtvec_current_img, int img_num) {
	
	//vector of rectangles containing the faces found by running the face detector
	vector<Rect> faces_found;

	// grayscale image of img_orig
	Mat img_gray;

	// preparing image by turning it into grayscale and normalising the lighting
	// turning to grayscale
	cvtColor(img_orig, img_gray, CV_BGR2GRAY);
	// normalizing the image
	equalizeHist(img_gray, img_gray);

	// performing the Viola-Jones Object Detection approach
	cascade_faces.detectMultiScale(img_gray, faces_found, 1.1, 1, 0 | CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500, 500));

	// printing the number of faces found
	cout << "Number of face(s) predicted:" << faces_found.size() << std::endl;

	// initializing parameters for calculating F1Score
	// tp_count = 0, fp_count = 0, fn_count = 0
	F1Score f1s;

	for (int i = 0; i < gtvec_current_img.size(); i++) {
		rectangle(img_orig, gtvec_current_img[i], Scalar(255, 0, 0), 2);
	}

	// drawing box around faces found and comparing with the ground truth to calculate the F1Sore
	for (int i = 0; i < faces_found.size(); i++)
	{
		// drawing box around faces found by face detector
		Rect detected_box = Rect(faces_found[i].x, faces_found[i].y, faces_found[i].width, faces_found[i].height);
		rectangle(img_orig, detected_box, Scalar(0, 255, 0), 2);

		// calculating area interesection between detected box and ground truth boxes
		for (int j = 0; j < gtvec_current_img.size(); j++) {
			// check if the the area of intersection is greater than threshold value (0.5)
			if (f1s.calculateIntersectionAreaBetweenGTBoxAndDetectedBox(gtvec_current_img[j], detected_box)) {
				f1s.tp_count++;
			}
		}
	}

	f1s.fp_count = faces_found.size() - f1s.tp_count;
	f1s.fn_count = gtvec_current_img.size() - f1s.tp_count;

	f1s.calculateF1Score(f1s.calculatePrecision(f1s.tp_count, f1s.fp_count), f1s.calculateRecall(f1s.tp_count, f1s.fn_count));

	return img_orig;
}
