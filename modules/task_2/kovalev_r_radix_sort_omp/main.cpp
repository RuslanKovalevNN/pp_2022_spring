// Copyright 2022 Kovalev Ruslan
#include <gtest/gtest.h>
#include <omp.h>
#include <time.h>

#include <vector>

#include "./radix_sort_omp.h"

TEST(Sequential_algorithm, radix_sort_1) {
  int len = 40;
  std::vector<int> vec_1(10000);
  std::vector<int> vec_2(10000);
  vec_gen(vec_1, 10000);
  vec_2 = vec_1;
  double start;
  double end;
  start = omp_get_wtime();
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 10000);
  end = omp_get_wtime();
  start = omp_get_wtime();
  vec_2 = Odd_Even_Merge(vec_2, 10000);
  end = omp_get_wtime();
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Sequential_algorithm, radix_sort_2) {
  int len = 40;
  std::vector<int> vec_1(40000);
  std::vector<int> vec_2(40000);
  vec_gen(vec_1, 40000);
  vec_2 = vec_1;
  double start;
  double end;
  start = omp_get_wtime();
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 40000);
  end = omp_get_wtime();
  start = omp_get_wtime();
  vec_2 = Odd_Even_Merge(vec_2, 40000);
  end = omp_get_wtime();
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Sequential_algorithm, radix_sort_3) {
  int len = 40;
  std::vector<int> vec_1(100);
  std::vector<int> vec_2(100);
  vec_gen(vec_1, 100);
  vec_2 = vec_1;
  double start;
  double end;
  start = omp_get_wtime();
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 100);
  end = omp_get_wtime();
  start = omp_get_wtime();
  vec_2 = Odd_Even_Merge(vec_2, 100);
  end = omp_get_wtime();
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Sequential_algorithm, radix_sort_4) {
  int len = 40;
  std::vector<int> vec_1(90);
  std::vector<int> vec_2(90);
  vec_gen(vec_1, 90);
  vec_2 = vec_1;
  double start;
  double end;
  start = omp_get_wtime();
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 90);
  end = omp_get_wtime();
  start = omp_get_wtime();
  vec_2 = Odd_Even_Merge(vec_2, 90);
  end = omp_get_wtime();
  ASSERT_EQ(vec_1, vec_2);
}

TEST(Sequential_algorithm, radix_sort_5) {
  int len = 40;
  std::vector<int> vec_1(30);
  std::vector<int> vec_2(30);
  vec_gen(vec_1, 30);
  vec_2 = vec_1;
  double start;
  double end;
  start = omp_get_wtime();
  vec_1 = Odd_Even_Merge_Parallel(vec_1, 30);
  end = omp_get_wtime();
  start = omp_get_wtime();
  vec_2 = Odd_Even_Merge(vec_2, 30);
  end = omp_get_wtime();
  ASSERT_EQ(vec_1, vec_2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
