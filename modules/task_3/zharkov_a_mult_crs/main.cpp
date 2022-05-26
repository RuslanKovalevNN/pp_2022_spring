// Copyright 2022 Zharkov Andrey
#include <gtest/gtest.h>

#include <ctime>
#include <iostream>
#include <vector>

#include "./zharkov_a_mult_crs.h"


TEST(CRS_Matrix_Mult, Random_Mat) {
  const int rows = 3;
  const int cols = 4;

  Matrix matrix = generateRandomMat(rows, cols);

  EXPECT_EQ(matrix.val.size(), static_cast<size_t>(rows * cols));
}

TEST(CRS_Matrix_Mult, Convert) {
  const int rows = 3;
  const int cols = 4;

  Matrix matrix = generateRandomMat(rows, cols);

  size_t count = 0;
  std::vector<std::complex<int>> c_val;
  for (size_t i = 0; i < matrix.val.size(); ++i)
    if (matrix.val[i] != 0) {
      ++count;
      c_val.emplace_back(matrix.val[i]);
    }

  MatrixCRS matrixCRS = convert(matrix);

  EXPECT_EQ(matrixCRS.val.size(), count);
  EXPECT_EQ(matrixCRS.val, c_val);
}

TEST(CRS_Matrix_Mult, B) {
  Matrix first(3, 3);
  Matrix second(3, 3);

  std::vector<std::complex<int>> first_val = {1, 0, 2, -1, 3, 0, 0, 0, 3};

  std::vector<std::complex<int>> second_val = {0, 2, 0, 4, 0, 0, 0, 0, 1};

  std::vector<std::complex<int>> res_val = {0, 2, 2, 12, -2, 0, 0, 0, 3};

  first.val = first_val;
  second.val = second_val;

  Matrix res = matrixMult(first, second);

  EXPECT_EQ(res.val, res_val);
}

TEST(CRS_Matrix_Mult, C) {
  std::vector<std::complex<int>> first_val = {1, 0, 2, -1, 3, 0, 0, 0, 3};
  Matrix fir(3, 3);
  fir.val = first_val;
  MatrixCRS first = convert(fir);
  //    first.rows = first.cols = 3;
  //    first.val = {1, 2, -1, 3, 3};
  //    first.cols_pos = {0, 2, 0, 1, 2};
  //    first.ptrs = {1, 3, 5, 6};

  std::vector<std::complex<int>> second_val = {0, 2, 0, 4, 0, 0, 0, 0, 1};
  Matrix sec(3, 3);
  sec.val = second_val;
  MatrixCRS second = convert(sec);

  Matrix re = matrixMult(fir, sec);
  MatrixCRS res = convert(re);

  //    res.cols = res.rows = 3;
  //    res.val = {2, 2, 12, -2, 3};
  //    res.cols_pos = {1, 2, 0, 1, 2};
  //    res.ptrs = {1, 3, 5, 6};

  MatrixCRS multRes = matrixCRSMult(first, second);

  EXPECT_EQ(res.val, multRes.val);
  EXPECT_EQ(res.cols_pos, multRes.cols_pos);
  EXPECT_EQ(res.ptrs, multRes.ptrs);
}

TEST(CRS_Matrix_Mult, D) {
  std::vector<std::complex<int>> first_val = {1, 0, 2, -1, 3, 0, 0, 0, 3};
  Matrix fir(3, 3);
  fir.val = first_val;
  MatrixCRS first = convert(fir);

  std::vector<std::complex<int>> second_val = {0, 2, 0, 4, 0, 0, 0, 0, 1};
  Matrix sec(3, 3);
  sec.val = second_val;
  MatrixCRS second = convert(sec);

  Matrix re = matrixMult(fir, sec);
  MatrixCRS res = convert(re);

  MatrixCRS multRes = matrixCRSMultTBB(first, second);

  EXPECT_EQ(res.val, multRes.val);
  EXPECT_EQ(res.cols_pos, multRes.cols_pos);
  EXPECT_EQ(res.ptrs, multRes.ptrs);
}

TEST(CRS_Matrix_Mult, mult_random_matrix) {
  Matrix f = generateRandomMat(150, 150);
  Matrix s = generateRandomMat(150, 150);

  MatrixCRS first = convert(f);
  MatrixCRS second = convert(s);

  clock_t Start = clock();
  MatrixCRS resSeq = matrixCRSMult(first, second);
  clock_t End = clock();
  double seqTime = static_cast<double>(End - Start) / CLOCKS_PER_SEC;

  Start = clock();
  MatrixCRS resParall = matrixCRSMultTBB(first, second);
  End = clock();
  double parallTime = static_cast<double>(End - Start) / CLOCKS_PER_SEC;

  std::cout << "seq = " << seqTime << std::endl;
  std::cout << "parall = " << parallTime << std::endl;
  std::cout << "boost = " << seqTime / parallTime << std::endl;

  EXPECT_EQ(resSeq.val, resParall.val);
  EXPECT_EQ(resSeq.cols_pos, resParall.cols_pos);
  EXPECT_EQ(resSeq.ptrs, resParall.ptrs);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
