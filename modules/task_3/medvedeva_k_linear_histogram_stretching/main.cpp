// Copyright 2022 Medvedeva Karina
#include <gtest/gtest.h>
#include "./linear_histogram_stretching.h"

TEST(Generation_Matrix, can_generate_square_matrix) {
    ASSERT_NO_THROW(getRandomMatrix(15, 15));
}

TEST(Generation_Matrix, can_generate_arbitrary_matrix) {
    ASSERT_NO_THROW(getRandomMatrix(11, 15));
}

TEST(Parallel_Operations, getParallelOperations_can_work_with_square_matrix) {
    std::vector<int> matrix = getRandomMatrix(15, 15);

    ASSERT_NO_THROW(getParallelOperations(matrix, 15, 15));
}

TEST(Parallel_Operations, getParallelOperations_can_work_with_arbitrary_matrix) {
    std::vector<int> matrix = getRandomMatrix(10, 15);

    ASSERT_NO_THROW(getParallelOperations(matrix, 10, 15));
}

TEST(Parallel_Operations, getParallelOperations_can_work_with_big_matrix) {
    std::vector<int> matrix = getRandomMatrix(30, 30);

    ASSERT_NO_THROW(getParallelOperations(matrix, 30, 30));
}

TEST(Parallel_Operations, getParallelOperations_works_correctly_with_square_matrix) {
    std::vector<int> matrix = {1, 3, 2, 5, 15, 7, 1, 0, 9};
    std::vector<int> res = {17, 51, 34, 85, 255, 119, 17, 0, 153};

    ASSERT_EQ(res, getParallelOperations(matrix, 3, 3));
}

TEST(Parallel_Operations, getParallelOperations_works_correctly_with_arbitrary_matrix) {
    std::vector<int> matrix = {2, 17, 10, 4, 7, 3};
    std::vector<int> res = { 0, 255, 136, 34, 85, 17};

    ASSERT_EQ(res, getParallelOperations(matrix, 2, 3));
}

TEST(DISABLED_Parallel_Operations, acceleration_test) {
    std::vector<int>::size_type matrix_size = 10000;
    std::vector<int> matrix(matrix_size * matrix_size);
    matrix = getRandomMatrix(matrix_size, matrix_size);

    auto start_getSequentialOperations = tbb::tick_count::now();
    std::vector<int> expected_res = getSequentialOperations(matrix, matrix_size, matrix_size);
    auto finish_getSequentialOperations = tbb::tick_count::now();

    auto start_getParallelOperations = tbb::tick_count::now();
    std::vector<int> res = getParallelOperations(matrix, matrix_size, matrix_size);
    auto finish_getParallelOperations = tbb::tick_count::now();

    auto getSequentialOperations_running_time =
        (finish_getSequentialOperations - start_getSequentialOperations).seconds();
    auto getParallelOperations_running_time =
        (finish_getParallelOperations - start_getParallelOperations).seconds();
    auto acceleration = getSequentialOperations_running_time / getParallelOperations_running_time;

    printf("Running time of sequential algorithm=%lf\nRunning time of parallel algorithm=%lf\n",
        getSequentialOperations_running_time, getParallelOperations_running_time);
    printf("Acceleration=%lf\n", acceleration);

    ASSERT_EQ(res, expected_res);
}
