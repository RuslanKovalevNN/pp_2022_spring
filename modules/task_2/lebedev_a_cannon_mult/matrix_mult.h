// Copyright 2022 LEBEDEV ANDREW
#ifndef MODULES_TASK_2_LEBEDEV_A_CANNON_MULT_MATRIX_MULT_H_
#define MODULES_TASK_2_LEBEDEV_A_CANNON_MULT_MATRIX_MULT_H_
#include <random>
#include <vector>

std::vector<std::vector<double> > get_random_matrix(size_t size, double val);

std::vector< std::vector<double> > matrix_mult(
    const std::vector< std::vector<double> > &matr_a,
    const std::vector< std::vector<double> > &matr_b, size_t size);

std::vector<std::vector<double> > cannon_mult_seq(
    const std::vector<std::vector<double> > &matr_a,
    const std::vector<std::vector<double> > &matr_b,
    size_t num_of_blocks, size_t block_size, size_t size);

std::vector<std::vector<double> > cannon_mult_omp(
    const std::vector<std::vector<double> > &A,
    const std::vector<std::vector<double> > &B,
    size_t n, size_t bs, size_t s);

#endif  // MODULES_TASK_2_LEBEDEV_A_CANNON_MULT_MATRIX_MULT_H_
