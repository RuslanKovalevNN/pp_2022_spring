// Copyright 2022 Vanyushkov Maxim
#include <gtest/gtest.h>
#include "./sort.h"

bool test(int size) {
    std::vector<int> vec_seq = getRandomVector(size);
    std::vector<int> vec_par = vec_seq;

    tbb::tick_count start_seq = tbb::tick_count::now();
    ShellSortSequantial(&vec_seq);
    tbb::tick_count end_seq = tbb::tick_count::now();

    tbb::tick_count start_par = tbb::tick_count::now();
    ShellSortParallel(&vec_par);
    tbb::tick_count end_par = tbb::tick_count::now();

    double seq_time = (end_seq - start_seq).seconds();
    double par_time = (end_par - start_par).seconds();
    std::cout << "Effective: " << seq_time / par_time << '\n';

    return vec_seq == vec_par && checkSort(vec_par);
}

TEST(ShellSort, test_size_101) {
    ASSERT_TRUE(test(101));
}

TEST(ShellSort, test_size_503) {
    ASSERT_TRUE(test(503));
}

TEST(ShellSort, test_size_1021) {
    ASSERT_TRUE(test(1021));
}

TEST(ShellSort, test_size_2322) {
    ASSERT_TRUE(test(2322));
}

TEST(ShellSort, test_size_12323) {
    ASSERT_TRUE(test(12323));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
