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
	if (isnan(result)) {
		cout << "Precision: " << 0 << endl;
		return 0;
	}
	else {
		cout << "Precision: " << result << endl;
		return result;
	}
	
}

float F1Score::calculateRecall(float tp_count, float fn_count) {
	float result = tp_count / (tp_count + fn_count);
	if (isnan(result)) {
		cout << "Recall: " << 0 << endl;
		return 0;
	}
	else {
		cout << "Recall: " << result << endl;
		return result;
	}
	
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
	Rect intersection_rect = ground_truth_box & detected_box;
	Rect union_rect = ground_truth_box | detected_box;
	float intersection_area = intersection_rect.area();
	float union_area = union_rect.area();
	float intersection_ratio = intersection_area / union_area;
	return intersection_ratio > 0.5;
}



