// Copyright 2022 LEBEDEV ANDREW

#include <omp.h>
#include <iostream>
#include "../../../modules/task_2/lebedev_a_cannon_mult/matrix_mult.h"

std::vector<std::vector<double> > get_random_matrix(size_t size, double val) {
    std::vector<std::vector<double> > res(size, std::vector<double>(size));
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            res[i][j] = i * j + val;
        }
    }
    return res;
}

std::vector< std::vector<double> > matrix_mult(
    const std::vector< std::vector<double> > &matr_a,
    const std::vector< std::vector<double> > &matr_b, size_t size) {
    std::vector< std::vector<double> > matr_c(size,
     std::vector<double>(size, 0.0));
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < size; k++) {
                matr_c[i][j] += matr_a[i][k] * matr_b[k][j];
            }
        }
    }
    return matr_c;
}

std::vector<std::vector<double> > cannon_mult_seq(
    const std::vector<std::vector<double> > &matr_a,
    const std::vector<std::vector<double> > &matr_b,
    size_t num_of_blocks, size_t block_size, size_t size) {
    std::vector< std::vector<double> > matr_c(size,
     std::vector<double>(size, 0.0));
    for (size_t q = 0; q < num_of_blocks * num_of_blocks; q++) {
        std::vector< std::vector<double> > C_ij(block_size,
            std::vector<double>(block_size, 0.0));
        size_t pos_i = q / num_of_blocks;
        size_t pos_j = q % num_of_blocks;
        std::pair<size_t, size_t> A_pos;
        A_pos.first = pos_i;
        A_pos.second = (pos_j + pos_i) % num_of_blocks;
        std::pair<size_t, size_t> B_pos;
        B_pos.first = (pos_j + pos_i) % num_of_blocks;
        B_pos.second = pos_j;
        for (size_t p = 0; p < num_of_blocks; p++) {
            for (size_t i = 0; i < block_size; i++) {
                for (size_t j = 0; j < block_size; j++) {
                    for (size_t k = 0; k < block_size; k++) {
                        size_t a_i = A_pos.first * block_size;
                        size_t a_j = A_pos.second * block_size;
                        size_t b_i = B_pos.first * block_size;
                        size_t b_j = B_pos.second * block_size;
                        C_ij[i][j] +=
                        matr_a[a_i + i][a_j + k] * matr_b[b_i + k][b_j + j];
                    }
                }
            }
            A_pos.second = (A_pos.second + 1) % num_of_blocks;
            B_pos.first = (B_pos.first + 1) % num_of_blocks;
        }
        for (size_t i = 0; i < block_size; i++) {
            for (size_t j = 0; j < block_size; j++) {
                matr_c[pos_i * block_size + i][pos_j * block_size + j] =
                C_ij[i][j];
            }
        }
    }
    return matr_c;
}

std::vector<std::vector<double> > cannon_mult_omp(
    const std::vector<std::vector<double> > &A,
    const std::vector<std::vector<double> > &B,
    size_t n, size_t bs, size_t s) {
    std::vector< std::vector<double> > C(s,
     std::vector<double>(s, 0.0));
    int thr = static_cast<int>(n * n);
    omp_set_num_threads(thr);
#pragma omp parallel firstprivate(bs, n, s, thr) shared(A, B, C)
    {
#pragma omp for schedule(static)
        for (int t = 0; t < thr; t++) {
            std::vector< std::vector<double> > C_ij(bs,
                std::vector<double>(bs, 0.0));
            size_t q = static_cast<size_t>(t);
            size_t pos_i = q / n;
            size_t pos_j = q % n;
            std::pair<size_t, size_t> A_pos;
            A_pos.first = pos_i;
            A_pos.second = (pos_j + pos_i) % n;
            std::pair<size_t, size_t> B_pos;
            B_pos.first = (pos_j + pos_i) % n;
            B_pos.second = pos_j;
            for (size_t p = 0; p < n; p++) {
                for (size_t i = 0; i < bs; i++) {
                    for (size_t j = 0; j < bs; j++) {
                        for (size_t k = 0; k < bs; k++) {
                            size_t a_i = A_pos.first * bs;
                            size_t a_j = A_pos.second * bs;
                            size_t b_i = B_pos.first * bs;
                            size_t b_j = B_pos.second * bs;
                            C_ij[i][j] +=
                            A[a_i + i][a_j + k] * B[b_i + k][b_j + j];
                        }
                    }
                }
                A_pos.second = (A_pos.second + 1) % n;
                B_pos.first = (B_pos.first + 1) % n;
            }
            for (size_t i = 0; i < bs; i++) {
                for (size_t j = 0; j < bs; j++) {
                    C[pos_i * bs + i][pos_j * bs + j] =
                    C_ij[i][j];
                }
            }
        }
    }
    return C;
}
