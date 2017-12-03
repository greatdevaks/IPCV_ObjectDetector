#include <opencv2\highgui\highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

class DartboardDetector_GroundTruthInitializer
{
public:
	DartboardDetector_GroundTruthInitializer();
	~DartboardDetector_GroundTruthInitializer();

	// defining vector containig groundtruth vectors for dartboard detector for each image
	vector<vector<Rect>> groundtruth_dartboards;

	// defining groundtruth vectors for dartbaord detector
	vector<Rect> gtvec_dart0_dartboards;
	vector<Rect> gtvec_dart1_dartboards;
	vector<Rect> gtvec_dart2_dartboards;
	vector<Rect> gtvec_dart3_dartboards;
	vector<Rect> gtvec_dart4_dartboards;
	vector<Rect> gtvec_dart5_dartboards;
	vector<Rect> gtvec_dart6_dartboards;
	vector<Rect> gtvec_dart7_dartboards;
	vector<Rect> gtvec_dart8_dartboards;
	vector<Rect> gtvec_dart9_dartboards;
	vector<Rect> gtvec_dart10_dartboards;
	vector<Rect> gtvec_dart11_dartboards;
	vector<Rect> gtvec_dart12_dartboards;
	vector<Rect> gtvec_dart13_dartboards;
	vector<Rect> gtvec_dart14_dartboards;
	vector<Rect> gtvec_dart15_dartboards;
};

