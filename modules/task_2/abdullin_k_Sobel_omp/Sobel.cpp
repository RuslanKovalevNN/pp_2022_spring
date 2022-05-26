// Copyright 2022 Abdullin Konstantin
#include <omp.h>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>

#include "../../../modules/task_2/abdullin_k_Sobel_omp/Sobel.h"

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
  int height, int width, int x, int y) {
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
        source, height, width, x, y);

  return result;
}

std::vector<int> ParallelSobelFilter(const std::vector<int>&
  source, int height, int width, std::size_t num_threads) {
  omp_set_num_threads(num_threads);
  std::vector<int> result(height * width);
  std::size_t part_size = source.size() / num_threads;
  std::size_t shift = source.size() % num_threads;
  std::vector<int> part;
#pragma omp parallel shared(source, shift) private(part)
  {
    std::size_t thread_id = omp_get_thread_num();
    if (thread_id == 0) {
      part.resize(part_size + shift);
      std::copy(source.begin(), source.begin() + part_size + shift,
        part.begin());
    } else {
      part.resize(part_size);
    }
    for (std::size_t i = 1; i < num_threads; i++) {
      if (thread_id == i) {
        std::copy(source.begin() + part_size * i + shift, source.end() -
          part_size * (num_threads - i - 1), part.begin());
      }
    }
    for (std::size_t i = 0; i < part.size(); i++) {
      int x, y;
      if (thread_id > 0) {
        x = static_cast<int>(thread_id * part_size + shift + i) % width;
        y = static_cast<int>(thread_id * part_size + shift + i) / width;
      } else {
        x = static_cast<int>(i) % width; y = static_cast<int>(i) / width;
      }
      part[i] = CalculatePixelValue(source, height, width, x, y);
    }
    if (thread_id == 0) {
      for (std::size_t i = 0; i < part.size(); i++) {
        result[i] = part[i];
      }
    } else {
      for (std::size_t i = 0; i < part.size(); i++) {
        result[part_size * thread_id + shift + i] = part[i];
      }
    }
    part.clear();
  }
  return result;
}
