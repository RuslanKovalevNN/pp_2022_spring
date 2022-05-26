//  Copyright 2022 Purtova Ksenia
#include <gtest/gtest.h>
#include<iostream>
#include "./shell_sort.h"

TEST(test_Shell_Batch_sort_seq, test_on_10_elements) {
  std::vector<int> res = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  std::vector<int> betch = ShellWithBatcher(res, 10);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Batch_sort_seq, test_on_10_random_elements) {
  std::vector<int> res = VectorRandomizer(10);
  std::vector<int> betch = ShellWithBatcher(res, 10);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Batch_sort_seq, test_on_100_random_elements) {
  std::vector<int> res = VectorRandomizer(100);
  std::vector<int> betch = ShellWithBatcher(res, 100);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Batch_sort_seq, test_on_1000_random_elements) {
  std::vector<int> res = VectorRandomizer(1000);
  std::vector<int> betch = ShellWithBatcher(res, 1000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Batch_sort_seq, test_on_5000_random_elements) {
  std::vector<int> res = VectorRandomizer(5000);
  std::vector<int> betch = ShellWithBatcher(res, 5000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
