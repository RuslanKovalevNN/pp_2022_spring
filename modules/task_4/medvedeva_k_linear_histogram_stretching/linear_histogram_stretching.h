// Copyright 2022 Medvedeva Karina
#ifndef MODULES_TASK_4_MEDVEDEVA_K_LINEAR_HISTOGRAM_STRETCHING_LINEAR_HISTOGRAM_STRETCHING_H_
#define MODULES_TASK_4_MEDVEDEVA_K_LINEAR_HISTOGRAM_STRETCHING_LINEAR_HISTOGRAM_STRETCHING_H_

#include <vector>

std::vector<int> getRandomMatrix(std::vector<int>::size_type row_count,
    std::vector<int>::size_type column_count);
std::vector<int> getSequentialOperations(const std::vector<int>& matrix,
    std::vector<int>::size_type row_count,
    std::vector<int>::size_type column_count);
std::vector<int> getParallelOperations(const std::vector<int>& matrix,
    std::vector<int>::size_type row_count,
    std::vector<int>::size_type column_count, std::size_t thread_count = 12);

#endif  // MODULES_TASK_4_MEDVEDEVA_K_LINEAR_HISTOGRAM_STRETCHING_LINEAR_HISTOGRAM_STRETCHING_H_
