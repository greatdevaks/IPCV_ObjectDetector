#include <opencv2\highgui\highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

class FaceDetector_GroundTruthInitializer
{
public:
	FaceDetector_GroundTruthInitializer();
	~FaceDetector_GroundTruthInitializer();

	// defining vector containig groundtruth vectors for face detector for each image
	vector<vector<Rect>> groundtruth_faces;

	// defining groundtruth vectors for face detector
	vector<Rect> gtvec_dart0_faces;
	vector<Rect> gtvec_dart1_faces;
	vector<Rect> gtvec_dart2_faces;
	vector<Rect> gtvec_dart3_faces;
	vector<Rect> gtvec_dart4_faces;
	vector<Rect> gtvec_dart5_faces;
	vector<Rect> gtvec_dart6_faces;
	vector<Rect> gtvec_dart7_faces;
	vector<Rect> gtvec_dart8_faces;
	vector<Rect> gtvec_dart9_faces;
	vector<Rect> gtvec_dart10_faces;
	vector<Rect> gtvec_dart11_faces;
	vector<Rect> gtvec_dart12_faces;
	vector<Rect> gtvec_dart13_faces;
	vector<Rect> gtvec_dart14_faces;
	vector<Rect> gtvec_dart15_faces;

};

