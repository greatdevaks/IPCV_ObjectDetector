
#include <vector>
using namespace std;
class HoughLines
{
public:
	HoughLines();
	virtual ~HoughLines();
public:
	int performHoughLineTransform(unsigned char* img_data, int w, int h);
	vector<pair<pair<int, int>, pair<int, int> > > GetLines(int threshold);
	const unsigned int* getAccum(int *w, int *h);
public:
	// declaring the accumulator parameters
	unsigned int* accum;
	int accum_width;
	int accum_height;
	int img_cols;
	int img_rows;
};

