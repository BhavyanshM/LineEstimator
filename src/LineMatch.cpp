#include "../include/LineMatch.h"

LineMatch::LineMatch(Vec4f l1, Vec4f l2){
    this->prevLine = l1;
    this->curLine = l2;
}

LineMatch::LineMatch(Vec4f l1, Vec4f l2, double angleCost, double midPointCost, double lengthCost){
    this->prevLine = l1;
    this->curLine = l2;
    this->angleCost = angleCost;
    this->midPointCost = midPointCost;
    this->lengthCost = lengthCost;
}

