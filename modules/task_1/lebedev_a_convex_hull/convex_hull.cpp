// Copyright 2022 Lebedev Alexey
#include <algorithm>
#include "../../../modules/task_1/lebedev_a_convex_hull/convex_hull.h"

bool cw(const cv::Point2d& p1, const cv::Point2d& p2, const cv::Point2d& p3) {
    return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y) < 0;
}

bool ccw(const cv::Point2d& p1, const cv::Point2d& p2, const cv::Point2d& p3) {
    return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y) > 0;
}

void lab1::convex_hull(const cv::Mat& c1_image, std::vector<cv::Point2d>* output) {
    cv::findNonZero(c1_image, *output);
    if (output->size() <= 2) {
        return;
    }
    std::sort(output->begin(), output->end(), [](const cv::Point2d& p1, const cv::Point2d& p2) {
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
        });
    cv::Point2d p1 = output->front(), p2 = output->back();
    std::vector<cv::Point2d> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (size_t i = 1; i < output->size(); ++i) {
        if (i == output->size() - 1 || cw(p1, (*output)[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], (*output)[i])) {
                up.pop_back();
            }
            up.push_back((*output)[i]);
        }
        if (i == output->size() - 1 || ccw(p1, (*output)[i], p2)) {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], (*output)[i])) {
                down.pop_back();
            }
            down.push_back((*output)[i]);
        }
    }
    output->clear();
    output->resize(up.size() + down.size() - 2);
    auto it = std::copy(up.begin(), up.end(), output->begin());
    std::copy(down.rbegin() + 1, down.rend() - 1, it);
}
