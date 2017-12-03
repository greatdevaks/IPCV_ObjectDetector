#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>

#include <sstream>

#include "stdafx.h"
#include "DartboardDetector.h"
#include "DartboardDetector_GroundTruthInitializer.h"
#include "F1Score.h"
#include "HoughTransform.h"
#include <regex>


using namespace cv;
using namespace std;


DartboardDetector::DartboardDetector(Mat img_orig, string img_name)
{
	// getting the image number from image name
	string img_num_str = regex_replace(img_name, regex(R"([^0-9])"), "");
	stringstream geek(img_num_str);
	int img_num;
	geek >> img_num;

	// initializing the ground truths for dartboard detector
	DartboardDetector_GroundTruthInitializer dartboards_gti;

	// fetching ground truths for the current image
	vector<Rect> gtvec_current_img = dartboards_gti.groundtruth_dartboards[img_num];

	// viola jones detection
	cascade_name = "dartboard_detector_cascade.xml";
	loadCascadeXML();
	Mat img_res_vj = detectDartboardsAndDisplayResult(img_orig, gtvec_current_img, img_num);

	// saving the result image of viola jones detector
	imwrite("viola_jones.jpg", img_res_vj);

	// hough transform detection
	HoughTransform ht(img_orig, img_name);

	// drawing results merged from viola-jones and hough transform
	hough_transform_boxes = ht.bounded_rectangles;
	
	vector<Rect> detections;
	if (viola_jones_boxes.size() != 0 && hough_transform_boxes.size() != 0) {
		for (int i = 0; i < viola_jones_boxes.size(); i++) {
			for (int j = 0; j < hough_transform_boxes.size(); j++) {
				if ((viola_jones_boxes[i] & hough_transform_boxes[j]).area() == 0) {
					if (find(detections.begin(), detections.end(), viola_jones_boxes[i]) != detections.end()) {
						// rectangle is already there
					}
					else {
						detections.push_back(viola_jones_boxes[i]);
					}
					if (find(detections.begin(), detections.end(), hough_transform_boxes[j]) != detections.end()) {
						// rectangle is already there
					}
					else {
						detections.push_back(hough_transform_boxes[j]);
					}
				}
				else {
					if (viola_jones_boxes[i].area() > hough_transform_boxes[j].area()) {
						if (find(detections.begin(), detections.end(), viola_jones_boxes[i]) != detections.end()) {
							// rectangle is already there
						}
						else {
							detections.push_back(viola_jones_boxes[i]);
						}
						if (find(detections.begin(), detections.end(), hough_transform_boxes[j]) != detections.end()) {
							detections.erase(remove(detections.begin(), detections.end(), hough_transform_boxes[j]), detections.end());
						}
					}
					else {
						if (find(detections.begin(), detections.end(), hough_transform_boxes[j]) != detections.end()) {
							// rectangle is already there
						}
						else {
							detections.push_back(hough_transform_boxes[j]);
						}
						if (find(detections.begin(), detections.end(), viola_jones_boxes[i]) != detections.end()) {
							detections.erase(remove(detections.begin(), detections.end(), viola_jones_boxes[i]), detections.end());
						}
					}
				}
			}
		}
	}
	else if (viola_jones_boxes.size() == 0 && hough_transform_boxes.size() != 0) {
		for (int i = 0; i < hough_transform_boxes.size(); i++) {
			detections.push_back(hough_transform_boxes[i]);
		}
	}
	else if (viola_jones_boxes.size() != 0 && hough_transform_boxes.size() == 0) {
		for (int i = 0; i < viola_jones_boxes.size(); i++) {
			detections.push_back(viola_jones_boxes[i]);
		}
	}
	else if (viola_jones_boxes.size() == 0 && hough_transform_boxes.size() == 0) {
		for (int i = 0; i < hough_transform_boxes.size(); i++) {
			cout << "No dartboard detected." << endl;
		}
	}
	
	if (detections.size() != 0) {
		Mat img_merged = img_orig.clone();
		for (size_t i = 0; i < detections.size(); i++)
		{
			rectangle(img_merged, detections[i], Scalar(0, 69, 255), 2);
		}
		cout << detections.size() << " dartboard(s) predicted." << endl;
		imwrite("merged.jpg", img_merged);
	}
	
	F1Score f1s;
	// calculating the F1Score, Precision and Recall
	for (int i = 0; i < detections.size(); i++)
	{
		// calculating area interesection between detected box and ground truth boxes
		for (int j = 0; j < gtvec_current_img.size(); j++) {
			// check if the the area of intersection is greater than threshold value (0.5)
			if (f1s.calculateIntersectionAreaBetweenGTBoxAndDetectedBox(gtvec_current_img[j], detections[i])) {
				f1s.tp_count++;
			}
		}
	}

	f1s.fp_count = detections.size() - f1s.tp_count;
	f1s.fn_count = gtvec_current_img.size() - f1s.tp_count;

	f1s.calculateF1Score(f1s.calculatePrecision(f1s.tp_count, f1s.fp_count), f1s.calculateRecall(f1s.tp_count, f1s.fn_count));

}


DartboardDetector::~DartboardDetector()
{
}

int DartboardDetector::loadCascadeXML() {
	if (!cascade_dartboards.load(cascade_name)) {
		cout << "--(!) Error loading dartboard_detector_cascade.xml" << endl;
		return -1;
	}
}

Mat DartboardDetector::detectDartboardsAndDisplayResult(Mat img_orig, vector<Rect> gtvec_current_img, int img_num) {

	//vector of rectangles containing the dartboards found by running the dartboard detector
	/*vector<Rect> dartboards_found;*/

	// creating clone of img_orig
	Mat img_orig_clone = img_orig.clone();

	// grayscale image of img_orig
	Mat img_gray;

	// preparing image by turning it into grayscale and normalising the lighting
	// turning to grayscale
	cvtColor(img_orig_clone, img_gray, CV_BGR2GRAY);
	// normalizing the image
	equalizeHist(img_gray, img_gray);

	// performing the Viola-Jones Object Detection approach
	cascade_dartboards.detectMultiScale(img_gray, dartboards_found, 1.1, 1, 0 | CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500, 500));

	// drawing box around dartboards found
	for (int i = 0; i < dartboards_found.size(); i++)
	{
		// drawing box around dartboards found by dartboard detector
		Rect detected_box = Rect(dartboards_found[i].x, dartboards_found[i].y, dartboards_found[i].width, dartboards_found[i].height);
		viola_jones_boxes.push_back(detected_box);
		rectangle(img_orig_clone, detected_box, Scalar(0, 255, 0), 2);
	}

	return img_orig_clone;
}

