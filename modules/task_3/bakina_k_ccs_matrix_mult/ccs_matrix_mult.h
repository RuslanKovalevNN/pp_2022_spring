// Copyright 2022 Bakina Kseniia

#ifndef MODULES_TASK_3_BAKINA_K_CCS_MATRIX_MULT_CCS_MATRIX_MULT_H_
#define MODULES_TASK_3_BAKINA_K_CCS_MATRIX_MULT_CCS_MATRIX_MULT_H_

#include <tbb/tbb.h>
#include <vector>

struct CCS_matrix {
    int row_n;
    int col_n;
    std::vector<double> value;
    std::vector<int> row;
    std::vector<int> column_pointer;

    bool operator==(const CCS_matrix& m);
};

std::vector<std::vector<double>> get_random_matrix(int n, int m);

CCS_matrix convert_to_ccs(const std::vector<std::vector<double>>& A);
CCS_matrix ccs_matrix_transposition(const CCS_matrix& B);
CCS_matrix ccs_matrix_multplication(const CCS_matrix& A, const CCS_matrix& B);
CCS_matrix ccs_matrix_transposition_tbb(const CCS_matrix& B);
CCS_matrix ccs_matrix_multplication_tbb(const CCS_matrix& A,
    const CCS_matrix& B);

#endif  // MODULES_TASK_3_BAKINA_K_CCS_MATRIX_MULT_CCS_MATRIX_MULT_H_
