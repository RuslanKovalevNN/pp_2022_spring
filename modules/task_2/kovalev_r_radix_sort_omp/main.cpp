// Copyright 2022 Kovalev Ruslan
#include <gtest/gtest.h>
#include <omp.h>
#include <time.h>

#include <vector>

#include "./radix_sort_omp.h"

TEST(Sequential_algorithm, radix_sort_1) {
  std::vector<int> vec_1(101);
  std::vector<int> vec_2(101);
  vec_gen(&vec_1, 101);
  vec_2 = vec_1;
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 101);
  vec_2 = Odd_Even_Merge(vec_2, 101);
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Sequential_algorithm, radix_sort_2) {
  std::vector<int> vec_1(40);
  std::vector<int> vec_2(40);
  vec_gen(&vec_1, 40);
  vec_2 = vec_1;
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 40);
  vec_2 = Odd_Even_Merge(vec_2, 40);
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Sequential_algorithm, radix_sort_3) {
  std::vector<int> vec_1(100);
  std::vector<int> vec_2(100);
  vec_gen(&vec_1, 100);
  vec_2 = vec_1;
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 100);
  vec_2 = Odd_Even_Merge(vec_2, 100);
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Sequential_algorithm, radix_sort_4) {
  std::vector<int> vec_1(90);
  std::vector<int> vec_2(90);
  vec_gen(&vec_1, 90);
  vec_2 = vec_1;
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 90);
  vec_2 = Odd_Even_Merge(vec_2, 90);
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Sequential_algorithm, radix_sort_5) {
  std::vector<int> vec_1(30);
  std::vector<int> vec_2(30);
  vec_gen(&vec_1, 30);
  vec_2 = vec_1;
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 30);
  vec_2 = Odd_Even_Merge(vec_2, 30);
  ASSERT_EQ(vec_1, vec_2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
