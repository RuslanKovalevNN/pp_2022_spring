// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <vector>
#include<random>
#include<fstream>
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
  ASSERT_EQ(rez[y * height + x],
            Pixel::calcNewPixel(x, y, kernel, width, height, img));
}
TEST(GaussianFilterBlock, Test_Large_Image) {
  const int width = 300;
  const int height = 300;
  tbb::tick_count start;
  tbb::tick_count finish;
  std::vector<Pixel> img = generateImage(width, height, 2);
  /*std::ofstream outfile("C:\\Feoandrew\\image.txt");
  //outfile << width << std::endl;
  //outfile << height << std::endl;
  //for each (Pixel p in img) {
   // outfile << p.getR() << " " << p.getG() << " " << p.getB() << " ";
  }*/
  std::vector<float> kernel = createGaussKernel(1, 1.2);
  start = start.now();
  std::vector<Pixel> rez = sequentialGauss(img, width, height, kernel);
  finish = finish.now();
  std::cout << "Time_Elapsed_SEQ: " << (finish - start).seconds() << std::endl;
  start = start.now();
  std::vector<Pixel> rezp = parallelGauss(img, width, height, kernel);
  finish = finish.now();
  std::cout << "Time_Elapsed_Parallel: " << (finish - start).seconds()
            << std::endl;
 /* std::ofstream outfile1("C:\\Feoandrew\\image2.txt");
 // outfile1 << width << std::endl;
 // outfile1 << height << std::endl;
 // for each( Pixel p in rezp) {
 //   outfile1 << p.getR() << " " << p.getG() << " " << p.getB() << " ";
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
