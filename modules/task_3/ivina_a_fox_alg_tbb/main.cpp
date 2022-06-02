// Copyright 2022 Ivina Anastasiya
#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "./Fox_alg_tbb.h"

TEST(MatrixMultTBB, RandNumCorrectSize) {
  const int size = 3;
  std::vector<std::vector<double>> MatrixA(size, std::vector<double>(size, 0));
  MatrixA = FillMatrixRandom(MatrixA);
  std::vector<std::vector<double>> MatrixB(size, std::vector<double>(size, 0));
  MatrixB = FillMatrixRandom(MatrixB);
  ASSERT_NO_THROW(Fox(MatrixA, MatrixB));
}

TEST(MatrixMultTBB, RandNumWrongSize) {
  const int row1 = 3;
  const int col1 = 5;
  std::vector<std::vector<double>> MatrixA(row1, std::vector<double>(col1, 0));
  FillMatrixRandom(MatrixA);
  const int row2 = 1;
  const int col2 = 4;
  std::vector<std::vector<double>> MatrixB(row2, std::vector<double>(col2, 0));
  FillMatrixRandom(MatrixB);

  ASSERT_ANY_THROW(Fox(MatrixA, MatrixB));
}

TEST(MatrixMultTBB, ConstNumFox) {
  std::vector<std::vector<double>> MatrixA{
      {1.2, 3.1, 2.7},
      {3.5, 2.5, 1.9},
      {2.1, 5, 5.1},
  };

  std::vector<std::vector<double>> MatrixB{
      {2.6, 5.1, 2.4},
      {1.7, 4.5, 3.2},
      {6.1, 3.5, 1.2},
  };

  std::vector<std::vector<double>> MatrixC{
      {24.86, 29.52, 16.04},
      {24.94, 35.75, 18.68},
      {45.07, 51.06, 27.16},
  };
  std::vector<std::vector<double>> MatrixD = Fox(MatrixA, MatrixB);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(MatrixC[i][j], MatrixD[i][j]);
    }
  }
}

TEST(MatrixMultTBB, RandNumCompare10x10) {
  const int n = 10;
  std::vector<std::vector<double>> MatrixA(n, std::vector<double>(n, 0));
  MatrixA = FillMatrixRandom(MatrixA);
  std::vector<std::vector<double>> MatrixB(n, std::vector<double>(n, 0));
  MatrixB = FillMatrixRandom(MatrixB);
  std::vector<std::vector<double>> MatrixC =
      DenseMatrixMultiplication(MatrixA, MatrixB);
  std::vector<std::vector<double>> MatrixD = Fox(MatrixA, MatrixB);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ASSERT_NEAR(MatrixC[i][j], MatrixD[i][j], 0.001F);
    }
  }
}

TEST(MatrixMultTBB, RandNumCompare100x100) {
  const int n = 100;
  std::vector<std::vector<double>> MatrixA(n, std::vector<double>(n, 0));
  MatrixA = FillMatrixRandom(MatrixA);
  std::vector<std::vector<double>> MatrixB(n, std::vector<double>(n, 0));
  MatrixB = FillMatrixRandom(MatrixB);
  std::vector<std::vector<double>> MatrixC =
      DenseMatrixMultiplication(MatrixA, MatrixB);
  std::vector<std::vector<double>> MatrixD = Fox(MatrixA, MatrixB);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ASSERT_NEAR(MatrixC[i][j], MatrixD[i][j], 0.001F);
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
