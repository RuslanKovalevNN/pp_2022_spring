// Copyright 2022 Bakina Kseniia

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

#include "../../../modules/task_3/bakina_k_ccs_matrix_mult/ccs_matrix_mult.h"

std::vector<std::vector<double>> get_random_matrix(int n, int m) {
    if (n < 0 || m < 0) {
        throw("Wrong matrix size for generation");
    }
    std::srand(time(0));
    std::vector<std::vector<double>> matrix(n, std::vector<double>(m, 0));
    int size = n * m /  100 * 15;
    for (int i = 0; i < size; i++) {
        matrix[std::rand() % n][std::rand() % m] =
            static_cast<double>(std::rand() % 10000);
    }
    return matrix;
}

bool CCS_matrix::operator==(const CCS_matrix& m) {
    return this->row_n == m.row_n && this->col_n == m.col_n
        && this->value == m.value && this->row == m.row
        && this->column_pointer == m.column_pointer;
}

CCS_matrix convert_to_ccs(const std::vector<std::vector<double>>& A) {
    if (A.empty()) {
        throw("Empty matrix for transposition");
    }
    CCS_matrix A_ccs;
    A_ccs.row_n = A.size();
    A_ccs.col_n = A[0].size();
    A_ccs.column_pointer.push_back(0);

    for (int i = 0; i < A_ccs.col_n; ++i) {
        for (int j = 0; j < A_ccs.row_n; ++j) {
            if (A[j][i] > 0) {
                A_ccs.value.push_back(A[j][i]);
                A_ccs.row.push_back(j);
            }
        }
        A_ccs.column_pointer.push_back(A_ccs.value.size());
    }
    return A_ccs;
}

CCS_matrix ccs_matrix_transposition(const CCS_matrix& B) {
    CCS_matrix BT;
    BT.col_n = B.row_n;
    BT.row_n = B.col_n;
    std::vector<std::vector<int>> for_row(B.row_n);
    std::vector<std::vector<double>> for_value(B.row_n);
    for (int j = 0; j < B.col_n; ++j) {
        for (int i = B.column_pointer[j]; i < B.column_pointer[j + 1]; ++i) {
            for_row[B.row[i]].push_back(j);
            for_value[B.row[i]].push_back(B.value[i]);
        }
    }
    BT.column_pointer.resize(BT.col_n + 1);
    BT.column_pointer[0] = 0;
    for (int i = 0; i < BT.col_n; ++i) {
        BT.column_pointer[i + 1] = BT.column_pointer[i] + for_value[i].size();
        int n = for_value[i].size();
        for (int j = 0; j < n; ++j) {
            BT.value.push_back(for_value[i][j]);
            BT.row.push_back(for_row[i][j]);
        }
    }
    return BT;
}

CCS_matrix ccs_matrix_transposition_tbb(const CCS_matrix& B) {
    CCS_matrix BT;
    BT.col_n = B.row_n;
    BT.row_n = B.col_n;
    std::vector<std::vector<int>> for_row(B.row_n);
    std::vector<std::vector<double>> for_value(B.row_n);
    for (int j = 0; j < B.col_n; ++j) {
        tbb::parallel_for(tbb::blocked_range<size_t>(B.column_pointer[j],
            B.column_pointer[j + 1]),
            [&](const tbb::blocked_range<size_t>& r) {
                int begin = r.begin(), end = r.end();
                for (int i = begin; i != end; ++i) {
                    for_row[B.row[i]].push_back(j);
                    for_value[B.row[i]].push_back(B.value[i]);
                }
            });
    }
    BT.column_pointer.resize(BT.col_n + 1);
    BT.column_pointer[0] = 0;
    BT.value.resize(B.value.size());
    BT.row.resize(B.value.size());
    for (int i = 0; i < BT.col_n; ++i) {
        BT.column_pointer[i + 1] = BT.column_pointer[i] + for_value[i].size();
        for (int j = BT.column_pointer[i]; j < BT.column_pointer[i + 1]; ++j) {
            BT.value[j] = for_value[i][j - BT.column_pointer[i]];
            BT.row[j] = for_row[i][j - BT.column_pointer[i]];
        }
    }
    return BT;
}

CCS_matrix ccs_matrix_multplication(const CCS_matrix& A, const CCS_matrix& B) {
    if (A.row_n != B.col_n) {
        throw("Wrong matrix sizes for multiplication");
    }

    CCS_matrix C;
    // Transpose the matrix B
    CCS_matrix BT(ccs_matrix_transposition(B));

    // Initialization of matrix C
    C.col_n = A.col_n;
    C.row_n = B.row_n;
    C.column_pointer.push_back(0);

    // Multiplication
    for (int i = 0; i < A.col_n; ++i) {
        std::vector<int> x(A.row_n, -1);
        for (int j = A.column_pointer[i]; j < A.column_pointer[i + 1]; ++j) {
            x[A.row[j]] = j;
        }
        for (int k = 0; k < BT.col_n; ++k) {
            double sum = 0;
            for (int j = BT.column_pointer[k];
                j < BT.column_pointer[k + 1]; ++j) {
                if (x[BT.row[j]] > -1) {
                    sum += A.value[x[BT.row[j]]] * BT.value[j];
                }
            }
            if (sum > 0) {
                C.value.push_back(sum);
                C.row.push_back(k);
            }
        }
        C.column_pointer.push_back(C.value.size());
    }
    return C;
}

CCS_matrix ccs_matrix_multplication_tbb(const CCS_matrix& A,
    const CCS_matrix& B) {
    if (A.row_n != B.col_n) {
        throw("Wrong matrix sizes for multiplication");
    }

    // Transpose the matrix B
    CCS_matrix BT(ccs_matrix_transposition_tbb(B));

    // Initialization of matrix C
    CCS_matrix C;
    C.col_n = A.col_n;
    C.row_n = B.row_n;
    C.column_pointer.reserve(A.col_n + 1);
    C.value.reserve(A.col_n * BT.col_n);
    C.row.reserve(A.col_n * BT.col_n);
    C.column_pointer.push_back(0);

    // Multiplication
    std::vector<std::vector<int>> x(A.col_n, std::vector<int>(A.row_n, -1));
    tbb::parallel_for(tbb::blocked_range<size_t>(0, A.col_n),
        [&](const tbb::blocked_range<size_t>& r) {
            int begin = r.begin(), end = r.end();
            for (int i = begin; i < end; ++i) {
                for (int j = A.column_pointer[i];
                    j < A.column_pointer[i + 1]; ++j) {
                    x[i][A.row[j]] = j;
                }
            }
        });
    for (int i = 0; i < A.col_n; ++i) {
        for (int k = 0; k < BT.col_n; ++k) {
            double sum = 0;
            for (int j = BT.column_pointer[k];
                j < BT.column_pointer[k + 1]; ++j) {
                if (x[i][BT.row[j]] > -1) {
                    sum += A.value[x[i][BT.row[j]]] * BT.value[j];
                }
            }
            if (std::fabs(sum) > 0) {
                C.value.push_back(sum);
                C.row.push_back(k);
            }
        }
        C.column_pointer.push_back(C.value.size());
    }
    return C;
}

