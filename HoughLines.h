
#include <vector>
using namespace std;
class HoughLines
{
public:
	HoughLines();
	virtual ~HoughLines();
public:
	int performHoughLineTransform(unsigned char* img_data, int w, int h);
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > GetLines(int threshold);
	const unsigned int* GetAccu(int *w, int *h);
public:
	// declaring the accumulator parameters
	unsigned int* accum;
	int accum_width;
	int accum_height;
	int _img_w;
	int _img_h;
};

