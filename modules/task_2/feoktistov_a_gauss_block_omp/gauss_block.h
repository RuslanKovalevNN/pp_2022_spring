// Copyright 2022 Feoktistov Andrei
#ifndef MODULES_TASK_2_FEOKTISTOV_A_GAUSS_BLOCK_OMP_GAUSS_BLOCK_H_
#define MODULES_TASK_2_FEOKTISTOV_A_GAUSS_BLOCK_OMP_GAUSS_BLOCK_H_
#include <vector>
#include <string>

class Pixel {
 public:
  Pixel();
  Pixel(float R, float G, float B);
  ~Pixel();
  float getR() const { return red; }
  float getG() const { return green;}
  float getB() const { return blue; }

  Pixel& operator=(const Pixel& pixel) {
    red = pixel.red;
    green = pixel.green;
    blue = pixel.blue;
    return *this;
  }
  friend bool operator == (const Pixel& pixel , const Pixel& pixel2) {
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
                              int height, const std::vector<float>& kernel);
std::vector<Pixel> parallelGauss(const std::vector<Pixel>& img, int width,
                                   int height, const std::vector<float>& kernel,
                                 const int num_threads = 4);

#endif  // MODULES_TASK_2_FEOKTISTOV_A_GAUSS_BLOCK_OMP_GAUSS_BLOCK_H_
