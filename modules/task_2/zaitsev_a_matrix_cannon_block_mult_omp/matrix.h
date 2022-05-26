// Copyright 2022 Zaitsev Alexander
#ifndef MODULES_TASK_2_ZAITSEV_A_MATRIX_CANNON_BLOCK_MULT_OMP_MATRIX_H_
#define MODULES_TASK_2_ZAITSEV_A_MATRIX_CANNON_BLOCK_MULT_OMP_MATRIX_H_

#include <omp.h>

#include <iostream>
#include <vector>

std::vector<std::vector<double>> get_Matrix(double number, size_t size);
void shift_to_Left(std::vector<std::vector<double>> *matrix, size_t position,
                   size_t count_of_block, size_t size_of_block);
void shift_to_Up(std::vector<std::vector<double>> *matrix, size_t position,
                 size_t count_of_block, size_t size_of_block);
void multiply_to_Block(std::vector<std::vector<double>> first_block,
                       std::vector<std::vector<double>> second_block,
                       std::vector<std::vector<double>> res_block,
                       size_t shift_l, size_t shift_r, size_t size_of_block);
std::vector<std::vector<double>> cannon_mult_alg_OMP(
    std::vector<std::vector<double>> first_multiplier,
    std::vector<std::vector<double>> second_multiplier, int thread_nums,
    size_t size_of_block, int count_of_block, size_t size);
std::vector<std::vector<double>> cannon_mult_alg_Seq(
    std::vector<std::vector<double>> first_multiplier,
    std::vector<std::vector<double>> second_multiplier, size_t size_of_block,
    size_t count_of_block, size_t size);

#endif  //  MODULES_TASK_2_ZAITSEV_A_MATRIX_CANNON_BLOCK_MULT_OMP_MATRIX_H_
