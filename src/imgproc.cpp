
#include "../include/imgproc.h"

int mouseX,mouseY = 0;

void preProcessImage(const Mat& image, Mat& processed){
    Mat gray, pyr_1, pyr_2;
    cvtColor(image,gray,COLOR_BGR2GRAY);
    medianBlur(gray,processed,5);
    GaussianBlur(processed,processed, Size(3,3),20);
}

void getLines(const Mat& img, vector<Vec4i>& lines, Mat& edges){
    Canny(img,edges,30,500, 5, false);
    HoughLinesP(edges,lines,1,M_PI/180, 10,60,3);
}

void getLines(const Mat& img, vector<Vec4i>& lines){
    Mat edges;
    getLines(img,lines,edges);
}

void initFusedLines(vector<Vec4i>& lines, vector<FusedLine>& fusedLines){
    for(int i = 0; i<lines.size(); i++){
        Vector2f p1(lines[i][0], lines[i][1]), p2(lines[i][2], lines[i][3]);
        FusedLine fl(p1,p2,i);
        fusedLines.emplace_back(fl);
    }
}

void getLineEndPoints(vector<Vec4i>& prevLines, vector<Point2f>& f_points){
    for (auto l : prevLines){
        Point2f first(l[0],l[1]),second(l[2],l[3]);
        f_points.emplace_back(first);
        f_points.emplace_back(second);
    }
}

void getFusedLineEndPoints(vector<FusedLine>& fusedLines, vector<Point2f>& f_points){
    for (auto fl : fusedLines){
        Point2f first(fl.p1.x(),fl.p1.y()),second(fl.p2.x(),fl.p2.y());
        f_points.emplace_back(first);
        f_points.emplace_back(second);
    }
}

void flowUpdateFusedLines(vector<FusedLine>& fusedLines, vector<Point2f>& fn_points){
    for(int i = 0; i<fusedLines.size(); i++){
        Point2f fn_p1 = fn_points[2*i];
        Point2f fn_p2 = fn_points[2*i+1];
        fusedLines[i].p1(0) = fn_p1.x;
        fusedLines[i].p1(0) = fn_p1.y;
        fusedLines[i].p2(0) = fn_p2.x;
        fusedLines[i].p2(0) = fn_p2.y;
    }
}

void onMouseClick(int event, int x, int y, int, void*){
    if(event == EVENT_LBUTTONDOWN){
        mouseX = x;
        mouseY = y;
        cout << "MouseEventX:" << mouseX << "\t MouseEventY:" << mouseY << endl;
    }
}

void growClickedRegion(const Mat& prevProc, Mat& regionMap){
    cout << "MouseX:" << mouseX << "\t MouseY:" << mouseY << endl;
}

void extendLine(const Mat& img, Mat& disp, Vector2f& endPoint, Vector2f midPoint, Vector2f direction){
    Vector2f newEndPoint;
    double dist,prevDist = 0;
    int count = 0;
    double threshold = 150;
    while(dist < threshold){
        newEndPoint = endPoint + direction*3;;
        if (newEndPoint.x()-4>0 && newEndPoint.y()-4>0 && newEndPoint.x()+4<img.cols && newEndPoint.y()+4<img.rows &&
            midPoint.x()-4>0 && midPoint.y()-4>0 && midPoint.x()+4<img.cols && midPoint.y()+4<img.rows){
            Rect initROI(newEndPoint.x()-3, newEndPoint.y()-3, 6,6);
            Mat initPatch = img(initROI);
            Rect midROI(midPoint.x()-3, midPoint.y()-3, 6,6);
            Mat midPatch = img(midROI);
            dist = norm(initPatch, midPatch);
            cout << "Count:" << count << "\tNORM:" << dist << endl;
            if (abs(dist) < threshold){
                line( disp, Point(endPoint.x(), endPoint.y()),
                      Point(newEndPoint.x(), newEndPoint.y()),
                      Scalar(100,100,255), 3);
                endPoint = newEndPoint;
            }else{
                cout << "HIGH DIST:" << dist << endl;
            }
            // imshow("Extender",disp);if(waitKeyEx(100)==113)break;
            prevDist = dist;
            count++;
        }else{
            break;
        }
    }
}

void growLineRegions(const Mat& img, Mat& disp, vector<Vec4i>& lines){
    for(int i = 0; i<lines.size(); i++){
        Vec4i l = lines[i];
        Vector2f ep1(l[0],l[1]), ep2(l[2],l[3]);
        Vector2f dir1(ep1-ep2),dir2(ep2-ep1);
        extendLine(img, disp, ep1, (ep1+ep2)/2, dir1/dir1.norm());
        extendLine(img, disp, ep2, (ep1+ep2)/2, dir2/dir2.norm());
        printf("%d %d %d %d\t:\t%.2f %.2f %.2f %.2f\n",l[0],l[1],l[2],l[3],ep1.x(),ep1.y(),ep2.x(),ep2.y());
        lines[i][0] = ep1.x();
        lines[i][1] = ep1.y();
        lines[i][2] = ep2.x();
        lines[i][3] = ep2.y();
    }
}



