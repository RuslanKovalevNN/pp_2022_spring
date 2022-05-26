// Copyright 2022 Abdullin Konstantin
#include <gtest/gtest.h>
#include "./Sobel.h"

TEST(Sobel, Calculating_index_is_correct) {
  int x = 11, y = 13, w = 20;
  EXPECT_EQ(Index(x, y, w), 271);
}

TEST(Sobel, Clamp_max_is_correct) {
  EXPECT_EQ(clamp(256, 255, 0), 255);
}

TEST(Sobel, Clamp_min_is_correct) {
  EXPECT_EQ(clamp(-1, 255, 0), 0);
}

TEST(Sobel, InitRandMatrix_throw1) {
  ASSERT_ANY_THROW(InitRandMatrix(0, 1));
}

TEST(Sobel, InitRandMatrix_throw2) {
  ASSERT_ANY_THROW(InitRandMatrix(1, 0));
}

TEST(Sobel, Filter_is_correct) {
  std::vector<int> a = {44, 222, 87, 124, 0, 172, 218, 45, 87,
    17, 116, 211, 118, 228, 74, 143};
  int h = 4, w = 4;
  std::vector<int> result = xSobelFilter(a, h, w);
  std::vector<int> check = {255, 255, 0, 0, 255, 255, 0, 0,
    142, 232, 176, 86, 255, 0, 0, 255};
  EXPECT_EQ(result, check);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
