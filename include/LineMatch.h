#ifndef LINEESTIMATOR_LINEMATCH_H
#define LINEESTIMATOR_LINEMATCH_H

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class LineMatch {
public:
    Vec4f prevLine, curLine;
    double angleCost, lengthCost, midPointCost;
    LineMatch(Vec4f l1, Vec4f l2);
    LineMatch(Vec4f l1, Vec4f l2, double angleCost, double midPointCost, double lengthCost);
};


#endif //LINEESTIMATOR_LINEMATCH_H
