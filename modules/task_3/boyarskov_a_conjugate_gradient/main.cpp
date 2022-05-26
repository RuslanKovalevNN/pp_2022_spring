// Copyright 2022 Boyarskov Anton
#include <gtest/gtest.h>
#include <omp.h>

#include "./conjugate_gradient.h"

TEST(CONJUGATE_GRAD_TBB, TEST_1) {
  int n = 2;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  // print("A", A);
  // print("B", B);

  std::vector<double> X = conjugateGradientSolver(A, B);

  // print("X", X);
  vec check = matrixTimesVector(A, X);
  // print("Check AX:", check);

  // printError(B, check, n);
}

TEST(CONJUGATE_GRAD_TBB, TEST_2) {
  int n = 3;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  // print("A", A);
  // print("B", B);

  std::vector<double> X = conjugateGradientSolver(A, B);

  // print("X", X);
  vec check = matrixTimesVector(A, X);
  // print("Check AX:", check);

  // printError(B, check, n);
}

TEST(CONJUGATE_GRAD_TBB, TEST_3) {
  int n = 10;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  std::vector<double> X = conjugateGradientSolver(A, B);
  vec check = matrixTimesVector(A, X);

  // printError(B, check, n);
}

TEST(CONJUGATE_GRAD_TBB, TEST_4) {
  int n = 20;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  std::vector<double> X = conjugateGradientSolver(A, B);
  vec check = matrixTimesVector(A, X);

  // printError(B, check, n);
}

TEST(CONJUGATE_GRAD_TBB, TEST_5_TIME) {
  int n = 10;

  matrix A;
  vec B;

  B = generateRandomVector(n);
  A = generateMatrix(generateRandomVector(n));

  double time1 = omp_get_wtime();
  conjugateGradientSolver(A, B);
  double time2 = omp_get_wtime();
  double s_time = time2 - time1;

  time1 = omp_get_wtime();
  conjugateGradientSolverParallel(A, B);
  time2 = omp_get_wtime();
  double p_time = time2 - time1;

  std::cout << "Sequential " << s_time << std::endl;
  std::cout << "Parallel " << p_time << std::endl;
  std::cout << s_time / p_time << std::endl;
}
