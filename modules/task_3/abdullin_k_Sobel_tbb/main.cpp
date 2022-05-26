// Copyright 2022 Abdullin Konstantin
#include <gtest/gtest.h>
#include <tbb/tick_count.h>
#include <vector>
#include <iostream>
#include "./Sobel.h"

TEST(Sobel, Parallel_filter_20x18) {
  std::vector<int> a = InitRandMatrix(20, 18);
  tbb::tick_count start = tbb::tick_count::now();
  std::vector<int> seq_result = SequentialSobelFilter(a, 20, 18);
  tbb::tick_count finish = tbb::tick_count::now();
  float seq_time = (finish - start).seconds();
  start = tbb::tick_count::now();
  std::vector<int> par_result = ParallelSobelFilter(a, 20, 18);
  finish = tbb::tick_count::now();
  float par_time = (finish - start).seconds();
  std::cout << "S: " << seq_time << " P: " << par_time <<
    " Efficiency: " << seq_time / par_time << std::endl;
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

TEST(Sobel, Parallel_filter_65x15) {
  std::vector<int> a = InitRandMatrix(65, 15);
  tbb::tick_count start = tbb::tick_count::now();
  std::vector<int> seq_result = SequentialSobelFilter(a, 65, 15);
  tbb::tick_count finish = tbb::tick_count::now();
  float seq_time = (finish - start).seconds();
  start = tbb::tick_count::now();
  std::vector<int> par_result = ParallelSobelFilter(a, 65, 15);
  finish = tbb::tick_count::now();
  float par_time = (finish - start).seconds();
  std::cout << "S: " << seq_time << " P: " << par_time <<
    " Efficiency: " << seq_time / par_time << std::endl;
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

TEST(Sobel, Parallel_filter_150x90) {
  std::vector<int> a = InitRandMatrix(150, 90);
  tbb::tick_count start = tbb::tick_count::now();
  std::vector<int> seq_result = SequentialSobelFilter(a, 150, 90);
  tbb::tick_count finish = tbb::tick_count::now();
  float seq_time = (finish - start).seconds();
  start = tbb::tick_count::now();
  std::vector<int> par_result = ParallelSobelFilter(a, 150, 90);
  finish = tbb::tick_count::now();
  float par_time = (finish - start).seconds();
  std::cout << "S: " << seq_time << " P: " << par_time <<
    " Efficiency: " << seq_time / par_time << std::endl;
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

TEST(Sobel, Parallel_filter_500x200) {
  std::vector<int> a = InitRandMatrix(500, 200);
  tbb::tick_count start = tbb::tick_count::now();
  std::vector<int> seq_result = SequentialSobelFilter(a, 500, 200);
  tbb::tick_count finish = tbb::tick_count::now();
  float seq_time = (finish - start).seconds();
  start = tbb::tick_count::now();
  std::vector<int> par_result = ParallelSobelFilter(a, 500, 200);
  finish = tbb::tick_count::now();
  float par_time = (finish - start).seconds();
  std::cout << "S: " << seq_time << " P: " << par_time <<
    " Efficiency: " << seq_time / par_time << std::endl;
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

TEST(Sobel, Parallel_filter_1612x534) {
  std::vector<int> a = InitRandMatrix(1612, 534);
  tbb::tick_count start = tbb::tick_count::now();
  std::vector<int> seq_result = SequentialSobelFilter(a, 1612, 534);
  tbb::tick_count finish = tbb::tick_count::now();
  float seq_time = (finish - start).seconds();
  start = tbb::tick_count::now();
  std::vector<int> par_result = ParallelSobelFilter(a, 1612, 534);
  finish = tbb::tick_count::now();
  float par_time = (finish - start).seconds();
  std::cout << "S: " << seq_time << " P: " << par_time <<
    " Efficiency: " << seq_time / par_time << std::endl;
  EXPECT_EQ(seq_result, par_result);
  a.clear(); seq_result.clear(); par_result.clear();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
