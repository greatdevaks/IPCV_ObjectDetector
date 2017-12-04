#include "stdafx.h"
#include "ColourPatches.h"


ColourPatches::ColourPatches()
{
	// beige colour
	colour_beige = { 175, 239, 255 };

	// push the colour to the colour_of_dartboard palette
	colour_of_dartboard.push_back(colour_beige);

	// setting the colour tolerance
	colour_tolerance = 85;
}


ColourPatches::~ColourPatches()
{
}

bool ColourPatches::isDartBoardColor(Vec3b color) {

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

vector<Rect> ColourPatches::findDartboards(Mat img, vector<Rect> detections) {
	
	vector<Rect> cp_detections;
	for (int i = 0; i<detections.size(); i++) {
		Rect f = Rect(detections[i].x, detections[i].y, detections[i].width, detections[i].height);
		Mat subImage(img, f);
		
		
		imwrite("sub_image"+to_string(i)+".jpg", subImage);
	
		int searchDimensions = 5;
		int searchAreaX = (int)floor(subImage.cols / searchDimensions);
		int searchAreaY = (int)floor(subImage.rows / searchDimensions);



		vector<Rect> imgSubsectionsWithDartBoardColors;

		for (int i = 0; i < subImage.rows - searchDimensions; i = i + searchDimensions) {


			for (int j = 0; j < subImage.cols - searchDimensions; j = j + searchDimensions) {
				Rect r = Rect(j, i, searchDimensions, searchDimensions);
				Mat imgSubsection = subImage(r);


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
					rectangle(subImage, r, Scalar(255, 0, 255), 2);
					
				}



			}

		}
		if (imgSubsectionsWithDartBoardColors.size() > 20) {
			imwrite("cp_subimage_" + to_string(i) + ".jpg", subImage);
			cp_detections.push_back(detections[i]);
		}
	
	}

	return cp_detections;
}

