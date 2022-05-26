// Copyright 2022 Ivanov Arkady
#include <gtest/gtest.h>

#include "./rbms.h"


bool isStrictDescendingTest(size_t size, int degree) {
    std::vector<uint32_t> data(size);
    fillStrictDescending<uint32_t>(data.data(), size, size);
    std::vector<uint32_t> checkVector(data);

    radixBatchersMergesort_std<uint32_t>(&data, degree);
    radixSort<uint32_t>(&checkVector, 0, size);

    return isVecSame(data, checkVector);
}

template<class T>
bool isRndSortTestCorrect(size_t size, int degree, T from, T to) {
    std::vector<T> data(size);
    fillVecWithRandValues(data.data(), size, from, to);
    std::vector<T> checkVector(data);

    radixBatchersMergesort_std<T>(&data, degree);
    radixSort<T>(&checkVector, 0, size);

    return isVecSame(data, checkVector);
}

#if USE_EFFICIENCY_TESTS == 1
bool isEfficiencyTestCorrect(size_t size, const int degree) {
    std::vector<uint32_t> data(size);
    fillVecWithRandValues<uint32_t>(data.data(), size, 0, ~0);
    std::vector<uint32_t> checkVector(data);

    volatile double pt1 = omp_get_wtime();
    radixBatchersMergesort_std<uint32_t>(&data, degree);
    volatile double pt2 = omp_get_wtime();

    std::cout << "Parallel time: " << pt2 - pt1 << std::endl;

    volatile double st1 = omp_get_wtime();
    radixSort<uint32_t>(&checkVector, 0, size);
    volatile double st2 = omp_get_wtime();

    std::cout << "Sequential time: " << st2 - st1 << std::endl << std::flush;
    std::cout << "Ratio seq/par: " << (st2 - st1) / (pt2 - pt1) << std::endl;

    return isVecSame(data, checkVector);
}
#endif  // USE_EFFICIENCY_TESTS

// [12, 11, ..., 10, 1] -> [1, 2, ..., 11, 12] on 4 threads
TEST(rbms_check, can_sort_diff_sized_vect_1) {
    ASSERT_TRUE(isStrictDescendingTest(12, 2));
}

// [13, 12, ..., 10, 1] -> [1, 2, ..., 12, 13] on 4 threads
TEST(rbms_check, can_sort_diff_sized_vect_2) {
    ASSERT_TRUE(isStrictDescendingTest(13, 2));
}

// [14, 13, ..., 10, 1] -> [1, 2, ..., 13, 14] on 4 threads
TEST(rbms_check, can_sort_diff_sized_vect_3) {
    ASSERT_TRUE(isStrictDescendingTest(14, 2));
}

// [15, 14, ..., 10, 1] -> [1, 2, ..., 13, 14] on 4 threads
TEST(rbms_check, can_sort_diff_sized_vect_4) {
    ASSERT_TRUE(isStrictDescendingTest(14, 2));
}

// rand vector with rand size on 2 threads
TEST(rbms_check, rnd_vecSize_rnd_vec_2_thr) {
    uint32_t size = getRandValue<uint32_t>(100, 500);
    ASSERT_TRUE(isRndSortTestCorrect<uint32_t>(size, 1, 0, ~0));
}

// rand vector with rand size on 4 threads
TEST(rbms_check, rnd_vecSize_rnd_vec_4_thr) {
    uint32_t size = getRandValue<uint32_t>(100, 500);
    ASSERT_TRUE(isRndSortTestCorrect<uint32_t>(size, 2, 0, ~0));
}

// rand vector with rand size on 8 threads
TEST(rbms_check, rnd_vecSize_rnd_vec_8_thr) {
    uint32_t size = getRandValue<uint32_t>(100, 500);
    ASSERT_TRUE(isRndSortTestCorrect<uint32_t>(size, 3, 0, ~0));
}

// rand vector with rand size on 4 threads. SHORT INT
TEST(rbms_check, rnd_vecSize_rnd_vec_4_thr_short_int) {
    uint16_t size = getRandValue<uint16_t>(100, 500);
    ASSERT_TRUE(isRndSortTestCorrect<uint16_t>(size, 2, 0, ~0));
}

#if USE_EFFICIENCY_TESTS == 1

// 1 000 000 elements on 4 threads
TEST(rbms_efficiency_check, test_1mil_4thrd) {
    ASSERT_TRUE(isEfficiencyTestCorrect(1000000, 2));
}

// 2 000 000 elements on 8 threads
TEST(rbms_efficiency_check, test_2mil_8thrd) {
    ASSERT_TRUE(isEfficiencyTestCorrect(2000000, 3));
}

// 100 000 000 elements on 8 threads
TEST(rbms_efficiency_check, test_100mil_8thrd) {
    ASSERT_TRUE(isEfficiencyTestCorrect(100000000, 3));
}

// 100 000 000 elements on 16 threads
TEST(rbms_efficiency_check, test_100mil_16thrd) {
    ASSERT_TRUE(isEfficiencyTestCorrect(100000000, 4));
}
#endif  // USE_EFFICIENCY_TESTS


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
