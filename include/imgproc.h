#ifndef LINEESTIMATOR_IMGPROC_H
#define LINEESTIMATOR_IMGPROC_H

#endif //LINEESTIMATOR_IMGPROC_H

#include <opencv2/opencv.hpp>
#include "FusedLine.h"

using namespace cv;
using namespace std;

void initFusedLines(vector<Vec4i>& lines, vector<FusedLine>& fusedLines);
void preProcessImage(const Mat& image, Mat& processed);
void getLines(const Mat& img, vector<Vec4i>& lines, Mat& edges);
void getLines(const Mat& img, vector<Vec4i>& lines);
void getLineEndPoints(vector<Vec4i>& prevLines, vector<Point2f>& f_points);
void getFusedLineEndPoints(vector<FusedLine>& fusedLines, vector<Point2f>& f_points);
void flowUpdateFusedLines(vector<FusedLine>& fusedLines, vector<Point2f>& fn_points);
void growClickedRegion(const Mat& prevProc, Mat& regionMap);
void onMouseClick(int event, int x, int y, int, void*);
void growLineRegions(const Mat& img, Mat& disp, vector<Vec4i>& lines);