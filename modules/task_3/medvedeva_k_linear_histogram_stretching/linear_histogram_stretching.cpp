// Copyright 2022 Medvedeva Karina
#include "../../../modules/task_3/medvedeva_k_linear_histogram_stretching/linear_histogram_stretching.h"
#include <random>

std::vector<int> getRandomMatrix(std::vector<int>::size_type row_count, std::vector<int>::size_type column_count) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(row_count * column_count);
    for (std::vector<int>::size_type i = 0; i < row_count; i++) {
        for (std::vector<int>::size_type j = 0; j < column_count; j++) {
            vec[i * column_count + j] = gen() % 100;
        }
    }
    return vec;
}

std::vector<int> getSequentialOperations(const std::vector<int>& matrix,
    std::vector<int>::size_type row_count,
    std::vector<int>::size_type column_count) {
    std::vector<int> res(matrix);
    int max_y = 0;
    int min_y = 255;
    for (std::size_t i = 0; i < column_count * row_count; i++) {
        if (matrix[i] > max_y) {
            max_y = matrix[i];
        }
        if (matrix[i] < min_y) {
            min_y = matrix[i];
        }
    }
    for (std::size_t i = 0; i < column_count * row_count; i++) {
        res[i] = (matrix[i] - min_y) * (255 / (max_y - min_y));
    }
    return res;
}

std::vector<int> getParallelOperations(const std::vector<int>& matrix,
    std::vector<int>::size_type row_count,
    std::vector<int>::size_type column_count,
    int thread_count) {
    std::vector<int> res(matrix);
    tbb::task_scheduler_init init(thread_count);
    std::vector<int> local_max_y(thread_count, 0);
    std::vector<int> local_min_y(thread_count, 255);
    int max_y = 0;
    int min_y = 255;

    tbb::parallel_for(tbb::blocked_range<std::size_t>(0, column_count * row_count),
        [&](const tbb::blocked_range<std::size_t>& r) {
            for (std::size_t i = r.begin(); i < r.end(); i++) {
                if (matrix[i] > local_max_y[tbb::task_arena::current_thread_index()]) {
                    local_max_y[tbb::task_arena::current_thread_index()] = matrix[i];
                }
                if (matrix[i] < local_min_y[tbb::task_arena::current_thread_index()]) {
                    local_min_y[tbb::task_arena::current_thread_index()] = matrix[i];
                }
            }
        });

    for (auto i = 0; i < thread_count; i++) {
        if (local_max_y[i] > max_y)
            max_y = local_max_y[i];
        if (local_min_y[i] < min_y)
            min_y = local_min_y[i];
    }

    tbb::parallel_for(tbb::blocked_range<std::size_t>(0, column_count * row_count),
        [&](const tbb::blocked_range<std::size_t>& r) {
            for (std::size_t i = r.begin(); i < r.end(); i++) {
                res[i] = (matrix[i] - min_y) * (255 / (max_y - min_y));
            }
        });

    return res;
}

