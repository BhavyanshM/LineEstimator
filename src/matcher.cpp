#include "../include/matcher.h"

double calcAngleCost(Vec4f l1, Vec4f l2){
    Vector2f a(l1[0],l1[1]),b(l1[2],l1[3]),c(l2[0],l2[1]),d(l2[2],l2[3]);
    Vector2f l1_hat = (a-b)/((a-b).norm());
    Vector2f l2_hat = (c-d)/((c-d).norm());
    return pow( acos(l1_hat.dot(l2_hat))*180/M_PI , 2);
}

double calcMidPointCost(Vec4f l1, Vec4f l2){
    Vector2f a(l1[0],l1[1]),b(l1[2],l1[3]),c(l2[0],l2[1]),d(l2[2],l2[3]);
    return pow( ( (a+b)/2 - (c+d)/2 ).norm() , 2);
}

double calcLengthCost(Vec4f l1, Vec4f l2){
    Vector2f a(l1[0],l1[1]),b(l1[2],l1[3]),c(l2[0],l2[1]),d(l2[2],l2[3]);
    return pow((a-b).norm()-(c-d).norm(),2);
}

void matchFLDLines(vector<Vec4f>& prevFLDLines, vector<Vec4f>& FLDlines, vector<LineMatch>& corresp){
    double angleCost, midPointCost, lengthCost = 0;
    double angleThreshold = 50, midPointThreshold = 100, lengthThreshold = 1200;
    for(Vec4f pl : prevFLDLines){
        for(Vec4f cl : FLDlines){
            angleCost = calcAngleCost(pl,cl);
            midPointCost = calcMidPointCost(pl,cl);
            lengthCost = calcLengthCost(pl,cl);
            if(     angleCost < angleThreshold
                &&  midPointCost < midPointThreshold
                // &&  lengthCost < lengthThreshold
                ){
                    // printf("%.2lf\t%.2lf\t%.2lf\n",angleCost, midPointCost, lengthCost);
                    LineMatch lm(pl,cl,angleCost,midPointCost,lengthCost);
                    corresp.emplace_back(lm);
            }
        }
    }
}
