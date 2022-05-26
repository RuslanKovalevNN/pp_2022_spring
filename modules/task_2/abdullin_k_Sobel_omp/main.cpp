// Copyright 2022 Abdullin Konstantin
#include <gtest/gtest.h>
#include <vector>
#include "./Sobel.h"

TEST(Sobel, Parallel_filter_3_threads) {
  std::vector<int> a = { 44, 222, 87, 124, 0, 172, 218, 45, 87,
    17, 116, 211, 118, 228, 74, 143 };
  int h = 4, w = 4;
  std::vector<int> seq_result = SequentialSobelFilter(a, h, w);
  std::vector<int> par_result = ParallelSobelFilter(a, h, w, 3);
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

TEST(Sobel, Parallel_filter_4x8_4) {
  std::vector<int> a = InitRandMatrix(4, 8);
  std::vector<int> seq_result = SequentialSobelFilter(a, 4, 8);
  std::vector<int> par_result = ParallelSobelFilter(a, 4, 8, 4);
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

TEST(Sobel, Parallel_filter_11x4_3) {
  std::vector<int> a = InitRandMatrix(11, 4);
  std::vector<int> seq_result = SequentialSobelFilter(a, 11, 4);
  std::vector<int> par_result = ParallelSobelFilter(a, 11, 4, 3);
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

TEST(Sobel, Parallel_filter_4x5_5) {
  std::vector<int> a = InitRandMatrix(4, 5);
  std::vector<int> seq_result = SequentialSobelFilter(a, 4, 5);
  std::vector<int> par_result = ParallelSobelFilter(a, 4, 5, 5);
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

TEST(Sobel, Parallel_filter_6x3_4) {
  std::vector<int> a = InitRandMatrix(6, 3);
  std::vector<int> seq_result = SequentialSobelFilter(a, 6, 3);
  std::vector<int> par_result = ParallelSobelFilter(a, 6, 3, 4);
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
