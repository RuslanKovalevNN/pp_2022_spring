// Copyright 2022 Lazarev Aleksey
#include <gtest/gtest.h>

#include <chrono>  // NOLINT

#include "./strassen.h"

TEST(STRASSEN_STD, TEST_1) {
  int n = 2;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(STRASSEN_STD, TEST_2) {
  int n = 4;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(STRASSEN_STD, TEST_3) {
  int n = 8;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(STRASSEN_STD, TEST_4) {
  int n = 16;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(STRASSEN_STD, TEST_5) {
  int n = 20;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C1, C2;

  C1 = multiply(&A, &B, n);
  C2 = strassenMultiply(&A, &B, n);

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(STRASSEN_STD, TEST_6) {
  int n = 20;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C;

  // Get starting timepoint
  auto time1 = std::chrono::high_resolution_clock::now();
  C = multiply(&A, &B, n);
  // Get ending timepoint
  auto time2 = std::chrono::high_resolution_clock::now();
  auto native =
      std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)
          .count();
  std::cout << "native: " << native << std::endl;

  time1 = std::chrono::high_resolution_clock::now();
  C = strassenMultiply(&A, &B, n, false);
  time2 = std::chrono::high_resolution_clock::now();
  auto seq_time =
      std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)
          .count();
  std::cout << "strassen seq: " << seq_time << std::endl;

  time1 = std::chrono::high_resolution_clock::now();
  C = strassenMultiply(&A, &B, n);
  time2 = std::chrono::high_resolution_clock::now();
  auto parallel_time =
      std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)
          .count();
  std::cout << "strassen par: " << parallel_time << std::endl;

  std::cout << "times: " << seq_time / static_cast<double>(parallel_time)
            << std::endl;
}
