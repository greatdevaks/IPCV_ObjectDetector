#pragma once
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

class DartboardColourPatchs
{
public:
	DartboardColourPatchs();
	~DartboardColourPatchs();

	Vec3b colour_beige;
	vector<Vec3b> colour_of_dartboard;
	int colour_tolerance;
	Mat img_clone;


	bool isDartBoardColor(Vec3b color);
	void findDartboards(Mat img);

};

