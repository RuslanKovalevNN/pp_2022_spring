// Copyright 2022 Javier Galindo

#include "../../../modules/task_1/galindo_fox_algorithm/galindo_fox_algorithm.h"

bool is_equal(double x, double y) {
    return std::fabs(x - y) < 0.0001;
}

bool isEqualMatrix(Matrix A, Matrix B) {
    if ((A.size() <= 0) || (B.size() <= 0))
         throw "Size of matrix must be more than 0";
    if (A.size() != B.size())
        throw "Matrices are of different size";
    size_t size = A.size();
    for (size_t i = 0; i < size; i++)
         if (!is_equal(A[i], B[i]))
              return false;
    return true;
}

Matrix createRandomMatrix(size_t size) {
    if (size <= 0)
          throw "Size of matrix must be more than 0";
    Matrix result(size, 0);
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<> urd(-100000.0, 100000.0);
    for (size_t i = 0; i < size; i++) {
          result[i] = static_cast<double>(urd(mersenne));
    }
    return result;
}

Matrix sequentialMatrixMultiplication(std::vector<double> A,
    std::vector<double> B, size_t Size) {
    if (Size <= 0) {
    throw "Block size must be more than 0";
    }
    if ((A.size() <= 0) || (B.size() <= 0)) {
          throw "Size matrix must be more than 0";
    }
    if (A.size() != B.size()) {
        throw "Matrices are of different size";
    }
    if ((A.size() != Size) || (B.size() != Size)) {
        throw "Parameters and size are different";
    }
    size_t BlockSize = static_cast<size_t>(sqrt(Size));
    Matrix result(BlockSize * BlockSize, 0);
    for (size_t i = 0; i < BlockSize; i++)
        for (size_t j = 0; j < BlockSize; j++)
            for (size_t k = 0; k < BlockSize; k++)
               result[i * BlockSize + j] += A[i * BlockSize + k]
                   * B[k * BlockSize + j];
    return result;
}

Matrix sequentialBlockMatrixMultiplication(std::vector<double> A,
    std::vector<double> B, size_t Size) {
    if (Size <= 0) {
        throw "Block size must be more than 0";
    }
    if ((A.size() <= 0) || (B.size() <= 0)) {
        throw "Size matrix must be more than 0";
    }
    if (A.size() != B.size()) {
        throw "Matrices are of different size";
    }
    if ((A.size() != Size) || (B.size() != Size)) {
        throw "Parameters and size are different";
    }
    if (static_cast<size_t>(sqrt(Size)) *
        static_cast<size_t>(sqrt(Size)) != Size) {
        throw "Size is not square";
    }
    size_t BlockSize =
        static_cast<size_t>(sqrt(Size));
    size_t BlockCount =
        static_cast<size_t>(BlockSize/static_cast<size_t>(sqrt(pNum))) == 0
                          ? 1 : static_cast<size_t>
        (BlockSize/static_cast<size_t>(sqrt(pNum)));
    Matrix result(BlockSize * BlockSize, 0);
    for (size_t i = 0; i < BlockSize;
        i += BlockCount)
        for (size_t j = 0; j < BlockSize;
            j += BlockCount)
            for (size_t k = 0; k < BlockSize;
                k += BlockCount)
                for (size_t ii = i;
                    ii < ((BlockCount + i) % BlockSize + BlockCount); ii++)
                    for (size_t jj = j;
                        jj < ((BlockCount + j) % BlockSize + BlockCount); jj++)
for (size_t kk = k;
         kk < ((BlockCount + k) % BlockSize + BlockCount); kk++)
result[ii * BlockSize + jj] += A[ii * BlockSize + kk] * B[kk * BlockSize + jj];
    return result;
}
