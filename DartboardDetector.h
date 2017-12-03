#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

class DartboardDetector
{
public:
	DartboardDetector(Mat img_orig, string img_name);
	~DartboardDetector();

	int loadCascadeXML();
	Mat detectDartboardsAndDisplayResult(Mat img_orig, vector<Rect> gtvec_current_img, int img_num);

	String cascade_name;

	CascadeClassifier cascade_dartboards;

	vector<Rect> viola_jones_boxes;
	vector<Rect> hough_transform_boxes;

	//
	vector<Rect> dartboards_found;
};

