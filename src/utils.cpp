#include "../include/utils.h"

void getData(const string& gtPath, vector<Pose>& poseList, vector<double>& poseTimes){
    ifstream in(gtPath);
    int count = 0;
    string pose;
    double t,tx,ty,tz,qx,qy,qz,qw = 0.0;
    while(getline(in,pose)){
        if(count++>=3){
            istringstream ss(pose);
            ss >> t >> tx >> ty >> tz >> qx >> qy >> qz >> qw;
            poseList.emplace_back(Pose(t,tx,ty,tz,qx,qy,qz,qw));
            poseTimes.emplace_back(t);

        }
    }
}

long getTime(time_point<high_resolution_clock> start){
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    return duration.count();
}

void getImageFiles(const string& path, vector<string>& rgb){
    cout << path << endl;
    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.')
                continue;
            rgb.emplace_back(f->d_name);
        }
        closedir(dir);
    }
    sort(rgb.begin(),rgb.end());
}

