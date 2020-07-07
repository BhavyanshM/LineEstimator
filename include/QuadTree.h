//
// Created by quantum on 7/1/20.
//

#ifndef LINEESTIMATOR_QUADTREE_H
#define LINEESTIMATOR_QUADTREE_H

class Quad{
public:
    Quad* chNodes[4];
    int x,y;

    Quad(int a, int b){
        this->x = a;
        this->y = b;
    }
};


class QuadTree{
public:
    Quad* root;

    QuadTree(int a, int b){
        this->root->x = a;
        this->root->y = b;
    }
};



#endif //LINEESTIMATOR_QUADTREE_H
