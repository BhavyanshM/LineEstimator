#ifndef LINEESTIMATOR_IMGPROC_H
#define LINEESTIMATOR_IMGPROC_H

#endif //LINEESTIMATOR_IMGPROC_H

#include <opencv2/ximgproc.hpp>
#include <opencv2/opencv.hpp>
#include "FusedLine.h"

using namespace cv;
using namespace std;
using namespace ximgproc;

void initFusedLines(vector<Vec4i>& lines, vector<FusedLine>& fusedLines);
void preProcessImage(const Mat& image, Mat& processed);
void getHoughLines(const Mat& img, vector<Vec4i>& lines, Mat& edges);
void getHoughLines(const Mat& img, vector<Vec4i>& lines);
void getLineEndPoints(vector<Vec4i>& prevLines, vector<Point2f>& f_points);
void getFusedLineEndPoints(vector<FusedLine>& fusedLines, vector<Point2f>& f_points);
void flowUpdateFusedLines(vector<FusedLine>& fusedLines, vector<Point2f>& fn_points);
void growClickedRegion(const Mat& prevProc, Mat& regionMap);
void onMouseClick(int event, int x, int y, int, void*);
void growLineRegions(const Mat& img, Mat& disp, vector<Vec4i>& lines);
void getORBFeatures(Mat& image, vector<KeyPoint> kpoints, Mat& descriptors);
void getFLDLines(Mat& image, Mat& gray, vector<Vec4f>& klines);
void matchFLDLines(vector<Vec4f> prevFLDLines, vector<Vec4f> FLDlines, vector<Vec4i> corresp);