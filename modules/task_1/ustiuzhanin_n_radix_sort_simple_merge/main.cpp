// Copyright 2022 Ustiuzhanin Nikita
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "./radix_sort.h"

using std::vector;
using std::cout;

TEST(SEQ_RADIX_SORT, TEST_SMALL_DATA) {
    vector<int> data;
    size_t size = 10;
    size_t countRad = 3;

    randomVector(&data, size, countRad);
    radixSort(&data);

    for (size_t i = 0; i < size - 1; i++)
        ASSERT_LE(data[i], data[i + 1]);
}

TEST(SEQ_RADIX_SORT, TEST_BIG_DATA) {
    vector<int> data;
    size_t size = 10000;
    size_t countRad = 6;

    randomVector(&data, size, countRad);
    radixSort(&data);

    for (size_t i = 0; i < size - 1; i++)
        ASSERT_LE(data[i], data[i + 1]);
}

TEST(SEQ_RADIX_SORT, TEST_DIFFERRENT_RAD) {
    vector<int> data;
    size_t size = 10;
    size_t countRad = 4;

    randomVector(&data, size, countRad);
    data.push_back(1);
    data.push_back(20);
    size += 2;
    radixSort(&data);

    for (size_t i = 0; i < size - 1; i++)
        ASSERT_LE(data[i], data[i + 1]);
}

TEST(SEQ_RADIX_SORT, TEST_EMPTY) {
    vector<int> data;
    size_t size = 0;
    size_t countRad = 4;

    randomVector(&data, size, countRad);
    ASSERT_NO_THROW(radixSort(&data));
}

TEST(SEQ_RADIX_SORT, TEST_WRONG_DATA) {
    vector<int> data;
    size_t size = 10;
    size_t countRad = 4;

    randomVector(&data, size, countRad);
    data.push_back(-1);
    ASSERT_ANY_THROW(radixSort(&data));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
