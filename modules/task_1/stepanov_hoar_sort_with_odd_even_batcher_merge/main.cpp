// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../../modules/task_1/stepanov_hoar_sort_with_odd_even_batcher_merge/hoar_sort_with_odd_even_batcher_merge.h"
TEST(Sequential, Test_5) {
    const int col = 5;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    std::sort(cp.begin(), cp.end());
    hoar_sort_with_batch_merge(arr);
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}

TEST(Sequential, Test_10) {
    const int col = 10;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    std::sort(cp.begin(), cp.end());
    hoar_sort_with_batch_merge(arr);
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}

TEST(Sequential, Test_20) {
    const int col = 20;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    std::sort(cp.begin(), cp.end());
    hoar_sort_with_batch_merge(arr);
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}

TEST(Sequential, Test_50) {
    const int col = 50;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    std::sort(cp.begin(), cp.end());
    hoar_sort_with_batch_merge(arr);
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}

TEST(Sequential, Test_100) {
    const int col = 100;
    std::vector<float>* arr = create_random_vector(col);
    std::vector<float> cp(*arr);
    std::sort(cp.begin(), cp.end());
    hoar_sort_with_batch_merge(arr);
    ASSERT_TRUE((*arr) == cp);
    delete arr;
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
