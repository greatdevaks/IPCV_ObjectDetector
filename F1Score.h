#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

class F1Score {
public:
	F1Score();
	~F1Score();

	float tp_count;
	float fp_count;
	float fn_count;

	float calculatePrecision(float tp_count, float fp_count);
	float calculateRecall(float tp_count, float fn_count);
	float calculateF1Score(float precision, float recall);
	bool calculateIntersectionAreaBetweenGTBoxAndDetectedBox(Rect ground_truth_box, Rect detected_box);
};

