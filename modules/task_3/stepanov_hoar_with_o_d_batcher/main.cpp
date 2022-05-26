// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../../modules/task_3/stepanov_hoar_with_o_d_batcher/stepanov_hoar_sort_with_odd_even_batcher_merge.h"
TEST(Sequential, Test_20) {
    const int col = 20;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    hoar_sort_with_batch_merge(&cp);
    hoar_sort_with_batch_merge_tbb(arr);
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}

TEST(Sequential, Test_30) {
    const int col = 30;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    hoar_sort_with_batch_merge(&cp);
    hoar_sort_with_batch_merge_tbb(arr);
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}

TEST(Sequential, Test_40) {
    const int col = 40;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    hoar_sort_with_batch_merge(&cp);
    hoar_sort_with_batch_merge_tbb(arr);
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}

TEST(Sequential, Test_50) {
    const int col = 150;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    // tbb::tick_count start_seq = tbb::tick_count::now();
    hoar_sort_with_batch_merge(&cp);
    // tbb::tick_count end_seq = tbb::tick_count::now();
    // double sequential_runtime = (end_seq - start_seq).seconds();
    // tbb::tick_count start_tbb = tbb::tick_count::now();
    hoar_sort_with_batch_merge_tbb(arr);
    // tbb::tick_count end_tbb = tbb::tick_count::now();
    // double parallel_tbb_runtime = (end_tbb - start_tbb).seconds();
    // std::cout << "sequential_runtime = " << sequential_runtime << std::endl;
    // std::cout << "parallel_tbb_runtime = " << parallel_tbb_runtime
    //    << std::endl;
    // std::cout << "a: " << sequential_runtime / parallel_tbb_runtime;
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}

TEST(Sequential, Test_100) {
    const int col = 200;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    // tbb::tick_count start_seq = tbb::tick_count::now();
    hoar_sort_with_batch_merge(&cp);
    // tbb::tick_count end_seq = tbb::tick_count::now();
    // double sequential_runtime = (end_seq - start_seq).seconds();
    // tbb::tick_count start_tbb = tbb::tick_count::now();
    hoar_sort_with_batch_merge_tbb(arr);
    // tbb::tick_count end_tbb = tbb::tick_count::now();
    // double parallel_tbb_runtime = (end_tbb - start_tbb).seconds();
    // std::cout << "sequential_runtime = " << sequential_runtime << std::endl;
    // std::cout << "parallel_tbb_runtime = " << parallel_tbb_runtime
    //    << std::endl;
    // std::cout << "a: " << sequential_runtime / parallel_tbb_runtime;
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
