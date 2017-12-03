#include "stdafx.h"
#include "DartboardColourPatchs.h"


DartboardColourPatchs::DartboardColourPatchs()
{
	// beige colour
	colour_beige = { 175, 239, 255 };

	// push the colour to the colour_of_dartboard palette
	colour_of_dartboard.push_back(colour_beige);

	// setting the colour tolerance
	colour_tolerance = 85;
}


DartboardColourPatchs::~DartboardColourPatchs()
{
}

bool DartboardColourPatchs::isDartBoardColor(Vec3b color) {

	bool ret = false;

	//BGR colors
	for (int i = 0; i < colour_of_dartboard.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//cout << "norm: "<<norm(colour_of_dartboard[i], color) << endl;
			double dist = norm(colour_of_dartboard[i], color);
			if (dist <= colour_tolerance) {
				ret = true;
			}
		}
	}
	return ret;
}

void DartboardColourPatchs::findDartboards(Mat img) {


	//img.convertTo(img, CV_32F, 1.0 / 255, 0);
	img_clone = img.clone();

	int searchDimensions = 5;
	int searchAreaX = (int)floor(img.cols / searchDimensions);
	int searchAreaY = (int)floor(img.rows / searchDimensions);



	vector<Rect> imgSubsectionsWithDartBoardColors;

	for (int i = 0; i < img.rows - searchDimensions; i = i + searchDimensions) {


		for (int j = 0; j < img.cols - searchDimensions; j = j + searchDimensions) {
			Rect r = Rect(j, i, searchDimensions, searchDimensions);
			Mat imgSubsection = img(r);


			int subsectionVotes = 0;
			int maxvotes = searchDimensions * searchDimensions;

			for (int k = 0; k < imgSubsection.rows; k++)
			{
				for (int l = 0; l < imgSubsection.cols; l++)
				{
					Vec3b pixelColor;
					try
					{
						pixelColor = imgSubsection.at<Vec3b>(k, l);
						if (isDartBoardColor(pixelColor)) {

							subsectionVotes++;
						}
						else {

						}

					}
					catch (cv::Exception& e)
					{
						const char* err_msg = e.what();
						std::cout << "exception caught: " << err_msg << std::endl;
					}
				}
			}

			if (subsectionVotes > maxvotes / 2) {
				imgSubsectionsWithDartBoardColors.push_back(r);
				rectangle(img_clone, r, Scalar(255, 0, 255), 2);
			}



		}
		namedWindow("testimg", CV_WINDOW_AUTOSIZE);
		imshow("testimg", img_clone);
		waitKey(0);
	}
}

