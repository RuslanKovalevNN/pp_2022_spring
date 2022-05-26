// Copyright 2022 Kim Nikita
#include <gtest/gtest.h>
// #include <tbb/tick_count.h>
#include <vector>
#include "./radix_sort.h"

TEST(TBB, Vector_One_Size) {
  int size = 1;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(TBB, Vector_Two_Size) {
  int size = 2;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(TBB, Vector_Odd_Size) {
  int size = 21;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(TBB, Vector_Even_Size) {
  int size = 20;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(TBB, Vector_Odd_Large_Size) {
  int size = 121;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(TBB, Vector_Even_Large_Size) {
  int size = 120;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(TBB, Vector_Mega_Large_Size) {
  int size = 1000003;
  // tbb::tick_count t1, t2;
  // double t1_res, t2_res;
  std::vector<int> input_vec = getRandomVector(size);

  // t1 = tbb::tick_count::now();
  std::vector<int> exp_res = radixSort(input_vec, size);
  // t1_res = (tbb::tick_count::now() - t1).seconds();

  // t2 = tbb::tick_count::now();
  std::vector<int> res = radixSortParallel(input_vec, size);
  // t2_res = (tbb::tick_count::now() - t2).seconds();

  ASSERT_EQ(exp_res, res);
  // EXPECT_EQ(t1_res / t2_res, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
