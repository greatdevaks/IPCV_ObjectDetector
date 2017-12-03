#pragma once
#include "stdafx.h"
#include "HoughTransform.h"

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>


using namespace std;
using namespace cv;

HoughTransform::HoughTransform(Mat img_orig, string img_name)
{
	// convert the img_orig to grayscale
	Mat img_gray;
	cvtColor(img_orig, img_gray, CV_BGR2GRAY);

	// apply gaussian blur to the grayscale image
	GaussianBlur(img_gray, img_gray, Size(9, 9), 2, 2);

	// define a vector of three float co-ordinates to store the hough circles that will be generated using HoughCircle function
	vector<Vec3f> vec_hough_circles;

	// generate hough circles using HoughCircle function
	HoughCircles(img_gray, vec_hough_circles, CV_HOUGH_GRADIENT, 1, img_gray.rows / 8, 200, 100, 0, 0);

	// display the hough circles over the original image's clone
	Mat img_hough_circles;
	img_hough_circles = img_orig.clone();
	Mat img_hough_transform = drawHoughCircles(img_hough_circles, vec_hough_circles);

	// initialize line intersection count and line count per box to zero
	for (int i = 0; i < tolerance_rectangles.size(); i++) {
		myIntersectionCount.push_back(0);
		myLineCountPerBox.push_back(0);
	}

	// define a vector of three float co-ordinates to store the hough circles that will be generated using HoughCircle function
	vector<Vec4i> vec_hough_lines;

	// generate canny image using img_orig
	Mat img_canny;
	Canny(img_orig, img_canny, 50, 200, 3);

	// generate hough circles using HoughCircle function
	HoughLinesP(img_canny, vec_hough_lines, 1, CV_PI / 180, 50, 50, 10);

	// find hough lines present in the bounding rectangles and push them to hl_present_in_bounding_boxes vector
	for (int i = 0; i < vec_hough_lines.size(); i++) {
		Vec4i line_coordinates = vec_hough_lines[i];
		checkLinesInBoundaryBox(Point(line_coordinates[0], line_coordinates[1]), Point(line_coordinates[2], line_coordinates[3]), bounded_rectangles.size());
	}

	// check if two lines intersect within tolerance region and if yes then psuh them to hl_to_draw
	for (int i = 0; i < hl_present_in_bounding_boxes.size(); i++) {

		// initialize line 1
		Vec4i l1 = hl_present_in_bounding_boxes[i];

		for (int j = 0; j < hl_present_in_bounding_boxes.size(), j != i; j++) {

			// initialize line 2
			Vec4i l2 = hl_present_in_bounding_boxes[j];

			Point2f pi = checkIfTwoLinesIntersect(Point(l1[0], l1[1]), Point(l1[2], l1[3]), Point(l2[0], l2[1]), Point(l2[2], l2[3]));

			if (pi.x != -1 && pi.y != -1) {
				if (checkLineIntersectionsInToleranceRegion(tolerance_rectangles, pi)) {
					if (find(hl_to_draw.begin(), hl_to_draw.end(), l1) != hl_to_draw.end()) {

					}
					else {
						hl_to_draw.push_back(l1);
					}
					if (find(hl_to_draw.begin(), hl_to_draw.end(), l2) != hl_to_draw.end()) {

					}
					else {
						hl_to_draw.push_back(l2);
					}
				}
			}
		}
	}

	// count the number of lines in the bounding boxes
	for (int i = 0; i < hl_to_draw.size(); i++) {
		Vec4i l = hl_to_draw[i];
		countLinesPerBoundaryBox(Point(l[0], l[1]), Point(l[2], l[3]));
	}

	// drawing the hough lines and the tolerance and bunding rectangles
	img_hough_transform = drawHoughLinesAndBoundingBoxes(img_hough_transform);

	imwrite("hough_transform.jpg", img_hough_transform);

	Mat hs_clone = img_orig.clone();
	showHoughCircleSpace(img_name);
	//showHoughLinesSpace(img_name);
}


HoughTransform::~HoughTransform()
{
}

