// Copyright 2022 Feoktistov Andrei
#define _USE_MATH_DEFINES
#include "../../../modules/task_3/feoktistov_a_gauss_block/gauss_block.h"
#include <math.h>
#include <tbb/tbb.h>
#include <functional>
#include <numeric>
#include <random>
#include <string>
#include <vector>


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


GaussBlur::GaussBlur(const std::vector<Pixel>& image, int x, int y,
  const std::vector<float>& kern, std::vector<Pixel>* result) {
  img = &image;
  kernel = &kern;
  rez = result;
  height = y;
  width = x;
}
void  GaussBlur::operator()(const tbb::blocked_range2d<int, int>& r) const {
  int colbegin = r.cols().begin();
  int colend = r.cols().end();
  int rowbegin = r.rows().begin();
  int rowend = r.rows().end();
  for (int y = colbegin; y < colend; y++) {
    for (int x = rowbegin; x < rowend; x++) {
      int pixelNumber = y * width + x;
      Pixel newPixel = Pixel::calcNewPixel(x, y, *kernel, width, height, *img);
      rez[0][pixelNumber] = newPixel;
    }
  }
}

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
  tbb::task_scheduler_init init(num_threads);
  int grainsize1 = width / num_threads;
  int grainsize2 = height / num_threads;
  if (grainsize1 == 0) grainsize1 = 1;
  if (grainsize2 == 0) grainsize2 = 1;

  std::vector<Pixel> result(PixelCount);
  tbb::parallel_for(tbb::blocked_range2d<int>(0, width, grainsize1 , 0,
                                              height, grainsize2),
                    GaussBlur(img, width, height, kernel, &result));

  return result;
}
