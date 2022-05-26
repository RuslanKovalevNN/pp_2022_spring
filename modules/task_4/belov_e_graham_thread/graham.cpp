// Copyright 2022 Belov Egor
#include "../../../modules/task_4/belov_e_graham_thread/graham.h"

#include <algorithm>
#include <ctime>
#include <random>
#include <utility>
#include <vector>
#include <thread> // NOLINT
#include <mutex> // NOLINT

bool rotate(const Point& A, const Point& B, const Point& C) {
  return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x) >= 0;
}

bool comp(const Point& A, const Point& B) {
  return B.x * (A.y - B.y) - B.y * (A.x - B.x) < 0 ||
         (B.x * (A.y - B.y) - B.y * (A.x - B.x) == 0 &&
          A.x * A.x + A.y * A.y < B.x * B.x + B.y * B.y);
}

std::vector<Point> Graham(std::vector<Point>::iterator begin,
                          std::vector<Point>::iterator end) {
  std::vector<Point> tmp(end - begin);
  std::copy(begin, end, tmp.begin());
  int l = 0;
  for (size_t i = 1; i < tmp.size(); i++) {
    if ((tmp[i].y < tmp[l].y) ||
        ((tmp[i].y == tmp[l].y) && (tmp[i].x < tmp[l].x)))
      l = i;
  }
  std::swap(tmp[0], tmp[l]);
  Point p = tmp[0];

  for (size_t i = 0; i < tmp.size(); i++) {
    tmp[i].x -= p.x;
    tmp[i].y -= p.y;
  }
  std::sort(tmp.begin() + 1, tmp.end(), &comp);

  std::vector<Point> res;
  res.push_back(tmp[0]);
  res.push_back(tmp[1]);

  size_t i = 2, j = 0;
  do {
    Point t = tmp[i];

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

std::vector<Point> RandPoint(int n) {
  std::vector<Point> res(n);
  std::mt19937 gen;
  for (int i = 0; i < n; i++) {
    res[i].x = gen() % 10000;
    res[i].y = gen() % 10000;
  }
  return res;
}

std::vector<Point> ThreadGraham(std::vector<Point> tmp, std::size_t n_threads) {
  auto begin = tmp.begin();
  auto end = tmp.end();
  if (n_threads == 0) {
    throw "incorrect number of threads";
  }
  std::thread* threads = new std::thread[n_threads];
  std::mutex m;

  int step = (end - begin) / n_threads;
  std::vector<Point> last_points;

  for (std::size_t i = 0; i < n_threads - 1; ++i) {
    threads[i] = std::thread([&last_points, i, begin, step, &m]() {
      auto left = begin + step * i;
      auto right = begin + step * (i + 1);
      auto local_scan = Graham(left, right);
      for (std::size_t j = 0; j < local_scan.size(); ++j) {
        m.lock();
        last_points.push_back(local_scan[j]);
        m.unlock();
      }
    });
  }
  threads[n_threads - 1] =
      std::thread([&last_points, begin, end, n_threads, step, &m]() {
        auto local_scan = Graham(begin + step * (n_threads - 1), end);
        for (std::size_t j = 0; j < local_scan.size(); ++j) {
          m.lock();
          last_points.push_back(local_scan[j]);
          m.unlock();
        }
      });
  for (std::size_t i = 0; i < n_threads; ++i) {
    threads[i].join();
  }
  delete[] threads;
  return Graham(last_points.begin(), last_points.end());
}
