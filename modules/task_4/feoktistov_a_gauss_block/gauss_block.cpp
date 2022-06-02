// Copyright 2022 Feoktistov Andrei
#define _USE_MATH_DEFINES
#include <vector>
#include <string>
#include <utility>
#include <random>
#include <iostream>
#include "../../../modules/task_4/feoktistov_a_gauss_block/gauss_block.h"
#include "../../../3rdparty/unapproved/unapproved.h"


std::vector<Pixel> generateImage(int width, int height, int step) {
  if (width <= 0 || height <= 0) {
    throw "zero_pixel_exeption";
  }
  int PixelCount = width * height;
  std::vector<Pixel> img(PixelCount);
  for (int i = 0; i < width * height; i++) {
    img[i] = Pixel(255.0f * ((i % width) % step > 0),
                   255.0f * ((i % width) % (step + 1) > 0),
                   255.0f * ((i % width) % (step + 2) > 0));
    // std::cout << img[i].getR() << " " << img[i].getG() << " "
    // << img[i].getB()<< " ";
    // if (i % width == width-1) std::cout << std::endl;
  }

  return img;
}
std::vector<float> createGaussKernel(int radius, float sigma) {
  if (sigma == 0) {
    throw "zero_sigma_exeption";
  }
  int size = 2 * radius + 1;
  std::vector<float> res(pow(size, 2));
  float norm = 0;
  for (int x = -radius; x <= radius; x++)
    for (int y = -radius; y <= radius; y++) {
      int k = (x + radius) * size + (y + radius);
      res[k] = 1 / (2 * M_PI * sigma * sigma) *
               std::exp(-(x * x + y * y) / (2 * sigma * sigma));
      norm += res[k];
    }

  for (int i = 0; i < size * size; i++) {
    res[i] /= norm;
  }

  return res;
}

Pixel Pixel::calcNewPixel(const int x, const int y,
                          const std::vector<float>& kernel, const int width,
                          const int height, const std::vector<Pixel>& img) {
  int radius = sqrt(kernel.size()) / 2;
  if (radius == 0) {
    int N = y * width + x;
    return img[N];
  }
  float R = 0;
  float G = 0;
  float B = 0;

  for (int i = -radius; i <= radius; i++)
    for (int j = -radius; j <= radius; j++) {
      int kern = (i + radius) * (2 * radius + 1) + j + radius;

      if (x + j >= 0 && x + j < width && y + i >= 0 && y + i < height) {
        int pixelNumber = (y + i) * width + x + j;

        R += (img[pixelNumber].getR() * kernel[kern]);
        G += (img[pixelNumber].getG() * kernel[kern]);
        B += (img[pixelNumber].getB() * kernel[kern]);
      }
    }

  return Pixel(R, G, B);
}

Pixel::Pixel() {
  red = 0;
  green = 0;
  blue = 0;
}
Pixel::Pixel(float R, float G, float B) {
  if (R < 256) {
    red = R;
  } else {
    red = 255;
  }
  if (G < 256) {
    green = G;
  } else {
    green = 255;
  }
  if (B < 256) {
    blue = B;
  } else {
    blue = 255;
  }
}
Pixel::~Pixel() {}



std::vector<Pixel> sequentialGauss(const std::vector<Pixel>& img, int width,
                                   int height,
                                   const std::vector<float>& kernel) {
  unsigned int PixelCount = abs(width * height);
  if (width < 0 || height < 0 || PixelCount < img.size()) {
    throw "wrong_pixel_number";
  }

  std::vector<Pixel> result(PixelCount);
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int pixelNumber = y * width + x;
      Pixel newPixel = Pixel::calcNewPixel(x, y, kernel, width, height, img);
      result[pixelNumber] = newPixel;
    }
  }
  return result;
}

void ProcessPart(const std::vector<Pixel>& img, int width, int height,
                 const std::vector<int>& bounds,
                 const std::vector<float>& kernel,
                  std::vector<Pixel>* res) {
  for (int i = 0; i < static_cast<int>(bounds.size()); i = i + 4) {
    for (int y = bounds[i + 1]; y < bounds[i + 3]; y++) {
      for (int x = bounds[i]; x < bounds[i + 2]; x++) {
        int pixelNumber = y * width + x;
        Pixel newPixel = Pixel::calcNewPixel(x, y, kernel, width, height, img);
        res[0][pixelNumber] = newPixel;
      }
    }
  }
}

std::vector<Pixel> parallelGauss(const std::vector<Pixel>& img, int width,
                                 int height, const std::vector<float>& kernel,
                                 const int num_threads) {
  unsigned int PixelCount = abs(width * height);
  if (width < 0 || height < 0 || PixelCount < img.size()) {
    throw "wrong_pixel_number";
  }
  if (num_threads <= 0) {
    throw "ERROR: number of threads <= 0";
  }
  std::vector<Pixel> result(PixelCount);
  int clusterw = std::max(1, width / (num_threads));
  int clusterh = std::max(1, height / (num_threads));
  std::vector<std::thread> threads;
  std::vector<std::vector<int>> bounds(num_threads);
  int numOfThread = 0;

  for (int i = 0; i < height; i += clusterh) {
    for (int j = 0; j < width; j += clusterw) {
      bounds[numOfThread].push_back(j);
      bounds[numOfThread].push_back(i);
      if ((width - (j + clusterw)) < clusterw) {
        bounds[numOfThread].push_back(width);
      } else {
        bounds[numOfThread].push_back(j + clusterw);
      }
      if ((height - (i + clusterh)) < clusterh) {
        bounds[numOfThread].push_back(height);
      } else {
        bounds[numOfThread].push_back(i + clusterh);
      }
      if (numOfThread == num_threads-1) {
        numOfThread = 0;
      } else {
        numOfThread++;
      }
    }
  }
  for (int i = 0; i < num_threads; i++) {
    threads.push_back(std::thread(ProcessPart, img, width, height,
      bounds[i], kernel, &result));
  }
  for (int i = 0; i < num_threads; i++) {
    threads[i].join();
  }


  return result;
}
