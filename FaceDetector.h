#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

class FaceDetector
{
public:
	FaceDetector(Mat img_orig, string img_name);
	~FaceDetector();

	int loadCascadeXML();
	Mat detectFacesAndDisplayResult(Mat img_orig, vector<Rect> gtvec_current_img, int img_num);

	String cascade_name;
};

