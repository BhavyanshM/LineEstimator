#ifndef LINEESTIMATOR_MATCHER_H
#define LINEESTIMATOR_MATCHER_H

#endif //LINEESTIMATOR_MATCHER_H

#include "../include/LineMatch.h"

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

using namespace Eigen;
using namespace cv;
using namespace std;

void matchFLDLines(vector<Vec4f>& prevFLDLines, vector<Vec4f>& FLDlines, vector<LineMatch>& corresp);
double calcAngleCost(Vec4f line1, Vec4f line2);
double calcMidPointCost(Vec4f line1, Vec4f line2);
double calcLengthCost(Vec4f line1, Vec4f line2);
