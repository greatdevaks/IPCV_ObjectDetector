
#include <vector>

class HoughLines
{
public:
	HoughLines();
	virtual ~HoughLines();
public:
	int Transform(unsigned char* img_data, int w, int h);
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > GetLines(int threshold);
	const unsigned int* GetAccu(int *w, int *h);
public:
	unsigned int* _accu;
	int _accu_w;
	int _accu_h;
	int _img_w;
	int _img_h;
};

