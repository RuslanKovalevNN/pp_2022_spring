// Copyright 2022 Belov Egor
#ifndef MODULES_TASK_4_BELOV_E_GRAHAM_THREAD_GRAHAM_H_
#define MODULES_TASK_4_BELOV_E_GRAHAM_THREAD_GRAHAM_H_

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

bool comp(const Point& A, const Point& B);  // B<C?

bool rotate(const Point& A, const Point& B, const Point& C);

std::vector<Point> RandPoint(int n);

std::vector<Point> Graham(std::vector<Point>::iterator begin,
                          std::vector<Point>::iterator end);
std::vector<Point> ThreadGraham(std::vector<Point> tmp,
                                std::size_t n_threads = 2);

#endif  // MODULES_TASK_4_BELOV_E_GRAHAM_THREAD_GRAHAM_H_
