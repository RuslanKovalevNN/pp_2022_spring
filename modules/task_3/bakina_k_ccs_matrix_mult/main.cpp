// Copyright 2022 Bakina Kseniia
#include <gtest/gtest.h>

#include "./ccs_matrix_mult.h"

TEST(Bakina_K_ccs_matrix_mult, check_matrix_transposition_small_size) {
    int n = 10, m = 15;
    std::vector<std::vector<double>> A = get_random_matrix(n, m);
    CCS_matrix A_ccs(convert_to_ccs(A));

    CCS_matrix AT_ccs(ccs_matrix_transposition(A_ccs));
    CCS_matrix AT_check(ccs_matrix_transposition_tbb(A_ccs));

    EXPECT_TRUE(AT_check == AT_ccs);
}

TEST(Bakina_K_ccs_matrix_mult, check_matrix_transposition_medium_size) {
    int n = 250, m = 300;
    std::vector<std::vector<double>> A = get_random_matrix(n, m);
    CCS_matrix A_ccs(convert_to_ccs(A));

    CCS_matrix AT_ccs(ccs_matrix_transposition(A_ccs));
    CCS_matrix AT_check(ccs_matrix_transposition_tbb(A_ccs));

    EXPECT_TRUE(AT_check == AT_ccs);
}

TEST(Bakina_K_ccs_matrix_mult, check_matrix_transposition_large_size) {
    int n = 200, m = 500;
    std::vector<std::vector<double>> A = get_random_matrix(n, m);
    CCS_matrix A_ccs(convert_to_ccs(A));

    CCS_matrix AT_ccs(ccs_matrix_transposition(A_ccs));
    CCS_matrix AT_check(ccs_matrix_transposition_tbb(A_ccs));

    EXPECT_TRUE(AT_check == AT_ccs);
}

TEST(Bakina_K_ccs_matrix_mult, check_matrix_multiplication_small_size) {
    int n = 10, m = 15, k = 20;
    std::vector<std::vector<double>> A = get_random_matrix(n, m);
    std::vector<std::vector<double>> B = get_random_matrix(k, n);
    CCS_matrix A_ccs(convert_to_ccs(A));
    CCS_matrix B_ccs(convert_to_ccs(B));

    tbb::tick_count t1_s = tbb::tick_count::now();
    CCS_matrix C_ccs(ccs_matrix_multplication(A_ccs, B_ccs));
    tbb::tick_count t2_s = tbb::tick_count::now();

    double time_s = (t2_s - t1_s).seconds();
    std::cout << "Sequential: " << time_s << "\n";

    tbb::tick_count t1 = tbb::tick_count::now();
    CCS_matrix C_check(ccs_matrix_multplication_tbb(A_ccs, B_ccs));
    tbb::tick_count t2 = tbb::tick_count::now();

    double time = (t2 - t1).seconds();
    std::cout << "TBB: " << time << "\n";
    std::cout << "Sequential/TBB " << time_s / time << "\n";

    EXPECT_TRUE(C_ccs == C_check);
}

TEST(Bakina_K_ccs_matrix_mult, check_matrix_multiplication_medium_size) {
    int n = 250, m = 100, k = 350;
    std::vector<std::vector<double>> A = get_random_matrix(n, m);
    std::vector<std::vector<double>> B = get_random_matrix(k, n);
    CCS_matrix A_ccs(convert_to_ccs(A));
    CCS_matrix B_ccs(convert_to_ccs(B));

    tbb::tick_count t1_s = tbb::tick_count::now();
    CCS_matrix C_ccs(ccs_matrix_multplication(A_ccs, B_ccs));
    tbb::tick_count t2_s = tbb::tick_count::now();

    double time_s = (t2_s - t1_s).seconds();
    std::cout << "Sequential: " << time_s << "\n";

    tbb::tick_count t1 = tbb::tick_count::now();
    CCS_matrix C_check(ccs_matrix_multplication_tbb(A_ccs, B_ccs));
    tbb::tick_count t2 = tbb::tick_count::now();

    double time = (t2 - t1).seconds();
    std::cout << "TBB: " << time << "\n";
    std::cout << "Sequential/TBB " << time_s / time << "\n";

    EXPECT_TRUE(C_ccs == C_check);
}

TEST(Bakina_K_ccs_matrix_mult, check_matrix_multiplication_large_size) {
    int n = 1200, m = 1500, k = 800;
    std::vector<std::vector<double>> A = get_random_matrix(n, m);
    std::vector<std::vector<double>> B = get_random_matrix(k, n);
    CCS_matrix A_ccs(convert_to_ccs(A));
    CCS_matrix B_ccs(convert_to_ccs(B));

    tbb::tick_count t1_s = tbb::tick_count::now();
    CCS_matrix C_ccs(ccs_matrix_multplication(A_ccs, B_ccs));
    tbb::tick_count t2_s = tbb::tick_count::now();

    double time_s = (t2_s - t1_s).seconds();
    std::cout << "Sequential: " << time_s << "\n";

    tbb::tick_count t1 = tbb::tick_count::now();
    CCS_matrix C_check(ccs_matrix_multplication_tbb(A_ccs, B_ccs));
    tbb::tick_count t2 = tbb::tick_count::now();

     double time = (t2 - t1).seconds();
     std::cout << "TBB: " << time << "\n";
     std::cout << "Sequential/TBB " << time_s / time << "\n";

    EXPECT_TRUE(C_ccs == C_check);
}

TEST(Bakina_K_ccs_matrix_mult, check_matrix_multiplication_large_size2) {
    int n = 1500, m = 2000, k = 1000;
    std::vector<std::vector<double>> A = get_random_matrix(n, m);
    std::vector<std::vector<double>> B = get_random_matrix(k, n);
    CCS_matrix A_ccs(convert_to_ccs(A));
    CCS_matrix B_ccs(convert_to_ccs(B));

    tbb::tick_count t1_s = tbb::tick_count::now();
    CCS_matrix C_ccs(ccs_matrix_multplication(A_ccs, B_ccs));
    tbb::tick_count t2_s = tbb::tick_count::now();

    double time_s = (t2_s - t1_s).seconds();
    std::cout << "Sequential: " << time_s << "\n";

    tbb::tick_count t1 = tbb::tick_count::now();
    CCS_matrix C_check(ccs_matrix_multplication_tbb(A_ccs, B_ccs));
    tbb::tick_count t2 = tbb::tick_count::now();

    double time = (t2 - t1).seconds();
    std::cout << "TBB: " << time << "\n";
    std::cout << "Sequential/TBB " << time_s / time << "\n";

    EXPECT_TRUE(C_ccs == C_check);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
