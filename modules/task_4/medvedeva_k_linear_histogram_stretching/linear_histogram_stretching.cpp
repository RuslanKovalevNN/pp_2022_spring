// Copyright 2022 Medvedeva Karina
#include "../../../modules/task_4/medvedeva_k_linear_histogram_stretching/linear_histogram_stretching.h"
#include <random>
#include "../../../3rdparty/unapproved/unapproved.h"

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

void thread_function(const std::vector<int>& matrix, int* local_max_y, int* local_min_y, int part_begin, int part_end) {
    for (int i = 0; i < part_end - part_begin; i++) {
        if (matrix[i] > *local_max_y) {
            *local_max_y = matrix[i];
        }
        if (matrix[i] < *local_min_y) {
            *local_min_y = matrix[i];
        }
    }
}

std::vector<int> getParallelOperations(const std::vector<int>& matrix,
    std::vector<int>::size_type row_count,
    std::vector<int>::size_type column_count,
    std::size_t thread_count) {
    std::vector<int> res(matrix);
    int max_y = 0;
    int min_y = 255;

    std::vector<int> local_max_y(thread_count, 0);
    std::vector<int> local_min_y(thread_count, 255);

    std::vector<std::thread> threads(thread_count);

    int part_begin = 0;
    int part_end = 0;

    for (std::size_t i = 0; i < thread_count; i++) {
        part_begin = part_end;
        part_end = (((row_count * column_count) / thread_count) * (i + 1) +
            (i == thread_count - 1 ? (row_count * column_count) % thread_count : 0));

        threads[i] = std::thread(thread_function, std::vector<int>(matrix.begin() + part_begin,
            matrix.begin() + part_end),
            &local_max_y[i], &local_min_y[i], part_begin, part_end);
    }

    for (size_t i = 0; i < thread_count; i++) {
        threads[i].join();
        if (max_y < local_max_y[i]) {
            max_y = local_max_y[i];
        }
        if (min_y > local_min_y[i]) {
            min_y = local_min_y[i];
        }
    }
    for (std::size_t i = 0; i < row_count * column_count; i++) {
        res[i] = (matrix[i] - min_y) * (255 / (max_y - min_y));
    }
    return res;
}
