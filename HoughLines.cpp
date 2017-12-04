#include "stdafx.h"
#include "HoughLines.h"
#include <cmath>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;
//defining the constatnt for degree to radian conversion
#define CONVERT_DEGREE_TO_RADIAN 0.017453293f

HoughLines::HoughLines() 
{
	// initializing the accumulator parameters like width, height and the accumumulator itself
	accum = 0;
	accum_width = 0;
	accum_height = 0;
	img_cols = 0;
	img_rows = 0;
}

HoughLines::~HoughLines() {
	if (accum)
		free(accum);
}


int HoughLines::performHoughLineTransform(unsigned char* img_data, int w, int h)
{
	img_cols = w;
	img_rows = h;

	//Create the accu
	double hough_h = ((sqrt(2.0) * (double)(h>w ? h : w)) / 2.0);
	accum_height = hough_h * 2.0; // -r -> +r
	accum_width = 180;

	accum = (unsigned int*)calloc(accum_height * accum_width, sizeof(unsigned int));

	double center_x = w / 2;
	double center_y = h / 2;


	for (int y = 0; y<h; y++)
	{
		for (int x = 0; x<w; x++)
		{
			if (img_data[(y*w) + x] > 250)
			{
				for (int t = 0; t<180; t++)
				{
					double r = (((double)x - center_x) * cos((double)t * CONVERT_DEGREE_TO_RADIAN)) + (((double)y - center_y) * sin((double)t * CONVERT_DEGREE_TO_RADIAN));
					accum[(int)((round(r + hough_h) * 180.0)) + t]++;
				}
			}
		}
	}

	return 0;
}

std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > HoughLines::GetLines(int threshold)
{
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines;

	if (accum == 0)
		return lines;

	for (int r = 0; r<accum_height; r++)
	{
		for (int t = 0; t<accum_width; t++)
		{
			if ((int)accum[(r*accum_width) + t] >= threshold)
			{
				//Is this point a local maxima (9x9)
				int max = accum[(r*accum_width) + t];
				for (int ly = -4; ly <= 4; ly++)
				{
					for (int lx = -4; lx <= 4; lx++)
					{
						if ((ly + r >= 0 && ly + r<accum_height) && (lx + t >= 0 && lx + t<accum_width))
						{
							if ((int)accum[((r + ly)*accum_width) + (t + lx)] > max)
							{
								max = accum[((r + ly)*accum_width) + (t + lx)];
								ly = lx = 5;
							}
						}
					}
				}
				if (max >(int)accum[(r*accum_width) + t])
					continue;


				int x1, y1, x2, y2;
				x1 = y1 = x2 = y2 = 0;

				if (t >= 45 && t <= 135)
				{
					//y = (r - x cos(t)) / sin(t)
					x1 = 0;
					y1 = ((double)(r - (accum_height / 2)) - ((x1 - (img_cols / 2)) * cos(t * CONVERT_DEGREE_TO_RADIAN))) / sin(t * CONVERT_DEGREE_TO_RADIAN) + (img_rows / 2);
					x2 = img_cols - 0;
					y2 = ((double)(r - (accum_height / 2)) - ((x2 - (img_cols / 2)) * cos(t * CONVERT_DEGREE_TO_RADIAN))) / sin(t * CONVERT_DEGREE_TO_RADIAN) + (img_rows / 2);
				}
				else
				{
					//x = (r - y sin(t)) / cos(t);
					y1 = 0;
					x1 = ((double)(r - (accum_height / 2)) - ((y1 - (img_rows / 2)) * sin(t * CONVERT_DEGREE_TO_RADIAN))) / cos(t * CONVERT_DEGREE_TO_RADIAN) + (img_cols / 2);
					y2 = img_rows - 0;
					x2 = ((double)(r - (accum_height / 2)) - ((y2 - (img_rows / 2)) * sin(t * CONVERT_DEGREE_TO_RADIAN))) / cos(t * CONVERT_DEGREE_TO_RADIAN) + (img_cols / 2);
				}

				lines.push_back(std::pair< std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(x1, y1), std::pair<int, int>(x2, y2)));

			}
		}
	}

	std::cout << "lines: " << lines.size() << " " << threshold << std::endl;
	return lines;
}

const unsigned int* HoughLines::getAccum(int *w, int *h)
{
	*w = accum_width;
	*h = accum_height;

	return accum;
}
