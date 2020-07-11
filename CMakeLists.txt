cmake_minimum_required(VERSION 3.16)
project(LineEstimator)

set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV 4.3.0 REQUIRED )
find_package(PCL 1.4 REQUIRED)
find_package(Ceres REQUIRED)

include_directories("./eigen-3.3.7")
include_directories(${CERES_INCLUDE_DIRS})
include_directories(${PCL_INCLUDE_DIRS} )

link_directories(${PCL_LIBRARY_DIRS} )
add_definitions(${PCL_DEFINITIONS} )

add_executable( BundleAdjuster
        src/simple_bundle_adjust.cpp)

add_executable( LineEstimator
        src/main.cpp
        src/QuadTree.cpp include/QuadTree.h
        src/utils.cpp include/utils.h
        src/imgproc.cpp include/imgproc.h include/main.h
        src/render.cpp include/render.h
        src/Pose.cpp include/Pose.h
        src/FusedLine.cpp include/FusedLine.h
        src/matcher.cpp include/matcher.h
        src/LineMatch.cpp include/LineMatch.h)

target_link_libraries( BundleAdjuster
        ${CERES_LIBRARIES}
)

target_link_libraries( LineEstimator
        ${OpenCV_LIBS}
        ${PCL_LIBRARIES}
        ${CERES_LIBRARIES}
)

