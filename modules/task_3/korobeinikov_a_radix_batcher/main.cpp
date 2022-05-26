// Copyright 2022 Korobeinikov Alexandr

#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <time.h>
#include <vector>
#include "../korobeinikov_a_radix_batcher/batcher_tbb.h"

TEST(Radix_Parallel_tbb, TestParallelSort_1) {
    int n = 100000;
    double* arr = new double[n];
    getRandomArray(arr, n);
    TbbParallelSort(arr, n, 8);
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Radix_Parallel_tbb, TestParallelSort_2) {
    int n = 100000;
    double* arr = new double[n];
    getRandomArray(arr, n);
    TbbParallelSort(arr, n, 5);
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Radix_Parallel_tbb, TestParallelSort_3) {
    int n = 23485;
    double* arr = new double[n];
    getRandomArray(arr, n);
    TbbParallelSort(arr, n, 5);
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Radix_Parallel_tbb, TestParallelSort_4) {
    int n = 123498;
    double* arr = new double[n];
    getRandomArray(arr, n);
    TbbParallelSort(arr, n, 4);
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

// TEST(Radix_Parallel_tbb, TestParallelSort_5) {
//     int n = 100000000;
//     double* arr1 = new double[n];
//     double* arr2 = new double[n];
//     getRandomArray(arr1, n);
//     getRandomArray(arr2, n);
//     tbb::tick_count start = tbb::tick_count::now();
//     RadixSort(arr1, 0, n-1);
//     tbb::tick_count finish = tbb::tick_count::now();
//     std::cout << "Seq time:" << (finish - start).seconds() << "\n";
//     start = tbb::tick_count::now();
//     TbbParallelSort(arr2, n, 6);
//     finish = tbb::tick_count::now();
//     std::cout << "Parallel time:" << (finish - start).seconds() << "\n";
//     ASSERT_EQ(1, checkCorrectnessOfSort(arr1, n));
//     ASSERT_EQ(1, checkCorrectnessOfSort(arr2, n));
// }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
