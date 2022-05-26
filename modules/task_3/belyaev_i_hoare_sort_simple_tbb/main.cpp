// Copyright 2022 Belyaev Ilya
#include <tbb/tbb.h>
#include <gtest/gtest.h>
#include <algorithm>

#include "./hoare_sort_tbb.h"

TEST(Hoare_Sort_Simple_Merge_TBB, Empty_Vector) {
    std::vector<int> v = getRandomVector(0);
    int lastIndex = static_cast<int>(v.size() - 1);
    ASSERT_NO_THROW(hoareSort(&v, 0, lastIndex));
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Positive_Numbers) {
    std::vector<int> v = getRandomVector(100, 1);
    int lastIndex = static_cast<int>(v.size() - 1);
    ASSERT_NO_THROW(hoareSort(&v, 0, lastIndex));
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Numbers_Small_Size) {
    std::vector<int> v = getRandomVector(100);
    int lastIndex = static_cast<int>(v.size() - 1);
    ASSERT_NO_THROW(hoareSort(&v, 0, lastIndex));
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Numbers_Big_Size) {
    std::vector<int> v = getRandomVector(10000);
    int lastIndex = static_cast<int>(v.size() - 1);
    ASSERT_NO_THROW(hoareSort(&v, 0, lastIndex));
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Already_Sorted) {
    std::vector<int> v = getRandomVector(100, 2);
    int lastIndex = static_cast<int>(v.size() - 1);
    ASSERT_NO_THROW(hoareSort(&v, 0, lastIndex));
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Worst_Case_Unsorted) {
    std::vector<int> v = getRandomVector(100, 3);
    int lastIndex = static_cast<int>(v.size() - 1);
    ASSERT_NO_THROW(hoareSort(&v, 0, lastIndex));
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Left_Empty) {
    std::vector<int> v1 = getRandomVector(100);
    std::vector<int> v2 = getRandomVector(0);
    hoareSort(&v1, 0, v1.size() - 1);
    std::vector<int> v = merge(v1, v2);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Right_Empty) {
    std::vector<int> v1 = getRandomVector(0);
    std::vector<int> v2 = getRandomVector(100);
    hoareSort(&v2, 0, v2.size() - 1);
    std::vector<int> v = merge(v1, v2);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Same_Size) {
    std::vector<int> v1 = getRandomVector(100);
    std::vector<int> v2 = getRandomVector(100);
    hoareSort(&v1, 0, v1.size() - 1);
    hoareSort(&v2, 0, v2.size() - 1);
    std::vector<int> v = merge(v1, v2);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Different_Size) {
    std::vector<int> v1 = getRandomVector(75);
    std::vector<int> v2 = getRandomVector(25);
    hoareSort(&v1, 0, v1.size() - 1);
    hoareSort(&v2, 0, v2.size() - 1);
    std::vector<int> v = merge(v1, v2);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Large_Vectors) {
    std::vector<int> v1 = getRandomVector(5000);
    std::vector<int> v2 = getRandomVector(5000);
    hoareSort(&v1, 0, v1.size() - 1);
    hoareSort(&v2, 0, v2.size() - 1);
    std::vector<int> v = merge(v1, v2);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Even_Size) {
    std::vector<int> v = getRandomVector(100000);
    ASSERT_NO_THROW(runHoareSort(&v));
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Odd_Size) {
    std::vector<int> v = getRandomVector(111111);
    ASSERT_NO_THROW(runHoareSort(&v));
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(Hoare_Sort_Simple_Merge_TBB, Compare_Time1) {
    std::vector<int> v1 = getRandomVector(100000);

    tbb::tick_count t0 = tbb::tick_count::now();
    ASSERT_NO_THROW(runHoareSort(&v1, 4));
    tbb::tick_count t1 = tbb::tick_count::now();
    std::cout << "Tbb: " << (t1 - t0).seconds() << std::endl;

    std::vector<int> v2 = getRandomVector(100000);

    tbb::tick_count t3 = tbb::tick_count::now();
    ASSERT_NO_THROW(hoareSort(&v2, 0, v2.size() - 1));
    tbb::tick_count t4 = tbb::tick_count::now();
    std::cout << "Not: " << (t4 - t3).seconds() << std::endl;
}

TEST(Hoare_Sort_Simple_Merge_TBB, Compare_Time2) {
  std::vector<int> v1 = getRandomVector(1000000);

  tbb::tick_count t0 = tbb::tick_count::now();
  ASSERT_NO_THROW(runHoareSort(&v1, 4));
  tbb::tick_count t1 = tbb::tick_count::now();
  std::cout << "Tbb: " << (t1 - t0).seconds() << std::endl;

  std::vector<int> v2 = getRandomVector(1000000);

  tbb::tick_count t3 = tbb::tick_count::now();
  ASSERT_NO_THROW(hoareSort(&v2, 0, v2.size() - 1));
  tbb::tick_count t4 = tbb::tick_count::now();
  std::cout << "Not: " << (t4 - t3).seconds() << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
