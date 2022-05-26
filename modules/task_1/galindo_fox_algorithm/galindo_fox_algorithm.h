// Copyright 2022 Javier Galindo

#ifndef MODULES_TASK_1_GALINDO_FOX_ALGORITHM_GALINDO_FOX_ALGORITHM_H_
#define MODULES_TASK_1_GALINDO_FOX_ALGORITHM_GALINDO_FOX_ALGORITHM_H_
#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <cmath>
#include <limits>
#define pNum 4

typedef std::vector<double> Matrix;

bool isEqual(double x, double y);
bool isEqualMatrix(Matrix A, Matrix B);

Matrix createRandomMatrix(size_t size);
Matrix sequentialMatrixMultiplication(std::vector<double> A,
    std::vector<double> B, size_t BlockSize);
Matrix sequentialBlockMatrixMultiplication(std::vector<double> A,
    std::vector<double> B, size_t Size);


#endif  // MODULES_TASK_1_GALINDO_FOX_ALGORITHM_GALINDO_FOX_ALGORITHM_H_
