// Copyright 2022 LEBEDEV ANDREW
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "./matrix_mult.h"

TEST(Cannon_test_tbb, size_4) {
    std::vector<std::vector<double> > A, B, C1, C2;
    size_t size = 4;
    size_t num_of_blocks = 2;
    size_t block_size = 2;
    A = get_random_matrix(size, 2.1);
    B = get_random_matrix(size, 3.6);
    C1 = matrix_mult(A, B, size);
    C2 = cannon_mult_tbb(A, B, num_of_blocks, block_size, size);
    for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                ASSERT_DOUBLE_EQ(C1[i][j], C2[i][j]);
                // std::cout << C1[i][j] << " " << C2[i][j] << std::endl;
            }
        }
}

TEST(Cannon_test_tbb, size_16) {
    std::vector<std::vector<double> > A, B, C1, C2;
    size_t size = 16;
    size_t num_of_blocks = 2;
    size_t block_size = 8;
    A = get_random_matrix(size, 4.1);
    B = get_random_matrix(size, 3.8);
    C1 = matrix_mult(A, B, size);
    C2 = cannon_mult_tbb(A, B, num_of_blocks, block_size, size);
    for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                ASSERT_DOUBLE_EQ(C1[i][j], C2[i][j]);
                // std::cout << C1[i][j] << " " << C2[i][j] << std::endl;
            }
        }
}

TEST(Cannon_test_tbb, size_20) {
    std::vector<std::vector<double> > A, B, C1, C2;
    size_t size = 20;
    size_t num_of_blocks = 2;
    size_t block_size = 10;
    A = get_random_matrix(size, 1.0);
    B = get_random_matrix(size, 6.0);
    C1 = matrix_mult(A, B, size);
    C2 = cannon_mult_tbb(A, B, num_of_blocks, block_size, size);
    for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                ASSERT_DOUBLE_EQ(C1[i][j], C2[i][j]);
                // std::cout << C1[i][j] << " " << C2[i][j] << std::endl;
            }
        }
}

TEST(Cannon_test_tbb, size_36) {
    std::vector<std::vector<double> > A, B, C1, C2;
    size_t size = 36;
    size_t num_of_blocks = 3;
    size_t block_size = 12;
    A = get_random_matrix(size, 2.0);
    B = get_random_matrix(size, 5.0);
    C1 = matrix_mult(A, B, size);
    C2 = cannon_mult_tbb(A, B, num_of_blocks, block_size, size);
    for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                ASSERT_DOUBLE_EQ(C1[i][j], C2[i][j]);
                // std::cout << C1[i][j] << " " << C2[i][j] << std::endl;
            }
        }
}

TEST(Cannon_test_tbb, size_32) {
    std::vector<std::vector<double> > A, B, C1, C2;
    size_t size = 32;
    size_t num_of_blocks = 2;
    size_t block_size = 16;
    A = get_random_matrix(size, 2.0);
    B = get_random_matrix(size, 3.0);
    C1 = matrix_mult(A, B, size);
    C2 = cannon_mult_tbb(A, B, num_of_blocks, block_size, size);
    for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                ASSERT_DOUBLE_EQ(C1[i][j], C2[i][j]);
                // std::cout << C1[i][j] << " " << C2[i][j] << std::endl;
            }
        }
}