Mat HoughTransform::drawHoughCircles(Mat img_hough_transform, vector<Vec3f> vec_hough_circles) {

	// draw hough circles on the image
	for (int i = 0; i < vec_hough_circles.size(); i++) {
		Point center(cvRound(vec_hough_circles[i][0]), cvRound(vec_hough_circles[i][1]));
		int radius = cvRound(vec_hough_circles[i][2]);
		circle(img_hough_transform, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(img_hough_transform, center, radius, Scalar(0, 0, 255), 3, 8, 0);

		// specifying co-ordinates for the tolerance rectangle
		Rect tol_rect;
		tol_rect.x = center.x - 5;
		tol_rect.y = center.y - 5;
		tol_rect.width = 10;
		tol_rect.height = 10;

		// pushing the tolerance rectangle to tolerance rectangle vector
		tolerance_rectangles.push_back(tol_rect);

		// specifying co-ordinates for the bounding rectangle
		Rect bound_rect;
		bound_rect.x = center.x - radius;
		bound_rect.y = center.y - radius;
		bound_rect.width = 2 * radius;
		bound_rect.height = 2 * radius;

		// pushing the bounded rectangle to bounded rectangle vector
		bounded_rectangles.push_back(bound_rect);

	}

	return img_hough_transform;

}

Mat HoughTransform::drawHoughLinesAndBoundingBoxes(Mat img_hough_transform) {

	// drawing hough lines
	for (size_t i = 0; i < hl_to_draw.size(); i++)
	{
		Vec4i l = hl_to_draw[i];
		line(img_hough_transform, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
	}

	// draw tolerance rectabgles and bounding rectangles
	for (int i = 0; i < tolerance_rectangles.size(); i++) {
		rectangle(img_hough_transform, tolerance_rectangles[i], Scalar(255, 0, 0));
		rectangle(img_hough_transform, bounded_rectangles[i], Scalar(120, 255, 0), 2);
	}

	return img_hough_transform;
}

void HoughTransform::checkLinesInBoundaryBox(Point p0, Point p1, int bounding_rect_size) {

	Vec4i line_to_return;
	for (int i = 0; i < bounding_rect_size; i++) {
		if (bounded_rectangles[i].contains(p0) && bounded_rectangles[i].contains(p1)) {
			line_to_return[0] = p0.x;
			line_to_return[1] = p0.y;
			line_to_return[2] = p1.x;
			line_to_return[3] = p1.y;
			hl_present_in_bounding_boxes.push_back(line_to_return);
		}
	}

}

Point2f HoughTransform::checkIfTwoLinesIntersect(Point p0, Point p1, Point p2, Point p3) {

	float A1, A2, B1, B2, C1, C2;
	A1 = p1.y - p0.y;
	B1 = p0.x - p1.x;
	C1 = (A1 * p0.x) + (B1 * p0.y);

	A2 = p3.y - p2.y;
	B2 = p2.x - p3.x;
	C2 = (A2 * p2.x) + (B2 * p2.y);

	float xi, yi, denominator;

	denominator = (A1 * B2) - (A2 * B1);

	xi = ((B2 * C1) - (B1 * C2)) / denominator;
	yi = ((A1 * C2) - (A2 * C1)) / denominator;

	Vec4i l1, l2;

	if (isinf(xi) || isinf(yi) || isnan(xi) || isnan(yi)) {
		return Point2f(-1, -1);
	}
	else {
		return Point2f(xi, yi);
	}
}

bool HoughTransform::checkLineIntersectionsInToleranceRegion(vector<Rect> rectRegions, Point2f intersection) {
	bool found = false;
	for (int i = 0; i < rectRegions.size(); i++) {
		if (rectRegions[i].contains(intersection)) {
			myIntersectionCount[i]++;
			found = true;
		}
	}
	return found;
}

void HoughTransform::countLinesPerBoundaryBox(Point p0, Point p1) {

	for (int i = 0; i < bounded_rectangles.size(); i++) {
		if (bounded_rectangles[i].contains(p0) && bounded_rectangles[i].contains(p1)) {
			myLineCountPerBox[i]++;
		}
	}

}

void HoughTransform::showHoughCircleSpace(string img_name) {

	int radius = 124;


	IplImage* img = cvLoadImage(img_name.c_str(), 0);			// The original image
	IplImage* edges = cvCreateImage(cvGetSize(img), 32, 1);		// Only edges
	IplImage* img_hough_space = cvCreateImage(cvGetSize(img), 8, 1);	// The accumulator cells

	// Ensure the accumulator cells are all zeroes out
	cvZero(img_hough_space);

	// Detect edges in the image
	cvSobel(img, edges, 1, 1);



	// Uncomment to save edges to a file
	//cvSaveImage("C:\\circle_edges.jpg", edges);

	// Loop through each pixel
	for (int x = 0; x < img->width; x++)
	{
		for (int y = 0; y < img->height; y++)
		{
			// Check if the current pixel is an edge
			int value = cvGetReal2D(edges, y, x);
			if (value == 0) continue;

			// If it is an edge, generate its circle in the parameter space
			for (int theta = 0; theta < 360; theta++)
			{
				int a = x + radius*cos(theta*3.1412 / 180);
				int b = y + radius*sin(theta*3.1412 / 180);

				// Outside the image? Skip onto the next pixel
				if (a < 0 || a >= img->width || b < 0 || b >= img->height) continue;

				value = cvGetReal2D(img_hough_space, b, a);
				cvSetReal2D(img_hough_space, b, a, value + 1);
			}
		}
	}



	// Uncomment to save to a file
	cvSaveImage("hough_space_circle.jpg", img_hough_space);
	cvWaitKey(0);
}
//
//void HoughTransform::showHoughLinesSpace(string img_name) {
//	int threshold = 175;
//	const char* CW_IMG_ORIGINAL = "Result";
//	const char* CW_IMG_EDGE = "Canny Edge Detection";
//	const char* CW_ACCUMULATOR = "Accumulator";
//
//
//
//
//	cv::Mat img_edge;
//	cv::Mat img_blur;
//
//	cv::Mat img_ori = cv::imread(img_name, 1);
//	cv::blur(img_ori, img_blur, cv::Size(5, 5));
//	cv::Canny(img_blur, img_edge, 100, 150, 3);
//
//	int w = img_edge.cols;
//	int h = img_edge.rows;
//
//	//Transform
//	_accu = 0; _accu_w = 0; _accu_h		= 0; _img_w = 0; _img_h = 0;
//
//	unsigned char* img_data = img_edge.data;
//	_img_w = w;
//	_img_h = h;
//
//	//Create the accu
//	double hough_h = ((sqrt(2.0) * (double)(h>w ? h : w)) / 2.0);
//	_accu_h = hough_h * 2.0; // -r -> +r
//	_accu_w = 180;
//
//	_accu = (unsigned int*)calloc(_accu_h * _accu_w, sizeof(unsigned int));
//
//	double center_x = w / 2;
//	double center_y = h / 2;
//
//
//	for (int y = 0; y<h; y++)
//	{
//		for (int x = 0; x<w; x++)
//		{
//			if (img_data[(y*w) + x] > 250)
//			{
//				for (int t = 0; t<180; t++)
//				{
//					double r = (((double)x - center_x) * cos((double)t * 0.017453293f)) + (((double)y - center_y) * sin((double)t * 0.017453293f));
//					_accu[(int)((round(r + hough_h) * 180.0)) + t]++;
//				}
//			}
//		}
//	}
//
//
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
//		std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines = GetLines(threshold);
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
//		const unsigned int* accu = GetAccu(&aw, &ah);
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
//	
//		imwrite("hough_lines_space.jpg", img_accu);
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
//std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > HoughTransform::GetLines(int threshold)
//{
//	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines;
//
//	if (_accu == 0)
//		return lines;
//
//	for (int r = 0; r<_accu_h; r++)
//	{
//		for (int t = 0; t<_accu_w; t++)
//		{
//			if ((int)_accu[(r*_accu_w) + t] >= threshold)
//			{
//				//Is this point a local maxima (9x9)
//				int max = _accu[(r*_accu_w) + t];
//				for (int ly = -4; ly <= 4; ly++)
//				{
//					for (int lx = -4; lx <= 4; lx++)
//					{
//						if ((ly + r >= 0 && ly + r<_accu_h) && (lx + t >= 0 && lx + t<_accu_w))
//						{
//							if ((int)_accu[((r + ly)*_accu_w) + (t + lx)] > max)
//							{
//								max = _accu[((r + ly)*_accu_w) + (t + lx)];
//								ly = lx = 5;
//							}
//						}
//					}
//				}
//				if (max >(int)_accu[(r*_accu_w) + t])
//					continue;
//
//
//				int x1, y1, x2, y2;
//				x1 = y1 = x2 = y2 = 0;
//
//				if (t >= 45 && t <= 135)
//				{
//					//y = (r - x cos(t)) / sin(t)
//					x1 = 0;
//					y1 = ((double)(r - (_accu_h / 2)) - ((x1 - (_img_w / 2)) * cos(t * 0.017453293f))) / sin(t * 0.017453293f) + (_img_h / 2);
//					x2 = _img_w - 0;
//					y2 = ((double)(r - (_accu_h / 2)) - ((x2 - (_img_w / 2)) * cos(t * 0.017453293f))) / sin(t * 0.017453293f) + (_img_h / 2);
//				}
//				else
//				{
//					//x = (r - y sin(t)) / cos(t);
//					y1 = 0;
//					x1 = ((double)(r - (_accu_h / 2)) - ((y1 - (_img_h / 2)) * sin(t * 0.017453293f))) / cos(t * 0.017453293f) + (_img_w / 2);
//					y2 = _img_h - 0;
//					x2 = ((double)(r - (_accu_h / 2)) - ((y2 - (_img_h / 2)) * sin(t * 0.017453293f))) / cos(t * 0.017453293f) + (_img_w / 2);
//				}
//
//				lines.push_back(std::pair< std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(x1, y1), std::pair<int, int>(x2, y2)));
//
//			}
//		}
//	}
//
//	std::cout << "lines: " << lines.size() << " " << threshold << std::endl;
//	return lines;
//}
//
//const unsigned int* HoughTransform::GetAccu(int *w, int *h)
//{
//	*w = _accu_w;
//	*h = _accu_h;
//
//	return _accu;
//}
