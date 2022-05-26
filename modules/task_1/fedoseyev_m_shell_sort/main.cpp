// Copyright 2022 Fedoseyev Mikhail
#include <gtest/gtest.h>

#include "./shell_sort.h"

TEST(SHELL_SORT_SEQ, TEST_1) {
  int size = 10;
  int* a = generate_vector(size);
  print_list(a, size);
  shell_sort(a, size);
  print_list(a, size);
  ASSERT_EQ(check_list(a, size), 0);
  delete[] a;
}

TEST(SHELL_SORT_SEQ, TEST_2) {
  int size = 20;
  int* a = generate_vector(size);
  shell_sort(a, size);
  ASSERT_EQ(check_list(a, size), 0);
  delete[] a;
}

TEST(SHELL_SORT_SEQ, TEST_3) {
  int size = 30;
  int* a = generate_vector(size);
  shell_sort(a, size);
  ASSERT_EQ(check_list(a, size), 0);
  delete[] a;
}

TEST(SHELL_SORT_SEQ, TEST_4) {
  int size = 40;
  int* a = generate_vector(size);
  shell_sort(a, size);
  ASSERT_EQ(check_list(a, size), 0);
  delete[] a;
}

TEST(SHELL_SORT_SEQ, TEST_5) {
  int size = 50;
  int* a = generate_vector(size);
  shell_sort(a, size);
  ASSERT_EQ(check_list(a, size), 0);
  delete[] a;
}
