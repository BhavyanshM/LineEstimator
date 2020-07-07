#include "../include/render.h"

int display(const Mat& image, string name, int delay_ms){
    namedWindow(name, WINDOW_AUTOSIZE );
    imshow(name, image);
    return waitKeyEx(delay_ms);
}



