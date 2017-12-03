#pragma once
#include "stdafx.h"
#include "F1Score.h"


F1Score::F1Score()
{
	// initializing parameters for calculating F1Score
	// tp_count = 0, fp_count = 0, fn_count = 0
	tp_count = 0;
	fp_count = 0;
	fn_count = 0;

}


F1Score::~F1Score()
{
}

float F1Score::calculatePrecision(float tp_count, float fp_count) {
	float result = tp_count / (tp_count + fp_count);
	cout << "Precision: " << result << endl;
	return result;
}

float F1Score::calculateRecall(float tp_count, float fn_count) {
	float result = tp_count / (tp_count + fn_count);
	cout << "Recall: " << result << endl;
	return result;
}

float F1Score::calculateF1Score(float precision, float recall) {
	if (precision + recall != 0)
	{
		float result = (2 * precision * recall) / (precision + recall);
		cout << "F1 Score: " << result << endl;
		return result;
	}
	else {
		cout << "F1 Score: " << 0 << endl;
		return 0;
	}
}

bool F1Score::calculateIntersectionAreaBetweenGTBoxAndDetectedBox(Rect ground_truth_box, Rect detected_box) {
	Rect intersection_area = ground_truth_box & detected_box;
	float intersection_ratio = (float)intersection_area.area() / (float)ground_truth_box.area();
	return intersection_ratio > 0.5;
}



