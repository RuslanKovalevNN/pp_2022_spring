// Copyright 2022 Belov Egor
#include "../../../modules/task_3/belov_e_graham_tbb/graham.h"

#include <tbb/tbb.h>
#include <algorithm>
#include <ctime>
#include <random>
#include <utility>
#include <vector>

bool cmp(Point A, Point B) { return A.x < B.x || (A.x == B.x && A.y < B.y); }

bool cw(Point A, Point B, Point C) {
  return A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y) < 0;
}

bool ccw(Point A, Point B, Point C) {
  return A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y) > 0;
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

std::vector<Point> Graham(std::vector<Point>::iterator begin,
                          std::vector<Point>::iterator end) {
  std::vector<Point> tmp(end - begin);
  std::copy(begin, end, tmp.begin());
  sort(tmp.begin(), tmp.end(), &cmp);
  Point p1 = tmp[0], p2 = tmp.back();
  std::vector<Point> arr, res;
  arr.push_back(p1);
  res.push_back(p1);
  for (size_t i = 1; i < tmp.size(); ++i) {
    if (i == tmp.size() - 1 || cw(p1, tmp[i], p2)) {
      while (arr.size() >= 2 && !cw(arr[arr.size() - 2],
        arr[arr.size() - 1], tmp[i]))
        arr.pop_back();
      arr.push_back(tmp[i]);
    }
    if (i == tmp.size() - 1 || ccw(p1, tmp[i], p2)) {
      while (res.size() >= 2 &&
             !ccw(res[res.size() - 2], res[res.size() - 1], tmp[i]))
        res.pop_back();
      res.push_back(tmp[i]);
    }
  }
  tmp.clear();
  for (size_t i = 0; i < arr.size(); ++i) tmp.push_back(arr[i]);
  for (size_t i = res.size() - 2; i > 0; --i) tmp.push_back(res[i]);
  return res;
}

std::vector<Point> TbbGraham(std::vector<Point> tmp, std::size_t threads_num) {
  std::vector<Point> res;
  int step = tmp.size() / threads_num;
  auto begin = tmp.begin();
  auto end = tmp.end();
  tbb::spin_mutex mute;
  tbb::task_group task;

  for (std::size_t i = 0; i < threads_num - 1; ++i) {
    task.run([&res, &mute, i, begin, step]() {
      auto local = Graham(begin + step * i, begin + step * (i + 1));
      for (std::size_t j = 0; j < local.size(); ++j) {
        tbb::spin_mutex::scoped_lock lock;
        lock.acquire(mute);
        res.push_back(local[j]);
        lock.release();
      }
    });
  }
  task.run([&res, begin, end, step, threads_num, &mute]() {
    auto local_scan = Graham(begin + step * (threads_num - 1), end);
    for (std::size_t j = 0; j < local_scan.size(); ++j) {
      tbb::spin_mutex::scoped_lock lock;
      lock.acquire(mute);
      res.push_back(local_scan[j]);
      lock.release();
    }
  });
  task.wait();
  return Graham(res.begin(), res.end());
}
