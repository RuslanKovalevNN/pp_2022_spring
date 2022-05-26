// Copyright 2022 Kamenev Ilya
#include <gtest/gtest.h>
#include "./strassen_matrix_multiply_tbb.h"

TEST(Kamenev_Strassen_Par, MatrixSize8Test) {
  int size = 8;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_par_res(size * size);
  std::vector<double> naive_res(size * size);

  for (size_t i = 0; i < size * size; i++) {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  strassen_tbb(a.data(), b.data(), strassen_par_res.data(), size);
  naive_mult(a.data(), b.data(), naive_res.data(), size);
  ASSERT_EQ(naive_res, strassen_par_res);
}

TEST(Kamenev_Strassen_Par, MatrixSize128Test) {
  int size = 128;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_par_res(size * size);
  std::vector<double> naive_res(size * size);

  for (size_t i = 0; i < size * size; i++) {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  strassen_tbb(a.data(), b.data(), strassen_par_res.data(), size);
  naive_mult(a.data(), b.data(), naive_res.data(), size);
  ASSERT_EQ(naive_res, strassen_par_res);
}

TEST(Kamenev_Strassen_Par, MatrixSize256Test) {
  int size = 256;

  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_par_res(size * size);
  std::vector<double> naive_res(size * size);

  for (size_t i = 0; i < size * size; i++) {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  strassen_tbb(a.data(), b.data(), strassen_par_res.data(), size);
  naive_mult(a.data(), b.data(), naive_res.data(), size);

  ASSERT_EQ(naive_res, strassen_par_res);
}

TEST(Kamenev_Strassen_Par, MatrixSize1024Test) {
  int size = 1024;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_par_res(size * size);
  std::vector<double> naive_res(size * size);
  for (size_t i = 0; i < size * size; i++) {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  strassen_tbb(a.data(), b.data(), strassen_par_res.data(), size);
  naive_mult(a.data(), b.data(), naive_res.data(), size);

  ASSERT_EQ(naive_res, strassen_par_res);
}

TEST(Kamenev_Strassen_Par, InvalidSizeTest) {
  int size = 57;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> strassen_res(size * size);

  for (size_t i = 0; i < size * size; i++) {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  ASSERT_THROW(strassen_tbb(a.data(), b.data(), strassen_res.data(), size),
               std::invalid_argument);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
