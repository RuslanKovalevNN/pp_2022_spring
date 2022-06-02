// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include<random>
#include<fstream>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "../../../modules/task_4/feoktistov_a_gauss_block/gauss_block.h"

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
  int pixelnum = y * height + x;
    ASSERT_EQ(rez[pixelnum],
            Pixel::calcNewPixel(x, y, kernel, width, height, img));
}
TEST(GaussianFilterBlock, Test_Large_Image) {
  const int width = 200;
  const int height = 200;
  std::vector<Pixel> img = generateImage(width, height, 2);
  /* std::ofstream outfile("C:\\Feoandrew\\image.txt");
  // outfile << width << std::endl;
  // outfile << height << std::endl;
  for each (Pixel p in img) {
    outfile << p.getR() << " " << p.getG() << " " << p.getB() << " ";
  }*/
  std::vector<float> kernel = createGaussKernel(1, 1.2);
  auto start = std::chrono::steady_clock::now();
  std::vector<Pixel> rez = sequentialGauss(img, width, height, kernel);
  auto finish = std::chrono::steady_clock::now();
  auto elapsed_ms =
    std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
  std::cout << "Time_Elapsed_SEQ: "<< elapsed_ms.count() << std::endl;
  start = std::chrono::steady_clock::now();
  std::vector<Pixel> rezp = parallelGauss(img, width, height, kernel);
  finish = std::chrono::steady_clock::now();
  elapsed_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
  std::cout << "Time_Elapsed_Parallel: " << elapsed_ms.count() << std::endl;
  /*std::ofstream outfile1("C:\\Feoandrew\\image1.txt");
  outfile1 << width << std::endl;
  outfile1 << height << std::endl;
  for each (Pixel p in rezp) {
    outfile1 << p.getR() << " " << p.getG() << " " << p.getB() << " ";
  }*/
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
  EXPECT_ANY_THROW(parallelGauss(img, width, height, kernel, 0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  return 0;
}
