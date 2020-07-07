#ifndef LINEESTIMATOR_UTILS_H
#define LINEESTIMATOR_UTILS_H

#endif //LINEESTIMATOR_UTILS_H

#include<bits/stdc++.h>
#include <dirent.h>
#include <pcl/point_cloud.h>
#include <Eigen/Dense>
#include "Pose.h"

using namespace std;
using namespace chrono;


void getData(const string& gtPath, vector<Pose>& poseList, vector<double>& poseTimes);
long getTime(time_point<high_resolution_clock> start);
void getImageFiles(const string& path, vector<string>& rgb);
