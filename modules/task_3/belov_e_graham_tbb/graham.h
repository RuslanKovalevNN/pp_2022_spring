// Copyright 2022 Belov Egor
#ifndef MODULES_TASK_3_BELOV_E_GRAHAM_TBB_GRAHAM_H_
#define MODULES_TASK_3_BELOV_E_GRAHAM_TBB_GRAHAM_H_

#include <vector>

struct Point {
  double x, y;
  Point() {
    x = 0.0;
    y = 0.0;
  }

  Point(double _x, double _y) : x(_x), y(_y) {}

  friend bool operator==(const Point& a, const Point& b) {
    return (a.x == b.x) && (a.y == b.y);
  }
};

bool cmp(Point A, Point B);
bool cw(Point A, Point B, Point C);
bool ccw(Point A, Point B, Point C);
std::vector<Point> Graham(std::vector<Point>::iterator begin,
                          std::vector<Point>::iterator end);
std::vector<Point> RandPoint(int n);
std::vector<Point> TbbGraham(std::vector<Point> tmp,
                             std::size_t threads_num = 2);

#endif  // MODULES_TASK_3_BELOV_E_GRAHAM_TBB_GRAHAM_H_
