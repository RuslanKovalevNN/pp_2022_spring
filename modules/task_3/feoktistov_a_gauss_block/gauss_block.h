// Copyright 2022 Feoktistov Andrei
#ifndef MODULES_TASK_3_FEOKTISTOV_A_GAUSS_BLOCK_GAUSS_BLOCK_H_
#define MODULES_TASK_3_FEOKTISTOV_A_GAUSS_BLOCK_GAUSS_BLOCK_H_
#include <tbb/tbb.h>
#include <string>
#include <vector>

class Pixel {
 public:
  Pixel();
  Pixel(float R, float G, float B);
  ~Pixel();
  float getR() const { return red; }
  float getG() const { return green; }
  float getB() const { return blue; }

  Pixel& operator=(const Pixel& pixel) {
    red = pixel.red;
    green = pixel.green;
    blue = pixel.blue;
    return *this;
  }

  friend bool operator==(const Pixel& pixel, const Pixel& pixel2) {
    if ((pixel.red == pixel2.red) && (pixel.green == pixel2.green) &&
        (pixel.blue == pixel2.blue)) {
      return true;
    } else {
      return false;
    }
  }
  Pixel static calcNewPixel(const int x, const int y,
                            const std::vector<float>& kernel, const int width,
                            const int height, const std::vector<Pixel>& img);

 private:
  float red;
  float green;
  float blue;
};

std::vector<float> createGaussKernel(int radius, float sigma);
std::vector<Pixel> generateImage(int width, int heigh, int step);
std::vector<Pixel> sequentialGauss(const std::vector<Pixel>& img, int width,
                                   int height,
                                   const std::vector<float>& kernel);
std::vector<Pixel> parallelGauss(const std::vector<Pixel>& img, int width,
                                 int height, const std::vector<float>& kernel,
                                 const int num_threads = 4);

class GaussBlur {
  const std::vector<Pixel>* img;
  const std::vector<float>* kernel;
  std::vector<Pixel>* rez;
  int height = 0;
  int width = 0;

 public:
  GaussBlur(const std::vector<Pixel>& image, int x, int y,
    const std::vector<float>& kern, std::vector<Pixel>* result);
  void operator()(const tbb::blocked_range2d<int, int>& r) const;
};

#endif  // MODULES_TASK_3_FEOKTISTOV_A_GAUSS_BLOCK_GAUSS_BLOCK_H_
