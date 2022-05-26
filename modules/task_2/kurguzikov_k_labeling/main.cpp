// Copyright 2022 Kurguzikov Kirill
#include <gtest/gtest.h>
#include <omp.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "./labeling.h"

TEST(Labeling_OpenMP, Test_150x140) {
    int rows = 150;
    int cols = 140;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 9000);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    double  t1 = omp_get_wtime();
    res = ParLabeling(arr, rows, cols);
    double  t2 = omp_get_wtime();
    double time_par = t2 - t1;
    std::cout << "parallel time is " << time_par << std::endl;
    n_size_par = check_for_par(res, rows, cols);

    double t3 = omp_get_wtime();
    expected = SeqLabeling(arr, rows, cols);
    double t4 = omp_get_wtime();
    double time_seq = t4 - t3;
    std::cout << "sequential time is " << time_seq << std::endl;
    n_size_seq = check_for_seq(expected, rows, cols);

    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}

TEST(Labeling_OpenMP, Test_160x160) {
    int rows = 160;
    int cols = 160;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 11000);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    double  t1 = omp_get_wtime();
    res = ParLabeling(arr, rows, cols);
    double  t2 = omp_get_wtime();
    double time_par = t2 - t1;
    std::cout << "parallel time is " << time_par << std::endl;
    n_size_par = check_for_par(res, rows, cols);

    double t3 = omp_get_wtime();
    expected = SeqLabeling(arr, rows, cols);
    double t4 = omp_get_wtime();
    double time_seq = t4 - t3;
    std::cout << "sequential time is " << time_seq << std::endl;
    n_size_seq = check_for_seq(expected, rows, cols);

    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}

TEST(Labeling_OpenMP, Test_200x70) {
    int rows = 200;
    int cols = 70;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 5000);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    double  t1 = omp_get_wtime();
    res = ParLabeling(arr, rows, cols);
    double  t2 = omp_get_wtime();
    double time_par = t2 - t1;
    std::cout << "parallel time is " << time_par << std::endl;
    n_size_par = check_for_par(res, rows, cols);

    double t3 = omp_get_wtime();
    expected = SeqLabeling(arr, rows, cols);
    double t4 = omp_get_wtime();
    double time_seq = t4 - t3;
    std::cout << "sequential time is " << time_seq << std::endl;
    n_size_seq = check_for_seq(expected, rows, cols);

    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}

TEST(Labeling_OpenMP, Test_300x300) {
    int rows = 300;
    int cols = 300;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 45000);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    double  t1 = omp_get_wtime();
    res = ParLabeling(arr, rows, cols);
    double  t2 = omp_get_wtime();
    double time_par = t2 - t1;
    std::cout << "parallel time is " << time_par << std::endl;
    n_size_par = check_for_par(res, rows, cols);

    double t3 = omp_get_wtime();
    expected = SeqLabeling(arr, rows, cols);
    double t4 = omp_get_wtime();
    double time_seq = t4 - t3;
    std::cout << "sequential time is " << time_seq << std::endl;
    n_size_seq = check_for_seq(expected, rows, cols);

    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}

TEST(Labeling_OpenMP, Test_55x85) {
    int rows = 55;
    int cols = 85;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 2200);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    double  t1 = omp_get_wtime();
    res = ParLabeling(arr, rows, cols);
    double  t2 = omp_get_wtime();
    double time_par = t2 - t1;
    std::cout << "parallel time is " << time_par << std::endl;
    n_size_par = check_for_par(res, rows, cols);

    double t3 = omp_get_wtime();
    expected = SeqLabeling(arr, rows, cols);
    double t4 = omp_get_wtime();
    double time_seq = t4 - t3;
    std::cout << "sequential time is " << time_seq << std::endl;
    n_size_seq = check_for_seq(expected, rows, cols);

    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
