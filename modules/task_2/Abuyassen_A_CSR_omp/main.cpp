// Copyright 2022 Abuyassen Albara

#include <gtest/gtest.h>
#include <omp.h>
#include <vector>
#include <complex>
#include "./CSR_omp.h"

TEST(CSR_seq, multiplication_100_100) {
    int width = 100, height = 100;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(height, width);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, height, width);
    double dtime;
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    dtime = omp_get_wtime() - dtime;
    printf("Sequential time : %f s\n", dtime);
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> PAR = omp_multiply(A_, B_);
    dtime = omp_get_wtime() - dtime;
    printf("Parallel time : %f s\n", dtime);
    dtime = omp_get_wtime();
    ASSERT_TRUE(SEQ == PAR);
}

TEST(CSR_seq, multiplication_250_300) {
    int width = 300, height = 250;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(width, height);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, width, height);
    double dtime;
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    dtime = omp_get_wtime() - dtime;
    printf("Sequential time : %f s\n", dtime);
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> PAR = omp_multiply(A_, B_);
    dtime = omp_get_wtime() - dtime;
    printf("Parallel time : %f s\n", dtime);
    dtime = omp_get_wtime();
    ASSERT_TRUE(SEQ == PAR);
}

TEST(CSR_seq, multiplication_1000_1000) {
    int width = 1000, height = 1000;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(width, height);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, width, height);
    double dtime;
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    dtime = omp_get_wtime() - dtime;
    printf("Sequential time : %f s\n", dtime);
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> PAR = omp_multiply(A_, B_);
    dtime = omp_get_wtime() - dtime;
    printf("Parallel time : %f s\n", dtime);
    dtime = omp_get_wtime();
    ASSERT_TRUE(SEQ == PAR);
}

TEST(CSR_seq, multiplication_250_160) {
    int width = 160, height = 250;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(width, height);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, width, height);
    double dtime;
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    dtime = omp_get_wtime() - dtime;
    printf("Sequential time : %f s\n", dtime);
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> PAR = omp_multiply(A_, B_);
    dtime = omp_get_wtime() - dtime;
    printf("Parallel time : %f s\n", dtime);
    dtime = omp_get_wtime();
    ASSERT_TRUE(SEQ == PAR);
}

TEST(CSR_seq, multiplication_20_10) {
    int width = 20, height = 10;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(width, height);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, width, height);
    double dtime;
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    dtime = omp_get_wtime() - dtime;
    printf("Sequential time : %f s\n", dtime);
    dtime = omp_get_wtime();
    std::vector<std::complex<int>> PAR = omp_multiply(A_, B_);
    dtime = omp_get_wtime() - dtime;
    printf("Parallel time : %f s\n", dtime);
    dtime = omp_get_wtime();
    ASSERT_TRUE(SEQ == PAR);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
