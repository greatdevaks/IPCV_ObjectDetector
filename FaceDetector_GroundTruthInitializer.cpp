#pragma once
#include "stdafx.h"
#include <iostream>
#include "FaceDetector_GroundTruthInitializer.h"

using namespace std;

FaceDetector_GroundTruthInitializer::FaceDetector_GroundTruthInitializer()
{
	cout << endl;
	cout << "Started initializing groundtruth for face detector." << endl;

	gtvec_dart0_faces.push_back(Rect(333, 53, abs(488 - 333), abs(278 - 53)));

	gtvec_dart1_faces.push_back(Rect(0, 0, abs(0 - 0), abs(0 - 0)));

	gtvec_dart2_faces.push_back(Rect(0, 0, abs(0 - 0), abs(0 - 0)));

	gtvec_dart3_faces.push_back(Rect(0, 0, abs(0 - 0), abs(0 - 0)));

	gtvec_dart4_faces.push_back(Rect(333, 53, abs(488 - 333), abs(278 - 53)));

	gtvec_dart5_faces.push_back(Rect(50, 240, abs(117 - 50), abs(324 - 240)));
	gtvec_dart5_faces.push_back(Rect(54, 112, abs(126 - 54), abs(210 - 112)));
	gtvec_dart5_faces.push_back(Rect(193, 209, abs(252 - 193), abs(289 - 209)));
	gtvec_dart5_faces.push_back(Rect(245, 162, abs(308 - 245), abs(235 - 162)));
	gtvec_dart5_faces.push_back(Rect(292, 230, abs(348 - 292), abs(309 - 230)));
	gtvec_dart5_faces.push_back(Rect(374, 182, abs(437 - 374), abs(254 - 182)));
	gtvec_dart5_faces.push_back(Rect(428, 228, abs(486 - 428), abs(308 - 228)));
	gtvec_dart5_faces.push_back(Rect(511, 168, abs(574 - 511), abs(244 - 168)));
	gtvec_dart5_faces.push_back(Rect(559, 239, abs(620 - 559), abs(317 - 239)));
	gtvec_dart5_faces.push_back(Rect(647, 178, abs(707 - 647), abs(254 - 178)));
	gtvec_dart5_faces.push_back(Rect(675, 237, abs(737 - 675), abs(313 - 237)));

	gtvec_dart6_faces.push_back(Rect(290, 116, abs(324 - 290), abs(157 - 116)));

	gtvec_dart7_faces.push_back(Rect(348, 193, abs(413 - 348), abs(285 - 193)));

	gtvec_dart8_faces.push_back(Rect(0, 0, abs(0 - 0), abs(0 - 0)));

	gtvec_dart9_faces.push_back(Rect(96, 210, abs(188 - 96), abs(334 - 210)));

	gtvec_dart10_faces.push_back(Rect(0, 0, abs(0 - 0), abs(0 - 0)));

	gtvec_dart11_faces.push_back(Rect(328, 84, abs(378 - 328), abs(146 - 84)));

	gtvec_dart12_faces.push_back(Rect(0, 0, abs(0 - 0), abs(0 - 0)));

	gtvec_dart13_faces.push_back(Rect(415, 113, abs(530 - 415), abs(261 - 113)));

	gtvec_dart14_faces.push_back(Rect(467, 202, abs(555 - 467), abs(324 - 202)));
	gtvec_dart14_faces.push_back(Rect(725, 181, abs(828 - 725), abs(300 - 181)));

	gtvec_dart15_faces.push_back(Rect(65, 134, abs(121 - 65), abs(211 - 134)));
	gtvec_dart15_faces.push_back(Rect(542, 133, abs(610 - 542), abs(215 - 133)));


	groundtruth_faces.push_back(gtvec_dart0_faces);
	groundtruth_faces.push_back(gtvec_dart1_faces);
	groundtruth_faces.push_back(gtvec_dart2_faces);
	groundtruth_faces.push_back(gtvec_dart3_faces);
	groundtruth_faces.push_back(gtvec_dart4_faces);
	groundtruth_faces.push_back(gtvec_dart5_faces);
	groundtruth_faces.push_back(gtvec_dart6_faces);
	groundtruth_faces.push_back(gtvec_dart7_faces);
	groundtruth_faces.push_back(gtvec_dart8_faces);
	groundtruth_faces.push_back(gtvec_dart9_faces);
	groundtruth_faces.push_back(gtvec_dart10_faces);
	groundtruth_faces.push_back(gtvec_dart11_faces);
	groundtruth_faces.push_back(gtvec_dart12_faces);
	groundtruth_faces.push_back(gtvec_dart13_faces);
	groundtruth_faces.push_back(gtvec_dart14_faces);
	groundtruth_faces.push_back(gtvec_dart15_faces);

	cout << "Done initializing groundtruth for face detector." << endl;
}


FaceDetector_GroundTruthInitializer::~FaceDetector_GroundTruthInitializer()
{
}
