// Copyright 2022 Belov Egor
#include <omp.h>
#include <algorithm>
#include <utility>
#include <random>
#include <vector>
#include <ctime>
#include "../../../modules/task_2/belov_e_graham_omp/graham.h"

bool rotate(const point& A, const point& B, const point& C) {
  return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x) >= 0;
}

bool comp(const point& A, const point& B) {
  return B.x * (A.y - B.y) - B.y * (A.x - B.x) < 0 ||
         (B.x * (A.y - B.y) - B.y * (A.x - B.x) == 0 &&
          A.x * A.x + A.y * A.y < B.x * B.x + B.y * B.y);
}

std::vector<point> Graham(std::vector<point>::iterator begin,
                          std::vector<point>::iterator end) {
  std::vector<point> tmp(end - begin);
  std::copy(begin, end, tmp.begin());
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

std::vector<point> OmpGraham(std::vector<point>::iterator begin,
                             std::vector<point>::iterator end,
                             std::size_t n_threads) {
  if (n_threads == 0) {
    throw "incorrect number of threads";
  }

  int step = (end - begin) / n_threads;
  std::vector<point> last_points;

#pragma omp parallel num_threads(n_threads)
  {
    std::size_t t_number = omp_get_thread_num();
    std::vector<point> local_scan;

    if (t_number == n_threads - 1) {
      local_scan = Graham(begin + step * t_number, end);
    } else {
      local_scan =
          Graham(begin + step * t_number, begin + step * (t_number + 1));
    }
#pragma omp critical
    {
      for (std::size_t i = 0; i < local_scan.size(); ++i) {
        last_points.push_back(local_scan[i]);
      }
    }
  }
  return Graham(last_points.begin(), last_points.end());
}
