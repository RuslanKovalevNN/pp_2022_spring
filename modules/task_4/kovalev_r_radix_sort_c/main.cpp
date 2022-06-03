// Copyright 2022 Kovalev Ruslan
#include <gtest/gtest.h>
#include <vector>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "./radix_sort_c.h"

TEST(Parallel_Operations_Std_Threads, Test_Radix_Sort_1) {
  std::vector<int> arr_1(40);
  std::vector<int> arr_2(40);
  vec_gen(&arr_1, 40);
  arr_2 = arr_1;
  std::vector<int> arr_3(40);
  std::vector<int> arr_4(40);
  arr_3 = Odd_Even_Merge_Parallel(arr_1, 40);
  arr_4 = Odd_Even_Merge(arr_2, 40);
  ASSERT_EQ(arr_3, arr_4);
}

TEST(Parallel_Operations_Std_Threads, Test_Radix_Sort_2) {
  std::vector<int> arr_1(50);
  std::vector<int> arr_2(50);
  vec_gen(&arr_1, 50);
  arr_2 = arr_1;
  std::vector<int> arr_3(50);
  std::vector<int> arr_4(50);
  arr_3 = Odd_Even_Merge_Parallel(arr_1, 50);
  arr_4 = Odd_Even_Merge(arr_2, 50);
  ASSERT_EQ(arr_3, arr_4);
}

TEST(Parallel_Operations_Std_Threads, Test_Radix_Sort_3) {
  std::vector<int> arr_1(60);
  std::vector<int> arr_2(60);
  vec_gen(&arr_1, 60);
  arr_2 = arr_1;
  std::vector<int> arr_3(60);
  std::vector<int> arr_4(60);
  arr_3 = Odd_Even_Merge_Parallel(arr_1, 60);
  arr_4 = Odd_Even_Merge(arr_2, 60);
  ASSERT_EQ(arr_3, arr_4);
}

TEST(Parallel_Operations_Std_Threads, Test_Radix_Sort_4) {
  std::vector<int> arr_1(70);
  std::vector<int> arr_2(70);
  vec_gen(&arr_1, 70);
  arr_2 = arr_1;
  std::vector<int> arr_3(70);
  std::vector<int> arr_4(70);
  arr_3 = Odd_Even_Merge_Parallel(arr_1, 70);
  arr_4 = Odd_Even_Merge(arr_2, 70);
  ASSERT_EQ(arr_3, arr_4);
}

TEST(Parallel_Operations_Std_Threads, Test_Radix_Sort_5) {
  std::vector<int> arr_1(45);
  std::vector<int> arr_2(45);
  vec_gen(&arr_1, 45);
  arr_2 = arr_1;
  std::vector<int> arr_3(45);
  std::vector<int> arr_4(45);
  arr_3 = Odd_Even_Merge_Parallel(arr_1, 45);
  arr_4 = Odd_Even_Merge(arr_2, 45);
  ASSERT_EQ(arr_3, arr_4);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
