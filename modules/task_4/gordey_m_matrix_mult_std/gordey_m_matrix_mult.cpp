// Copyright 2018 Nesterov Alexander
#include "../../modules/task_4/gordey_m_matrix_mult_std/gordey_m_matrix_mult.h"
#include <omp.h>
double* create_random_matrix(int size_n) {
    std::random_device dev;
    std::mt19937 gen(dev());
    double* in = new double[size_n];
    for (int i = 0; i < size_n; ++i) {
        in[i] = static_cast<double>(gen()) / gen();
        if ((i % 3 == 0)) in[i] = 0;
    }
    return in;
}
SparseM operator *(const SparseM& A, const SparseM& B) {
    SparseM C(A);
    std::vector<int> row;
    std::vector<double>value;
    std::vector<int>col_idx(B.cols);
    transport(&C);
    int ci = 0;
    bool flag = true;
    for (int i = 0; i < B.cols; i++) {
        for (int j = 0; j < C.cols; j++) {
            double res = 0;
            int ls = B.col_idx[i];
            int lf = B.col_idx[i + 1] - 1;
            int ks = C.col_idx[j];
            int kf = C.col_idx[j + 1] - 1;
            while ((ks <= kf) && (ls <= lf)) {
                if (C.row[ks] == B.row[ls]) {
                    res += C.value[ks] * B.value[ls];
                    ks++;
                    ls++;
                } else {
                    if (C.row[ks] < B.row[ls]) {
                        ks++;
                    } else {
                        ls++;
                    }
                }
            }
            if (res != 0) {
                if (flag) {
                    col_idx[i] = (ci);
                    flag = false;
                }
                value.push_back(res);
                row.push_back(j);
                ci++;
            }
        }
        if (flag)  col_idx[i] = (ci);
        flag = true;
    }
    col_idx.push_back(ci);
    C.row = std::move(row);
    C.value = std::move(value);
    C.col_idx = std::move(col_idx);

    return C;
}
void mult_part(const int st, const int fn, const SparseM& B, const SparseM& C,
std::vector<int>* col_idx, std::vector<std::vector<int>>* row,
std::vector<std::vector<double>>* value, int thread_num) {
    for (int i = st; i < fn; i++) {
        for (int j = 0; j < C.cols; j++) {
            double res = 0;
            int ls = B.col_idx[i];
            int lf = B.col_idx[i + 1] - 1;
            int ks = C.col_idx[j];
            int kf = C.col_idx[j + 1] - 1;
            while ((ks <= kf) && (ls <= lf)) {
                if (C.row[ks] == B.row[ls]) {
                    res += C.value[ks] * B.value[ls];
                    ks++;
                    ls++;
                } else {
                    if (C.row[ks] < B.row[ls]) {
                        ks++;
                    } else {
                        ls++;
                    }
                }
            }
            if (res != 0) {
                (*col_idx)[i]++;
                (*value)[thread_num].push_back(res);
                (*row)[thread_num].push_back(j);
            }
        }
    }
}

void transport(SparseM* v) {
    std::vector<std::queue<int >> A(v->rows);
    std::vector<std::queue<double >> B(v->rows);
    std::vector<int>col_idx(v->cols);
    int k = 0;
    bool flag = true;
    for (int i = 0; i < v->cols; i++) {
        for (int j = v->col_idx[i]; j <= v->col_idx[i + 1] - 1; j++) {
            A[v->row[j]].push(i);
            B[v->row[j]].push(v->value[j]);
        }
    }

    v->value.resize(0);
    v->row.resize(0);
    for (int i = 0; i < v->rows; i++) {
        while (!B[i].empty()) {
            if (flag) {
                col_idx[i] = k;
                flag = false;
            }
            v->value.push_back(B[i].front());
            B[i].pop();
            v->row.push_back(A[i].front());
            A[i].pop();
            k++;
        }
        flag = true;
    }
    col_idx.push_back(k);
    v->col_idx = std::move(col_idx);
}

SparseM Mult_parallel(const SparseM& A, const SparseM& B) {
    SparseM C(A);
    std::vector<double>vals;
    std::vector<int> rows;
    std::vector<int>col_idx(B.cols, 0);

    const int nthreads = std::thread::hardware_concurrency();
    const int delta = (B.cols / nthreads) + 1;
    std::vector<std::thread> threads(nthreads);
    std::vector<std::vector<int>> row(nthreads);
    std::vector<std::vector<double >> value(nthreads);
    transport(&C);
    for (int thread = 0; thread < nthreads; thread++) {
        threads[thread] =
        std::thread(mult_part, thread*delta,
        std::min((thread + 1)*delta, B.cols),
        B, C, &col_idx, &row, &value, thread);
    }
    for (int i = 0; i < nthreads; i++) {
        threads[i].join();
        for (size_t j = 0; j < value[i].size(); j++) {
            vals.push_back(value[i][j]);
            rows.push_back(row[i][j]);
        }
    }
    int sum = 0;
    for (size_t i = 0; i < col_idx.size(); i++) {
        int tmp = col_idx[i];
        col_idx[i] = sum;
        sum = tmp + sum;
    }
    col_idx.emplace_back(sum);
    C.col_idx = std::move((col_idx));
    C.row = std::move(rows);
    C.value = std::move(vals);
    return C;
}
