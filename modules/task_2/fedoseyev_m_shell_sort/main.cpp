// Copyright 2022 Fedoseyev Mikhail
#include <gtest/gtest.h>

#include "./shell_sort.h"

TEST(SHELL_SORT_OMP, TEST_1) {
  int size = 10;
  int* a = generate_vector(size);
  print_list(a, size);
  shell_sort(a, size);
  shell_sort(a, size, false);
  print_list(a, size);
  ASSERT_EQ(check_list(a, size), 0);
  delete[] a;
}

TEST(SHELL_SORT_OMP, TEST_2) {
  int size = 20;
  int* a = generate_vector(size);
  shell_sort(a, size);
  shell_sort(a, size, false);
  ASSERT_EQ(check_list(a, size), 0);
  delete[] a;
}

TEST(SHELL_SORT_OMP, TEST_3) {
  int size = 30;
  int* a = generate_vector(size);
  shell_sort(a, size);
  shell_sort(a, size, false);
  ASSERT_EQ(check_list(a, size), 0);
  delete[] a;
}

TEST(SHELL_SORT_OMP, TEST_4) {
  int size = 15;
  int* a = generate_vector(size);
  shell_sort(a, size);
  shell_sort(a, size, false);
  ASSERT_EQ(check_list(a, size), 0);
  delete[] a;
}

const int big_size = 10;

TEST(SHELL_SORT_OMP, SIZE_BIG) {
  int* a = generate_vector(big_size);
  int* b = new int[big_size];
  std::copy(a, a + big_size, b);

  double start = omp_get_wtime();
  shell_sort(a, big_size);
  double end = omp_get_wtime();
  double ptime = end - start;
  std::cout << "\tparallel time: " << ptime << "\n";

  start = omp_get_wtime();
  shell_sort(b, big_size, false);
  end = omp_get_wtime();
  double stime = end - start;
  std::cout << "\tsequential time: " << stime << "\n";

  std::cout << "\tefficiency: " << stime / ptime << "\n";

  ASSERT_EQ(check_list(a, big_size), 0);
  delete[] a;
  delete[] b;
}
