// Copyright 2022 Boyarskov Anton
#include <gtest/gtest.h>

#include "../../../3rdparty/unapproved/unapproved.h"
#include "./conjugate_gradient.h"

TEST(CONJUGATE_GRAD_STD, TEST_1) {
  int n = 2;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  std::vector<double> X = conjugateGradientSolver(A, B);

  vec check = matrixTimesVector(A, X);
}

TEST(CONJUGATE_GRAD_STD, TEST_2) {
  int n = 3;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  std::vector<double> X = conjugateGradientSolver(A, B);

  vec check = matrixTimesVector(A, X);
}

TEST(CONJUGATE_GRAD_STD, TEST_3) {
  int n = 10;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  std::vector<double> X = conjugateGradientSolver(A, B);
  vec check = matrixTimesVector(A, X);

  printError(B, check, n);
}

TEST(CONJUGATE_GRAD_STD, TEST_4) {
  int n = 20;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  std::vector<double> X = conjugateGradientSolver(A, B);
  vec check = matrixTimesVector(A, X);

  printError(B, check, n);
}

TEST(CONJUGATE_GRAD_STD, TEST_5) {
  int n = 10;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  auto seq_1 = clock();
  conjugateGradientSolver(A, B);
  auto seq_2 = clock();

  auto par_1 = clock();
  conjugateGradientSolverParallel(A, B);
  auto par_2 = clock();

  auto t2 = static_cast<double>(seq_2 - seq_1) / CLOCKS_PER_SEC;
  auto t1 = static_cast<double>(par_2 - par_1) / CLOCKS_PER_SEC;
  auto eff = (static_cast<double>(seq_2 - seq_1) / CLOCKS_PER_SEC) /
             (static_cast<double>(par_2 - par_1) / CLOCKS_PER_SEC);

  std::cout << t1 << std::endl;
  std::cout << t2 << std::endl;
  std::cout << eff << std::endl;
}
