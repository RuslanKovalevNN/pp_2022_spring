// Copyright 2022 LEBEDEV ANDREW
#ifndef MODULES_TASK_3_LEBEDEV_A_CANNON_MULT_MATRIX_MULT_H_
#define MODULES_TASK_3_LEBEDEV_A_CANNON_MULT_MATRIX_MULT_H_
#include <random>
#include <vector>
#include "tbb/tbb.h"

std::vector<std::vector<double> > get_random_matrix(size_t size, double val);

std::vector< std::vector<double> > matrix_mult(
    const std::vector< std::vector<double> > &matr_a,
    const std::vector< std::vector<double> > &matr_b, size_t size);

std::vector<std::vector<double> > cannon_mult_seq(
    const std::vector<std::vector<double> > &matr_a,
    const std::vector<std::vector<double> > &matr_b,
    size_t num_of_blocks, size_t block_size, size_t size);

std::vector<std::vector<double> > cannon_mult_tbb(
    const std::vector<std::vector<double> > &matr_a,
    const std::vector<std::vector<double> > &matr_b,
    size_t num_of_blocks, size_t block_size, size_t size);

#endif  // MODULES_TASK_3_LEBEDEV_A_CANNON_MULT_MATRIX_MULT_H_
