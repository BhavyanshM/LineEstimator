#ifndef LINEESTIMATOR_FUSEDLINE_H
#define LINEESTIMATOR_FUSEDLINE_H

#include <Eigen/Dense>

using namespace Eigen;

class FusedLine {
public:
    Vector2f p1,p2,mid;
    float slope;
    int votes,id;
    FusedLine(Vector2f p1, Vector2f p2, int id);
};


#endif //LINEESTIMATOR_FUSEDLINE_H
