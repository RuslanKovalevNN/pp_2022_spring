// Copyright 2022 Abuyassen Albara

#include "CSR_omp.h"

#include <omp.h>

#include <vector>

#include <random>

#include <complex>

CSR sparesify(const std::vector < std::complex < int >> & M,
  int height, int width) {
  CSR new_csr;
  new_csr.rows = height;
  new_csr.cols = width;
  new_csr.row_ptr.push_back(0);
  new_csr.NNZ = 0;
  for (int i = 0; i < new_csr.rows; i++) {
    for (int j = 0; j < new_csr.cols; j++) {
      if (M[i * width + j] != 0) {
        new_csr.values.push_back(M[i * width + j]);
        new_csr.cols_index.push_back(j);
        new_csr.NNZ++;
      }
    }
    new_csr.row_ptr.push_back(new_csr.NNZ);
  }

  return new_csr;
}

CSR sparse_transpose(const CSR & input) {
  CSR res {
      std::vector < std::complex < int >> (input.NNZ, 0),
      std::vector < int > (input.cols + 2, 0),  // one extra
      std::vector < int > (input.NNZ, 0),
      input.cols,
      input.rows,
      input.NNZ
  };

  // count per column
  for (int i = 0; i < input.NNZ; ++i) {
    ++res.row_ptr[input.cols_index[i] + 2];
  }

  // from count per column generate new rowPtr (but shifted)
  for (size_t i = 2; i < res.row_ptr.size(); ++i) {
    // create incremental sum
    res.row_ptr[i] += res.row_ptr[i - 1];
  }

  // perform the main part
  for (int i = 0; i < input.rows; ++i) {
    for (int j = input.row_ptr[i]; j < input.row_ptr[i + 1]; ++j) {
      // calculate index to transposed matrix
      // at which we should place current element,
      // and at the same time build final rowPtr
      const int new_index = res.row_ptr[input.cols_index[j] + 1]++;
      res.values[new_index] = input.values[j];
      res.cols_index[new_index] = i;
    }
  }
  res.row_ptr.pop_back();  // pop that one extra

  return res;
}

const std::vector < std::complex < int >> operator * (const CSR & A,
  const CSR & B) {
  if (A.cols != B.rows)
    throw "Size Error";
  CSR B_t = sparse_transpose(B);
  std::vector < std::complex < int >> result(A.rows * B.cols, 0);
  for (int i = 0; i < A.rows; i++)
    for (int j = A.row_ptr[i]; j < A.row_ptr[i + 1]; j++) {
      int Ai = A.cols_index[j];
      std::complex < int > Avalue = A.values[j];
      for (int k = 0; k < B_t.rows; k++) {
        std::complex < int > sum(0, 0);
        for (int l = B_t.row_ptr[k]; l < B_t.row_ptr[k + 1]; l++)
          if (Ai == B_t.cols_index[l]) {
            sum += Avalue * B_t.values[l];
            break;
          }
        if (sum != std::complex < int > (0, 0)) {
          result[i * B_t.rows + k] += sum;
        }
      }
    }
  return result;
}

const bool operator == (const CSR & A,
  const CSR & B) {
  return A.values == B.values && A.cols_index == B.cols_index &&
  A.row_ptr == B.row_ptr && A.rows == B.rows
  && A.cols == B.cols && A.NNZ == B.NNZ;
}

std::vector < std::complex < int >> randomSparseMatrix(int N, int M) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector < std::complex < int >> result(N * M, 0);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (gen() % 100 == 0) {
        result[i * M + j] += std::complex < int > (gen() % 10, gen() % 10);
      }
    }
  }

  return result;
}

std::vector < std::complex < int >> omp_multiply(const CSR & A,
  const CSR & B) {
  if (A.cols != B.rows)
    throw "Size error";
  CSR B_t = sparse_transpose(B);
  std::vector < std::complex < int >> result(A.rows * B.cols, 0);
  #pragma omp parallel for
    for (int i = 0; i < A.rows; i++) {
      for (int j = A.row_ptr[i]; j < A.row_ptr[i + 1]; j++) {
        int Ai = A.cols_index[j];
        std::complex < int > Avalue = A.values[j];
        for (int k = 0; k < B_t.rows; k++) {
          std::complex < int > sum(0, 0);
          for (int l = B_t.row_ptr[k]; l < B_t.row_ptr[k + 1]; l++)
            if (Ai == B_t.cols_index[l]) {
              sum += Avalue * B_t.values[l];
              break;
            }
          if (sum != std::complex < int > (0, 0)) {
            result[i * B_t.rows + k] += sum;
          }
        }
      }
    }
  return result;
}
