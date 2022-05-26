// Copyright 2022 Medvedeva Karina
#ifndef MODULES_TASK_3_MEDVEDEVA_K_LINEAR_HISTOGRAM_STRETCHING_LINEAR_HISTOGRAM_STRETCHING_H_
#define MODULES_TASK_3_MEDVEDEVA_K_LINEAR_HISTOGRAM_STRETCHING_LINEAR_HISTOGRAM_STRETCHING_H_

#include <tbb/tbb.h>
#include <vector>

std::vector<int> getRandomMatrix(std::vector<int>::size_type row_count,
    std::vector<int>::size_type column_count);
std::vector<int> getSequentialOperations(const std::vector<int>& matrix,
    std::vector<int>::size_type row_count,
    std::vector<int>::size_type column_count);
std::vector<int> getParallelOperations(const std::vector<int>& matrix,
    std::vector<int>::size_type row_count,
    std::vector<int>::size_type column_count,
    int thread_count = tbb::task_scheduler_init::default_num_threads());

#endif  // MODULES_TASK_3_MEDVEDEVA_K_LINEAR_HISTOGRAM_STRETCHING_LINEAR_HISTOGRAM_STRETCHING_H_
