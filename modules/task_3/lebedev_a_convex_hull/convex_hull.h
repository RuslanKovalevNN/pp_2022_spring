// Copyright 2022 Lebedev Alexey
#ifndef MODULES_TASK_3_LEBEDEV_A_CONVEX_HULL_CONVEX_HULL_H_
#define MODULES_TASK_3_LEBEDEV_A_CONVEX_HULL_CONVEX_HULL_H_


#include <vector>

#ifdef USE_OPENCV
#include "opencv2/opencv.hpp"
#else
#include "./utils.h"
namespace cv = lab3::image_utils;
#endif


namespace lab3 {
    enum Version {PARALLEL, SEQUENTIAL, PARALLEL_ONE_THREAD};
    void convex_hull(const cv::Mat& input, std::vector<cv::Point2d>* output,
        Version v = Version::PARALLEL_ONE_THREAD);
    void convex_hull(std::vector<cv::Point2d>* input, std::vector<cv::Point2d>* output,
        Version v = Version::PARALLEL_ONE_THREAD);
};  // namespace lab3


#endif  // MODULES_TASK_3_LEBEDEV_A_CONVEX_HULL_CONVEX_HULL_H_
