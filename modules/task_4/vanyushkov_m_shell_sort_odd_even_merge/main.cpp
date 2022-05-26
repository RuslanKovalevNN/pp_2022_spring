// Copyright 2022 Vanyushkov Maxim
#include <gtest/gtest.h>
#include "./sort.h"

bool test(int size) {
    std::vector<int> vec_seq = getRandomVector(size);
    std::vector<int> vec_par = vec_seq;

    auto start_seq = std::chrono::high_resolution_clock::now();
    ShellSortSequantial(&vec_seq);
    auto end_seq = std::chrono::high_resolution_clock::now();

    auto start_par = std::chrono::high_resolution_clock::now();
    ShellSortParallel(&vec_par);
    auto end_par = std::chrono::high_resolution_clock::now();

    auto seq_time = std::chrono::duration_cast
        <std::chrono::nanoseconds>(end_seq - start_seq);
    auto par_time = std::chrono::duration_cast
        <std::chrono::nanoseconds>(end_par - start_par);
    std::cout << "Effective: " << static_cast<double>(seq_time.count())
        / par_time.count() << '\n';

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
