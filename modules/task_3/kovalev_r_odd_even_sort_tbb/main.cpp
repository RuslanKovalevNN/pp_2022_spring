// Copyright 2022 Kovalev Ruslan

#include <gtest/gtest.h>
#include <vector>
#include "./odd_even_sort_tbb.h"

using std::vector;

TEST(Parallel, Get_Max) {
  vector<int> vec_1(100);
  vector<int> vec_2(100);
  vec_gen(&vec_1,100);
  vec_2 = vec_1;
  ParalleGetMax(&vec_1, 100);
  getMax(&vec_2, 100);
  ASSERT_EQ(vec_1,vec_2);
}

TEST(Parallel, Radix_Sort) {
  vector<int> vec_1(30);
  vector<int> vec_2(30);
  vec_gen(&vec_1, 30);
  vec_2 = vec_1;
  getSortParallel(&vec_1, 30);
  getSequantialSort(&vec_2, 30);
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Parallel, Counting_Sort) {
  vector<int> vec_1(20000);
  vector<int> vec_2(20000);
  vec_gen(&vec_1, 20000);
  vec_2 = vec_1;
  countingSort(&vec_1, 20000, 3);
  countingSortParallel(&vec_2, 20000, 3);
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Parallel, Odd_Even_Sort_1) {
  vector<int> vec_1(10);
  vec_gen(&vec_1, 10);
  vector<int> vec_2 = vec_1;
  Odd_Even_Merge_Parallel(vec_1, 10);
  Odd_Even_Merge(vec_2, 10);
  ASSERT_EQ(vec_1, vec_2);
}


TEST(Parallel, Odd_Even_Sort_2) {
  vector<int> vec_1(100);
  vec_gen(&vec_1, 100);
  vector<int> vec_2 = vec_1;
  Odd_Even_Merge_Parallel(vec_1, 100);
  Odd_Even_Merge(vec_2, 100);
  ASSERT_EQ(vec_1, vec_2);
}


/*
TEST(Parallel, Odd_Even_Sort_3) {
  vector<int> vec_1(1000000);
  vec_gen(&vec_1, 1000000);
  vector<int> vec_2 = vec_1;
  Odd_Even_Merge_Parallel(vec_1, 1000000);
  Odd_Even_Merge(vec_2, 1000000);
  ASSERT_EQ(vec_1, vec_2);
}
*/

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
