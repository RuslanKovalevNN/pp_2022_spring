// Copyright 2022 Lazarev Aleksey
#include <gtest/gtest.h>
#include <omp.h>

#include "./strassen.h"

TEST(STRASSEN_TBB, TEST_1) {
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

TEST(STRASSEN_TBB, TEST_2) {
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

TEST(STRASSEN_TBB, TEST_3) {
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

TEST(STRASSEN_TBB, TEST_4) {
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

TEST(STRASSEN_TBB, TEST_5) {
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

TEST(STRASSEN_TBB, TEST_6) {
  int n = 20;

  matrix A(n, vector(n, 0));
  matrix B(n, vector(n, 0));

  setToRandom(&A, n);
  setToRandom(&B, n);

  matrix C;

  double time1 = omp_get_wtime();
  C = multiply(&A, &B, n);
  double time2 = omp_get_wtime();
  double native = time2 - time1;
  std::cout << "native: " << native << std::endl;

  time1 = omp_get_wtime();
  C = strassenMultiply(&A, &B, n, false);
  time2 = omp_get_wtime();
  double seq_time = time2 - time1;
  std::cout << "strassen seq: " << seq_time << std::endl;

  time1 = omp_get_wtime();
  C = strassenMultiply(&A, &B, n);
  time2 = omp_get_wtime();
  double parallel_time = time2 - time1;
  std::cout << "strassen par: " << parallel_time << std::endl;

  std::cout << "times: " << seq_time / parallel_time << std::endl;
}
