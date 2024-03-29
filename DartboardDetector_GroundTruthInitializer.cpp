#pragma once
#include "stdafx.h"
#include <iostream>
#include "DartboardDetector_GroundTruthInitializer.h"


DartboardDetector_GroundTruthInitializer::DartboardDetector_GroundTruthInitializer()
{
	cout << endl;
	cout << "Started initializing groundtruth for dartboard detector." << endl;

	gtvec_dart0_dartboards.push_back(Rect(422, 1, abs(606 - 422), abs(219 - 1)));

	gtvec_dart1_dartboards.push_back(Rect(166, 100, abs(421 - 166), abs(355 - 100)));

	gtvec_dart2_dartboards.push_back(Rect(82, 73, abs(203 - 82), abs(208 - 73)));

	gtvec_dart3_dartboards.push_back(Rect(312, 138, 398 - 312, 226 - 138));

	gtvec_dart4_dartboards.push_back(Rect(150, 70, 404 - 150, 326 - 70));

	gtvec_dart5_dartboards.push_back(Rect(421, 126, 549 - 421, 266 - 126));

	gtvec_dart6_dartboards.push_back(Rect(202, 107, 282 - 202, 200 - 107));

	gtvec_dart7_dartboards.push_back(Rect(232, 152, 405 - 232, 354 - 152));

	gtvec_dart8_dartboards.push_back(Rect(62, 241, 134 - 62, 251 - 134));
	gtvec_dart8_dartboards.push_back(Rect(828, 205, 969 - 828, 351 - 205));

	gtvec_dart9_dartboards.push_back(Rect(169, 17, 468 - 169, 305 - 17));

	gtvec_dart10_dartboards.push_back(Rect(70, 80, 230 - 79, 242 - 90));
	gtvec_dart10_dartboards.push_back(Rect(579, 119, 643 - 579, 224 - 119));	
	gtvec_dart10_dartboards.push_back(Rect(913, 143, 954 - 913, 222 - 143));

	gtvec_dart11_dartboards.push_back(Rect(169, 92, 240 - 169, 187 - 92));

	gtvec_dart12_dartboards.push_back(Rect(150, 60, 232 - 150, 222 - 60));

	gtvec_dart13_dartboards.push_back(Rect(256, 105, 417 - 256, 268 - 105));

	gtvec_dart14_dartboards.push_back(Rect(98, 81, 271 - 98, 272 - 81));
	gtvec_dart14_dartboards.push_back(Rect(955, 70, 1142 - 955, 263 - 70));

	gtvec_dart15_dartboards.push_back(Rect(129, 36, 300 - 129, 207 - 36));

	groundtruth_dartboards.push_back(gtvec_dart0_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart1_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart2_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart3_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart4_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart5_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart6_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart7_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart8_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart9_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart10_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart11_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart12_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart13_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart14_dartboards);
	groundtruth_dartboards.push_back(gtvec_dart15_dartboards);

	cout << "Done initializing groundtruth for dartboard detector." << endl;
}


DartboardDetector_GroundTruthInitializer::~DartboardDetector_GroundTruthInitializer()
{
}
