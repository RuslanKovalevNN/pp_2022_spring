// Copyright 2022 Sablin Alexandr
#include <gtest/gtest.h>
#include "../../../modules/task_4/sablin_a_gaussian_vert/gaussian_vert.h"

TEST(Gaussian_Filter_vertical, Test_Zero_Pixels_and_Sigma) {
  std::vector<rgb_coub> img = getRandomImage(1, 1);
  EXPECT_ANY_THROW(Gaussian_Filter_Thread(img, 0, 0, 1));
  EXPECT_ANY_THROW(Gaussian_Filter_Thread(img, 0, 1, 1));
  EXPECT_ANY_THROW(Gaussian_Filter_Thread(img, 1, 0, 1));
  EXPECT_ANY_THROW(Gaussian_Filter_Thread(img, 1, 1, 0));
  EXPECT_ANY_THROW(getRandomImage(0, 0));
}

TEST(Gaussian_Filter_vertical, Test_Different_Rows_and_Columns) {
  int rows = 120, columns = 8;
  const double sigma = 2.0;
  std::vector<rgb_coub> image = getRandomImage(rows, columns);
  auto t1 = clock();
  std::vector<rgb_coub> res1 =
      Gaussian_Filter_Seq(image, rows, columns, sigma);
  auto t2 = clock();
  std::vector<rgb_coub> res2 =
      Gaussian_Filter_Thread(image, rows, columns, sigma);
  auto t3 = clock();
  std::cout << "Time Seq: " << static_cast<float>(t2 - t1) / CLOCKS_PER_SEC
            << std::endl;
  std::cout << "Time Thread: " << static_cast<float>(t3 - t2) / CLOCKS_PER_SEC
            << std::endl;
  std::cout << "Efficiency: "
            << (static_cast<float>(t2 - t1) / CLOCKS_PER_SEC) /
                   (static_cast<float>(t3 - t2) / CLOCKS_PER_SEC)
            << std::endl;
  ASSERT_EQ(res1, res2);
}

TEST(Gaussian_Filter_vertical, Test_Big_Image) {
  int rows = 300, columns = 300;
  const double sigma = 2.0;
  std::vector<rgb_coub> image = getRandomImage(rows, columns);
  auto t1 = clock();
  std::vector<rgb_coub> res1 =
      Gaussian_Filter_Seq(image, rows, columns, sigma);
  auto t2 = clock();
  std::vector<rgb_coub> res2 =
      Gaussian_Filter_Thread(image, rows, columns, sigma);
  auto t3 = clock();
  std::cout << "Time Seq: " << static_cast<float>(t2 - t1) / CLOCKS_PER_SEC
            << std::endl;
  std::cout << "Time Thread: " << static_cast<float>(t3 - t2) / CLOCKS_PER_SEC
            << std::endl;
  std::cout << "Efficiency: "
            << (static_cast<float>(t2 - t1) / CLOCKS_PER_SEC) /
                   (static_cast<float>(t3 - t2) / CLOCKS_PER_SEC)
            << std::endl;
  ASSERT_EQ(res1, res2);
}

TEST(Gaussian_Filter_vertical, Test_One_Pixel) {
  int rows = 1, columns = 1;
  const double sigma = 2.0;
  std::vector<rgb_coub> image = getRandomImage(rows, columns);
  std::vector<rgb_coub> copy(image);
  image = Gaussian_Filter_Thread(image, rows, columns, sigma);
  ASSERT_EQ(image, copy);
}

TEST(Gaussian_Filter_vertical, Test_Const_Image) {
  int rows = 3, columns = 3;
  const double sigma = 2.0;
  std::vector<rgb_coub> true_result(rows * columns);
  true_result[0].red = true_result[0].green = true_result[0].blue = 85;
  true_result[1].red = true_result[1].green = true_result[1].blue = 99;
  true_result[2].red = true_result[2].green = true_result[2].blue = 112;
  true_result[3].red = true_result[3].green = true_result[3].blue = 126;
  true_result[4].red = true_result[4].green = true_result[4].blue = 140;
  true_result[5].red = true_result[5].green = true_result[5].blue = 153;
  true_result[6].red = true_result[6].green = true_result[6].blue = 167;
  true_result[7].red = true_result[7].green = true_result[7].blue = 180;
  true_result[8].red = true_result[8].green = true_result[8].blue = 194;
  std::vector<rgb_coub> image(rows * columns);
  for (int i = 0; i < rows * columns; i++) {
    image[i].red = 60 + i * 20;
    image[i].green = 60 + i * 20;
    image[i].blue = 60 + i * 20;
  }
  image = Gaussian_Filter_Thread(image, rows, columns, sigma);
  ASSERT_EQ(image, true_result);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
