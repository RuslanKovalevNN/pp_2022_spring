// Copyright 2022 Abuyassen Albara

#ifndef MODULES_TASK_2_ABUYASSEN_A_CSR_OMP_CSR_OMP_H_
#define MODULES_TASK_2_ABUYASSEN_A_CSR_OMP_CSR_OMP_H_

#include <vector>
#include <complex>

struct CSR {
  std::vector<std::complex<int>> values;
  std::vector < int > row_ptr;
  std::vector < int > cols_index;
  int rows;
  int cols;
  int NNZ;

    friend const std::vector < std::complex < int >>
    operator*(const CSR &A, const CSR &B);
    friend const bool operator==(const CSR &A, const CSR &B);
};

CSR sparesify(const std::vector < std::complex < int >>  &M,
 int height, int width);
CSR sparse_transpose(const CSR &input);
std::vector < std::complex < int >> omp_multiply(const CSR & A,
  const CSR & B);
std::vector < std::complex < int >>  randomSparseMatrix(int N, int M);

#endif   // MODULES_TASK_2_ABUYASSEN_A_CSR_OMP_CSR_OMP_H_
