// Copyright 2022 Abdullin Konstantin
#ifndef MODULES_TASK_1_ABDULLIN_K_SOBEL_SOBEL_H_
#define MODULES_TASK_1_ABDULLIN_K_SOBEL_SOBEL_H_

#include <vector>
#include <random>
#include <ctime>

std::vector<int> InitRandMatrix(int height, int width);
template <class T>
T clamp(T value, T max, T min) {
  if (value > max)
    return max;
  if (value < min)
    return min;
  return value;
}
int Index(int x, int y, int height);
std::vector<int> xSobelFilter(std::vector<int> source,
  int height, int width);

#endif  // MODULES_TASK_1_ABDULLIN_K_SOBEL_SOBEL_H_
