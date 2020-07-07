#ifndef LINEESTIMATOR_POSE_H
#define LINEESTIMATOR_POSE_H

#include <iostream>

using namespace std;

class Pose{
public:
    double time, tx,ty,tz,qx,qy,qz,qw;
    Pose(double t, double tx, double ty, double tz, double qx, double qy, double qz, double qw);
    void print();
};

#endif //LINEESTIMATOR_POSE_H
