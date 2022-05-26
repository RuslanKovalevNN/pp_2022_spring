// Copyright 2022 Zaitsev Alexander
#include <gtest/gtest.h>

#include <vector>

#include "./matrix.h"

TEST(Test, test_1) {
  size_t size = 4;
  std::vector<std::vector<double>> matrix1(size, std::vector<double>(size));
  std::vector<std::vector<double>> matrix2(size, std::vector<double>(size));
  std::vector<std::vector<double>> answer(size, std::vector<double>(size, 0.0));
  size_t block_size = size / 4;
  size_t block_count = size / block_size;
  double num1 = 1.076, num2 = 2.067;
  // double start, end, time, time2;
  matrix1 = get_Matrix(num1, size);
  matrix2 = get_Matrix(num2, size);
  std::vector<std::vector<double>> matrix1_copy2 = matrix1;
  /*start = omp_get_wtime();*/
  std::vector<std::vector<double>> matrix3 =
      cannon_mult_alg_Seq(matrix1, matrix2, block_size, block_count, size);
  /*end = omp_get_wtime();
  time = end - start;
  std::cout << "Time= " << time << std::endl;
  start = omp_get_wtime();*/
  std::vector<std::vector<double>> matrix4 = cannon_mult_alg_TBB(
      matrix1_copy2, matrix2, block_size, block_count, size);
  /*end = omp_get_wtime();
  time2 = end - start;
  std::cout << "Time= " << time2 << std::endl;
  std::cout << std::endl;
  std::cout << time / time2 << std::endl;*/
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_DOUBLE_EQ(matrix3[i][j], matrix4[i][j]);
    }
  }
}

TEST(Test, test_2) {
  size_t size = 8;
  std::vector<std::vector<double>> matrix1(size, std::vector<double>(size));
  std::vector<std::vector<double>> matrix2(size, std::vector<double>(size));
  std::vector<std::vector<double>> answer(size, std::vector<double>(size, 0.0));
  size_t block_size = size / 4;
  size_t block_count = size / block_size;
  double num1 = 1.076, num2 = 2.067;
  matrix1 = get_Matrix(num1, size);
  matrix2 = get_Matrix(num2, size);
  std::vector<std::vector<double>> matrix1_copy2 = matrix1;
  std::vector<std::vector<double>> matrix3 =
      cannon_mult_alg_Seq(matrix1, matrix2, block_size, block_count, size);
  std::vector<std::vector<double>> matrix4 = cannon_mult_alg_TBB(
      matrix1_copy2, matrix2, block_size, block_count, size);
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_DOUBLE_EQ(matrix3[i][j], matrix4[i][j]);
    }
  }
}

TEST(Test, test_3) {
  size_t size = 12;
  std::vector<std::vector<double>> matrix1(size, std::vector<double>(size));
  std::vector<std::vector<double>> matrix2(size, std::vector<double>(size));
  std::vector<std::vector<double>> answer(size, std::vector<double>(size, 0.0));
  size_t block_size = size / 4;
  size_t block_count = size / block_size;
  double num1 = 1.076, num2 = 2.067;
  matrix1 = get_Matrix(num1, size);
  matrix2 = get_Matrix(num2, size);
  std::vector<std::vector<double>> matrix1_copy2 = matrix1;
  std::vector<std::vector<double>> matrix3 =
      cannon_mult_alg_Seq(matrix1, matrix2, block_size, block_count, size);
  std::vector<std::vector<double>> matrix4 = cannon_mult_alg_TBB(
      matrix1_copy2, matrix2, block_size, block_count, size);
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_DOUBLE_EQ(matrix3[i][j], matrix4[i][j]);
    }
  }
}

TEST(Test, test_4) {
  size_t size = 14;
  std::vector<std::vector<double>> matrix1(size, std::vector<double>(size));
  std::vector<std::vector<double>> matrix2(size, std::vector<double>(size));
  std::vector<std::vector<double>> answer(size, std::vector<double>(size, 0.0));
  size_t block_size = size / 4;
  size_t block_count = size / block_size;
  double num1 = 1.076, num2 = 2.067;
  matrix1 = get_Matrix(num1, size);
  matrix2 = get_Matrix(num2, size);
  std::vector<std::vector<double>> matrix1_copy2 = matrix1;
  std::vector<std::vector<double>> matrix3 =
      cannon_mult_alg_Seq(matrix1, matrix2, block_size, block_count, size);
  std::vector<std::vector<double>> matrix4 = cannon_mult_alg_TBB(
      matrix1_copy2, matrix2, block_size, block_count, size);
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_DOUBLE_EQ(matrix3[i][j], matrix4[i][j]);
    }
  }
}

TEST(Test, test_5) {
  size_t size = 16;
  std::vector<std::vector<double>> matrix1(size, std::vector<double>(size));
  std::vector<std::vector<double>> matrix2(size, std::vector<double>(size));
  std::vector<std::vector<double>> answer(size, std::vector<double>(size, 0.0));
  size_t block_size = size / 4;
  size_t block_count = size / block_size;
  double num1 = 1.076, num2 = 2.067;
  matrix1 = get_Matrix(num1, size);
  matrix2 = get_Matrix(num2, size);
  std::vector<std::vector<double>> matrix1_copy2 = matrix1;
  std::vector<std::vector<double>> matrix3 =
      cannon_mult_alg_Seq(matrix1, matrix2, block_size, block_count, size);
  std::vector<std::vector<double>> matrix4 = cannon_mult_alg_TBB(
      matrix1_copy2, matrix2, block_size, block_count, size);
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_DOUBLE_EQ(matrix3[i][j], matrix4[i][j]);
    }
  }
}
