// Copyright 2022 Feoktistov Andrei
#include <gtest/gtest.h>
#include <omp.h>
#include <vector>
#include<random>
#include "./gauss_block.h"



TEST(GaussianFilterBlock, Test_Random_Pixel) {
  const int width = 50;
  const int height = 50;
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<Pixel> img = generateImage(width, height, 2);
  std::vector<float> kernel = createGaussKernel(1, 1.2);
  std::vector<Pixel> rez = parallelGauss(img, width, height, kernel);
  int x = gen() % (width);
  int y = gen() % (height);
  ASSERT_EQ(rez[y*height+x], Pixel::calcNewPixel(x, y, kernel, width,
    height, img));
}
TEST(GaussianFilterBlock, Test_Large_Image) {
  const int width = 300;
  const int height = 300;
  double start = 0;
  double finish = 0;
  std::vector<Pixel> img = generateImage(width, height, 2);
  std::vector<float> kernel = createGaussKernel(1, 1.2);
  start = omp_get_wtime();
  std::vector<Pixel> rez = sequentialGauss(img, width, height, kernel);
  finish = omp_get_wtime();
  std::cout << "Time_Elapsed_SEQ: " << finish - start << std::endl;
  start = omp_get_wtime();
  std::vector<Pixel> rezp = parallelGauss(img, width, height, kernel);
  finish = omp_get_wtime();
  std::cout << "Time_Elapsed_Parallel: " << finish - start << std::endl;
  ASSERT_EQ(rez, rezp);
}
TEST(GaussianFilterBlock, Test_Zero_Pixels) {
  const int width = 50;
  const int height = 50;
  std::vector<Pixel> img = generateImage(width, height, 2);
  std::vector<float> kernel = createGaussKernel(1, 1.2);
  EXPECT_ANY_THROW(generateImage(0, 50, 2));
  EXPECT_ANY_THROW(generateImage(0, 0, 2));
  EXPECT_ANY_THROW(generateImage(50, 0, 2));
  EXPECT_ANY_THROW(generateImage(0, -50, 2));
  EXPECT_ANY_THROW(sequentialGauss(img, 0, 0, kernel));
  EXPECT_ANY_THROW(parallelGauss(img, 0, 0, kernel));
}
TEST(GaussianFilterBlock, Test_Small_Image) {
  const int width = 3;
  const int height = 3;
  std::vector<Pixel> img = generateImage(width, height, 2);
  std::vector<float> kernel = createGaussKernel(1, 1.2);
  std::vector<Pixel> rez = sequentialGauss(img, width, height, kernel);
  std::vector<Pixel> rezp = parallelGauss(img, width, height, kernel);
  ASSERT_EQ(rez, rezp);
}
TEST(GaussianFilterBlock, Test_Wrong_Thread_Count) {
  const int width = 30;
  const int height = 30;
  std::vector<Pixel> img = generateImage(width, height, 2);
  std::vector<float> kernel = createGaussKernel(1, 1.2);
  EXPECT_ANY_THROW(parallelGauss(img, width , height , kernel, 0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

    return 0; }
