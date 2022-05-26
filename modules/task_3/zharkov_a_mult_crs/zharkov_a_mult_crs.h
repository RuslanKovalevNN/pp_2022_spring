// Copyright 2022 Zharkov Andrey
#ifndef MODULES_TASK_3_ZHARKOV_A_MULT_CRS_ZHARKOV_A_MULT_CRS_H_
#define MODULES_TASK_3_ZHARKOV_A_MULT_CRS_ZHARKOV_A_MULT_CRS_H_

#include <complex>
#include <vector>

struct Matrix {
  int rows, cols;

  std::vector<std::complex<int>> val;

  Matrix(int _rows, int _cols) : rows(_rows), cols(_cols), val(cols * rows) { }
  ~Matrix() = default;
};

struct MatrixCRS {
  int rows, cols;
  std::vector<std::complex<int>> val;
  std::vector<int> cols_pos;
  std::vector<int> ptrs;
  MatrixCRS() = default;
  ~MatrixCRS() = default;
};

MatrixCRS generateRandomCRSMat(int rows, int cols);
Matrix generateRandomMat(int rows, int cols);

MatrixCRS convert(const Matrix &inMat);
MatrixCRS transp(const MatrixCRS &inMat);

MatrixCRS matrixCRSMult(const MatrixCRS &first, const MatrixCRS &second);
MatrixCRS matrixCRSMultTBB(const MatrixCRS &first, const MatrixCRS &second);
Matrix matrixMult(const Matrix &first, const Matrix &second);

void print(const MatrixCRS &in);

#endif  // MODULES_TASK_3_ZHARKOV_A_MULT_CRS_ZHARKOV_A_MULT_CRS_H_
