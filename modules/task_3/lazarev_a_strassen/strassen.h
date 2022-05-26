// Copyright 2022 Lazarev Aleksey
#ifndef MODULES_TASK_3_LAZAREV_A_STRASSEN_STRASSEN_H_
#define MODULES_TASK_3_LAZAREV_A_STRASSEN_STRASSEN_H_

#include <tbb/tbb.h>

#include <string>
#include <vector>

const int threshold = 256;

using vector = std::vector<int>;
using matrix = std::vector<std::vector<int>>;

void setToRandom(matrix* A, int n);

matrix strassenMultiply(matrix* A, matrix* B, int n, bool parallel = true);
matrix multiply(matrix* A, matrix* B, int n);

#endif  // MODULES_TASK_3_LAZAREV_A_STRASSEN_STRASSEN_H_
