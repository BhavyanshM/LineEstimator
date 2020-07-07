#include "../include/QuadTree.h"

void insert(Quad* node, Quad* stRoot, int level) {
    int posX = (node->x >> level) & 1;
    int posY = (node->y >> level) & 1;
    int pos = posX * 2 + posY;
    if (stRoot->chNodes[pos] == nullptr) {
        stRoot->chNodes[pos] = new Quad(node->x, node->y);
    } else {
        insert(node, stRoot->chNodes[pos], level + 1);
    }
}
