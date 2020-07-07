#include "../include/FusedLine.h"

FusedLine::FusedLine(Vector2f p1, Vector2f p2, int id){
    this->p1 = p1;
    this->p2 = p2;
    this->mid = (p1+p2)/2;
    this->slope = ((p1-p2)(1))/((p1-p2)(0));
    this->id = id;
}

