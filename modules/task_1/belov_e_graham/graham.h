// Copyright 2022 Belov Egor
#ifndef MODULES_TASK_1_BELOV_E_GRAHAM_GRAHAM_H_
#define MODULES_TASK_1_BELOV_E_GRAHAM_GRAHAM_H_

#include <vector>

struct point {
  double x, y;
  point() {
    x = 0.0;
    y = 0.0;
  }

  point(double _x, double _y) : x(_x), y(_y) {}

  friend bool operator==(const point& a, const point& b) {
    return (a.x == b.x) && (a.y == b.y);
  }
};

bool comp(const point& A, const point& B);  // B<C?

bool rotate(const point& A, const point& B, const point& C);

std::vector<point> RandPoint(int n);

std::vector<point> Graham(std::vector<point> Q);

#endif  // MODULES_TASK_1_BELOV_E_GRAHAM_GRAHAM_H_
