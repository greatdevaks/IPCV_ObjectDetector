#include "stdafx.h"
#include "FaceDetector.h"
#include "FaceDetector_GroundTruthInitializer.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <regex>
#include <sstream>
#include "HoughLines.h"

using namespace cv;
using namespace std;

class HoughTransform
{
public:
	HoughTransform(Mat img_orig, string img_name);
	~HoughTransform();

	void checkLinesInBoundaryBox(Point p0, Point p1, int bounding_rect_size);
	Point2f checkIfTwoLinesIntersect(Point p0, Point p1, Point p2, Point p3);
	bool checkLineIntersectionsInToleranceRegion(vector<Rect> rectRegions, Point2f intersection);
	void countLinesPerBoundaryBox(Point p0, Point p1);

	Mat drawHoughCircles(Mat img_hough_transform, vector<Vec3f> vec_hough_circles);
	Mat drawHoughLinesAndBoundingBoxes(Mat img_hough_transform);

	vector<Rect> tolerance_rectangles;
	vector<Rect> bounded_rectangles;

	vector<Vec4i> hl_present_in_bounding_boxes;
	vector<Vec4i> hl_to_draw;

	vector<int> myLineCountPerBox;
	vector<int> myIntersectionCount;

	void showHoughCircleSpace(string img_name);
	void showHoughLinesSpace(string img_name);

	// hough lines
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > GetLines(int threshold);
	const unsigned int* getAccum(int *w, int *h);

	unsigned int* accum;
	int accum_width;
	int accum_height;
	int img_cols;
	int img_rows;

};

