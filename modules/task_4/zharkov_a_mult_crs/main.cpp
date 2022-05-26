// Copyright 2022 Zharkov Andrey
#include <gtest/gtest.h>

#include <vector>

#include "./zharkov_a_mult_crs.h"

TEST(Sparce_Matrix_Multiplication, Test_Matrix_Create) {
  CRS_Matrix matrix({
      {cpx(10, -0.2), cpx(20, 1), cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
      {cpx(0, 0), cpx(30, 6), cpx(0, 0), cpx(40, 3.7), cpx(0, 0), cpx(0, 0)},
      {cpx(0, 0), cpx(0, 0), cpx(50, 3), cpx(60, 8), cpx(70, 2.5), cpx(0, 0)},
      {cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(80, 3.9)},
  });
  CRS_Matrix resMatrix(
      std::vector<cpx>({cpx(10, -0.2), cpx(20, 1), cpx(30, 6), cpx(40, 3.7),
                        cpx(50, 3), cpx(60, 8), cpx(70, 2.5), cpx(80, 3.9)}),
      std::vector<size_t>({0, 1, 1, 3, 2, 3, 4, 5}),
      std::vector<size_t>({0, 2, 4, 7, 8}), 6, 4);
  EXPECT_EQ(matrix, resMatrix);
}

TEST(Sparce_Matrix_Multiplication, Test_Matrix_Transpose) {
  CRS_Matrix matrix({
      {cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(3, 9)},
      {cpx(10, 3), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
      {cpx(0, 0), cpx(21, 5), cpx(0, 0), cpx(0, 0)},
      {cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
  });
  CRS_Matrix trans = matrix.transpose();
  CRS_Matrix resMatrix(std::vector<cpx>({cpx(10, 3), cpx(21, 5), cpx(3, 9)}),
                       std::vector<size_t>({1, 2, 0}),
                       std::vector<size_t>({0, 1, 2, 2, 3}), 4, 4);
  EXPECT_EQ(trans, resMatrix);
}

TEST(Sparce_Matrix_Multiplication, Test_Matrix_Multiplication) {
  CRS_Matrix matrix1({
      {cpx(0, 9), cpx(0, 0), cpx(0, 0), cpx(3, 9)},
      {cpx(10, 3), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
      {cpx(0, 0), cpx(21, 5), cpx(0, 0), cpx(0, 0)},
      {cpx(0, 0), cpx(0, 0), cpx(33, 2), cpx(0, 0)},
  });
  CRS_Matrix matrix2({
      {cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(0, 4)},
      {cpx(4, 5), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
      {cpx(8, 1), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
      {cpx(0, 0), cpx(0, 0), cpx(12, 9), cpx(0, 0)},
  });
  CRS_Matrix trans = matrix2.transpose();
  CRS_Matrix multRes = matrix1 * trans;
  CRS_Matrix resMatrix({
      {cpx(0, 0), cpx(0, 0), cpx(-45, 135), cpx(-36, 0)},
      {cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(-12, 40)},
      {cpx(59, 125), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
      {cpx(262, 49), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
  });
  EXPECT_EQ(multRes, resMatrix);
}

TEST(Sparce_Matrix_Multiplication, Test_Naive_and_CRS_Multiplication) {
  std::vector<std::vector<cpx>> mat1({
      {cpx(0, 0), cpx(3, 4), cpx(0, 0), cpx(7, 2)},
      {cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
      {cpx(0, 0), cpx(4, 5), cpx(0, 0), cpx(0, 0)},
  });
  std::vector<std::vector<cpx>> mat2({
      {cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(0, 0)},
      {cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(4, 3), cpx(0, 0)},
      {cpx(5, 9), cpx(0, 0), cpx(0, 0), cpx(0, 0), cpx(3, 1)},
      {cpx(0, 0), cpx(0, 0), cpx(8, 1), cpx(0, 0), cpx(0, 0)},
  });
  CRS_Matrix multCRS = CRS_Matrix(mat1) * CRS_Matrix(mat2).transpose();
  CRS_Matrix multNaive(naiveMultiplication(mat1, mat2));
  EXPECT_EQ(multCRS, multNaive);
}

TEST(Sparce_Matrix_Multiplication, Test_Big_Matrix) {
  CRS_Matrix rand1 = getRandomCRSMatrix(100, 100, 0.1);
  CRS_Matrix rand2 = getRandomCRSMatrix(100, 100, 0.1);
  CRS_Matrix trans = rand2.transpose();

  clock_t Start = clock();
  CRS_Matrix multCRSPar = rand1.parallelMultiply(trans);
  clock_t End = clock();
  double parallTime = static_cast<double>(End - Start) / CLOCKS_PER_SEC;
  std::cout << "Parall = " << parallTime << std::endl;

  Start = clock();
  CRS_Matrix multCRSSeq = rand1 * trans;
  End = clock();
  double seqTime = static_cast<double>(End - Start) / CLOCKS_PER_SEC;
  std::cout << "Seq = " << seqTime << std::endl;
  std::cout << "Boost = " << seqTime / parallTime << std::endl;
}
