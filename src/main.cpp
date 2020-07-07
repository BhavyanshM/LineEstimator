#include<bits/stdc++.h>
#include <string>

#include "../include/utils.h"
#include "../include/imgproc.h"
#include "../include/main.h"
#include "../include/render.h"
#include "../include/FusedLine.h"

using namespace Eigen;
using namespace cv;
using namespace pcl;

const int H = 800;
const int W = 1600;



int main()
{
    // pcl::visualization::PCLVisualizer viewer;

    vector<string> rgb;
    vector<Pose> poseList;
    vector<double> poseTimes;
    Mat image, prev, proc, prevProc;
    vector<Vec4i> prevLines,lines;

    getImageFiles(path, rgb);
    getData(gtPath,poseList, poseTimes);
    prev = imread(path+rgb[0],IMREAD_COLOR);

    preProcessImage(prev, prevProc);
    getLines(prevProc,prevLines);

    auto cmp = [](const FusedLine& a, const FusedLine& b){return (a.votes > b.votes);};
    vector<FusedLine> fusedLines;
    initFusedLines(prevLines, fusedLines);


    setMouseCallback("image",onMouseClick,0);

    for (int k = 1; k < rgb.size(); k++){
        auto start = high_resolution_clock::now();


        istringstream ss(rgb[k].substr(0,17));
        double imgTime = 0;
        ss >> imgTime;

        // auto p = upper_bound(poseTimes.begin(), poseTimes.end(), imgTime);
        // int timeIndex = (int)(p-poseTimes.begin());
        // Pose curPose = poseList[timeIndex];
        // showPose(curPose,viewer);
        // viewer.spinOnce();

        vector<Point2f> f_points;
        vector<Point2f> fn_points;
        vector<uchar> status;
        vector<float> err;
        Mat edges;

        image = imread(path + rgb[k], IMREAD_COLOR);
        preProcessImage(image, proc);
        getLines(proc,lines, edges);



        Mat labels, centers;

        // for(int i = 0; i<fusedLines.size(); i++){
        //     line( image, Point(fusedLines[i].p1.x(), fusedLines[i].p1.y()),
        //           Point(fusedLines[i].p2.x(), fusedLines[i].p2.y()),
        //           Scalar(0,0,255), 3);
        // }

        getLineEndPoints(prevLines,f_points);
        // getFusedLineEndPoints(fusedLines,f_points);
        calcOpticalFlowPyrLK(prev,image,f_points,fn_points,status,err);
        // flowUpdateFusedLines(fusedLines, fn_points);


        for(auto l : lines){
            line( image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,255,255), 2);
        }
        growLineRegions(proc, image, lines);

        cout << fusedLines.size() << endl;


//         for(int i = 0; i<prevLines.size(); i++){
//             Point2f fn_p1 = fn_points[2*i];
//             Point2f fn_p2 = fn_points[2*i+1];
//             line(image,Point(fn_p1.x,fn_p1.y),Point(fn_p2.x,fn_p2.y),Scalar(255,0,255),2);
// //            arrowedLine(image,Point(f_points[2*i].x,f_points[2*i].y),Point(fn_p1.x,fn_p1.y),Scalar(255,0,0));
// //            arrowedLine(image,Point(f_points[2*i+1].x,f_points[2*i+1].y),Point(fn_p2.x,fn_p2.y),Scalar(255,0,0));
//         }




        long duration = getTime(start);
        printf("Time:%ld ms\tLines:%d\tRows:%d\tCols:%d\n",duration,(int)lines.size(),image.rows,image.cols);

        Mat dispEdges, dispImage;
        cvtColor(edges,dispEdges,COLOR_GRAY2BGR);
        hconcat(image,dispEdges,dispImage);
        int x = display(dispImage,"TUM-RGBD", 1000);
        if(x == 113) break;

        prev = image;
        prevLines = lines;
    }
    return 0;
}