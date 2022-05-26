// Copyright 2022 Abdullin Konstantin
#include "../../../modules/task_1/abdullin_k_Sobel/Sobel.h"
#include <iostream>

std::vector<int> InitRandMatrix(int height, int width) {
  if (height <= 0 || width <= 0)
    throw "Size of matrix error!";
  std::mt19937 gen;
  gen.seed(static_cast<int>(time(0)));
  std::vector<int> result(height * width);
  for (int i = 0; i < height * width; i++)
    result[i] = gen() % 256;
  return result;
}

int Index(int x, int y, int width) {
  int result = y * width + x;
  return result;
}

std::vector<int> xSobelFilter(std::vector<int> source,
  int height, int width) {
  std::vector<int> result(height * width);
  int Kernel[9];
  int radius = 1, size = 3;
  Kernel[0] = -1, Kernel[1] = 0, Kernel[2] = 1,
    Kernel[3] = -2, Kernel[4] = 0, Kernel[5] = 2,
    Kernel[6] = -1, Kernel[7] = 0, Kernel[8] = 1;

  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++) {
      int pixel = 0;
      for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
          int idx = (i + radius) * size + (j + radius);
          int index = Index(clamp(x + j, width - 1, 0),
            clamp(y + i, height - 1, 0), width);
          pixel += Kernel[idx] * source[index];
        }
      result[Index(x, y, width)] = clamp(pixel, 255, 0);
    }

  return result;
}
