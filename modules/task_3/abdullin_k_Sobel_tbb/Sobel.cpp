// Copyright 2022 Abdullin Konstantin
#include <tbb/blocked_range.h>
#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>
#include <tbb/task_scheduler_init.h>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>

#include "../../../modules/task_3/abdullin_k_Sobel_tbb/Sobel.h"

int Kernel[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
int radius = 1, size = 3;

std::vector<int> InitRandMatrix(int height, int width) {
  if (height <= 0 || width <= 0)
    throw "Size of matrix error!";
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<int> result(height * width);
  for (int i = 0; i < height * width; i++)
    result[i] = gen() % 256;
  return result;
}

int Index(int x, int y, int width) {
  int result = y * width + x;
  return result;
}

int CalculatePixelValue(const std::vector<int>& source,
  int width, int x, int y) {
  int height = source.size() / width;
  int pixel = 0;
  for (int i = -radius; i <= radius; i++)
    for (int j = -radius; j <= radius; j++) {
      int idx = (i + radius) * size + (j + radius);
      int index = Index(clamp(x + j, width - 1, 0),
        clamp(y + i, height - 1, 0), width);
      pixel += Kernel[idx] * source[index];
    }
  return clamp(pixel, 255, 0);
}

std::vector<int> SequentialSobelFilter(const std::vector<int>&
  source, int height, int width) {
  std::vector<int> result(height * width);

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
      result[Index(x, y, width)] = CalculatePixelValue(
        source, width, x, y);

  return result;
}

std::vector<int> ParallelSobelFilter(const std::vector<int>&
  source, int height, int width) {
  std::vector<int> result(source.size());

  tbb::parallel_for(tbb::blocked_range<size_t>(0, source.size()),
    [&](const tbb::blocked_range<size_t>& r) {
      for (size_t i = r.begin(); i != r.end(); i++) {
        int x, y;
        y = (i) / width;
        x = (i) % width;
        result[i] = CalculatePixelValue(source, width, x, y);
      }
    });
  return result;
}
