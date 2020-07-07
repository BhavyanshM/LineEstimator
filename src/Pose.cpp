#include "../include/Pose.h"

Pose::Pose(double t, double tx, double ty, double tz, double qx, double qy, double qz, double qw){
    {
        this->time = t;
        this->tx = tx;
        this->ty = ty;
        this->tz = tz;
        this->qx = qx;
        this->qy = qy;
        this->qz = qz;
        this->qw = qw;
    }
}

void Pose::print() {
    printf("%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\n",
           this->time,this->tx,this->ty,this->tz,this->qx,this->qy,this->qz,this->qw);
}