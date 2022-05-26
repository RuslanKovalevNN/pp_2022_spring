// Copyright 2022 Belov Egor
#include <algorithm>
#include <utility>
#include <random>
#include <vector>
#include <ctime>
#include "../../../modules/task_1/belov_e_graham/graham.h"

bool rotate(const point& A, const point& B, const point& C) {
  return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x) >= 0;
}

bool comp(const point& A, const point& B) {
  return B.x * (A.y - B.y) - B.y * (A.x - B.x) < 0 ||
         (B.x * (A.y - B.y) - B.y * (A.x - B.x) == 0 &&
          A.x * A.x + A.y * A.y < B.x * B.x + B.y * B.y);
}

std::vector<point> Graham(std::vector<point> tmp) {
  if (tmp.size() < 3) throw "|Q|<3";

  int l = 0;
  for (size_t i = 1; i < tmp.size(); i++) {
    if ((tmp[i].y < tmp[l].y) ||
        ((tmp[i].y == tmp[l].y) && (tmp[i].x < tmp[l].x)))
      l = i;
  }
  std::swap(tmp[0], tmp[l]);
  point p = tmp[0];

  for (size_t i = 0; i < tmp.size(); i++) {
    tmp[i].x -= p.x;
    tmp[i].y -= p.y;
  }
  std::sort(tmp.begin() + 1, tmp.end(), &comp);

  std::vector<point> res;
  res.push_back(tmp[0]);
  res.push_back(tmp[1]);

  size_t i = 2, j = 0;
  do {
    point t = tmp[i];

    while (!rotate(res[j], res[j + 1], t)) {
      res.pop_back();
      --j;
    }
    res.push_back(t);
    ++j;
    ++i;
  } while (i < tmp.size());

  for (size_t t = 0; t < res.size(); t++) {
    res[t].x += p.x;
    res[t].y += p.y;
  }

  return res;
}

std::vector<point> RandPoint(int n) {
  std::vector<point> res(n);
  std::mt19937 gen;
  for (int i = 0; i < n; i++) {
    res[i].x = gen() % 10000;
    res[i].y = gen() % 10000;
  }
  return res;
}
