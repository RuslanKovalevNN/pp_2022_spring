// Copyright 2022 Podovinnikov Artyom
#include <gtest/gtest.h>

#include <complex>
#include <vector>

#include "./sparsematrix.h"

TEST(matrix_CSR_complex, int_constructor) {
  SparseMatrix a(1);
  ASSERT_EQ(static_cast<int>(a.getSize()), 1);
  ASSERT_EQ(static_cast<int>(a.getValues().size()), 0);
  ASSERT_EQ(static_cast<int>(a.getCols().size()), 0);
  ASSERT_EQ(static_cast<int>(a.getPointers().size()), 0);
}

TEST(matrix_CSR_complex, copy_constructor) {
  SparseMatrix a(1);
  SparseMatrix b(a);
  ASSERT_EQ(b.getSize(), a.getSize());
  ASSERT_EQ(b.getValues(), a.getValues());
  ASSERT_EQ(b.getCols(), a.getCols());
  ASSERT_EQ(b.getPointers(), a.getPointers());
}

TEST(matrix_CSR_complex, operator_equal) {
  SparseMatrix a(1);
  SparseMatrix b(25);
  b = a;
  ASSERT_EQ(b.getSize(), a.getSize());
  ASSERT_EQ(b.getValues(), a.getValues());
  ASSERT_EQ(b.getCols(), a.getCols());
  ASSERT_EQ(b.getPointers(), a.getPointers());
}

TEST(matrix_CSR_complex, matrix_constructor_and__createDenseMatrix) {
  int size = 5;
  std::vector<std::complex<double>> a = {
      {1, 0}, {-1, 0}, {0, 0}, {-3, 0}, {0, 0}, {-2, 0}, {5, 0},
      {0, 0}, {0, 0},  {0, 0}, {0, 0},  {0, 0}, {4, 0},  {6, 0},
      {4, 0}, {-4, 0}, {0, 0}, {2, 0},  {7, 0}, {0, 0},  {0, 0},
      {8, 0}, {0, 0},  {0, 0}, {-5, 0}};
  SparseMatrix b(a, size);
  ASSERT_EQ(b.getSize(), size);
  ASSERT_EQ(a, b.getDenseMatrix());
}

TEST(matrix_CSR_complex, transposition_and_getDenseMatrix) {
  int size = 4;
  std::vector<std::complex<double>> a = {
      {0, 0}, {3, 0}, {0, 0}, {7, 0}, {0, 0}, {0, 0}, {8, 0},  {0, 0},
      {0, 0}, {0, 0}, {0, 0}, {0, 0}, {9, 0}, {0, 0}, {15, 0}, {16, 0}};
  SparseMatrix b(a, size);
  ASSERT_EQ(b.getSize(), size);
  ASSERT_EQ(a, b.transposition().transposition().getDenseMatrix());
}

TEST(matrix_CSR_complex, square_matrix_multiplication) {
  // int size = 4;
  int size = 2;
  std::vector<std::complex<double>> a = {// {0, 0}, {3, 0}, {0, 0},  {7, 0},
                                         // {0, 0}, {0, 0}, {8, 0},  {0, 0},
                                         // {0, 0}, {0, 0}, {0, 0},  {0, 0},
                                         // {9, 0}, {0, 0}, {15, 0}, {16, 0}
                                         {1, -3},
                                         {2, 0},
                                         {3, 0},
                                         {4, 0}};
  std::vector<std::complex<double>> b = {{4, 0}, {3, 0}, {2, -2}, {-1, -7}};
  std::vector<std::complex<double>> ans = {
      // {63, 0},  {0, 0},  {129, 0}, {112, 0},
      // {0, 0},   {0, 0},  {0, 0},   {0, 0},
      // {0, 0},   {0, 0},  {0, 0},   {0, 0},
      // {144, 0}, {27, 0}, {240, 0}, {319, 0}
      {8, -16},
      {1, -23},
      {20, -8},
      {5, -28}};
  // SparseMatrix b(a, size);
  SparseMatrix bm(b, size);
  SparseMatrix am(a, size);
  // ASSERT_NO_THROW(am.operator*(bm));
  // ASSERT_NO_THROW(b.operator*(b));
  // SparseMatrix c = b * b;
  // SparseMatrix c = am * bm;
  // ASSERT_EQ(c.getSize(), size);
  // ASSERT_EQ(c.getDenseMatrix(), ans);
  // ASSERT_EQ(b.operator*(b).getDenseMatrix(), ans);
  ASSERT_EQ(am.operator*(bm).getDenseMatrix(), ans);
}

TEST(matrix_CSR_complex, exception_matrix_multiplication) {
  int sizeA = 1;
  std::vector<std::complex<double>> a = {{0, 0}};
  int sizeB = 2;
  std::vector<std::complex<double>> b = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  SparseMatrix matrA(a, sizeA);
  SparseMatrix matrB(b, sizeB);
  ASSERT_THROW(matrA * matrB, std::string);
}

TEST(matrix_CSR_complex, matrix_multiplication_only0) {
  int sizeA = 2;
  std::vector<std::complex<double>> a = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  int sizeB = 2;
  std::vector<std::complex<double>> b = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  std::vector<std::complex<double>> ans = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  SparseMatrix matrA(a, sizeA);
  SparseMatrix matrB(b, sizeB);
  SparseMatrix res = matrA * matrB;
  ASSERT_EQ(res.getDenseMatrix(), ans);
}
