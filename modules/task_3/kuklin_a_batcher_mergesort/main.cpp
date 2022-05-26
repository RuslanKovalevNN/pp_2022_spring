// Copyright 2022 Kuklin Andrey
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <iostream>
#include "./batcher_mergesort.h"

TEST(kuklin_a_betcher_mergesort, genRandVec) {
  ASSERT_NO_THROW(getRandVec(10, -100., 100.));
}

TEST(kuklin_a_betcher_mergesort, can_sort_positive_nubm) {
  auto vec = getRandVec(10, 10., 30.);

  ASSERT_NO_THROW(floatRadixSort(&vec));
}

TEST(kuklin_a_betcher_mergesort, can_sort_negative_nubm) {
  auto vec = getRandVec(10, -30., -20.);

  ASSERT_NO_THROW(floatRadixSort(&vec));
}

TEST(kuklin_a_betcher_mergesort, can_sort_rand_nubm) {
  auto vec = getRandVec(10, -100., 100.);

  ASSERT_NO_THROW(floatRadixSort(&vec));
}

TEST(kuklin_a_betcher_mergesort, radix_sort_correct) {
  auto vec = getRandVec(100, -100., 100.);

  auto copy_vec(vec);
  std::sort(copy_vec.begin(), copy_vec.end());

  floatRadixSort(&vec);
  ASSERT_EQ(vec, copy_vec);
}

TEST(kuklin_a_betcher_mergesort, can_merge_2_vec) {
  auto vec = getRandVec(12, -100., 100.);
  auto size_copy = vec.size() / 2;
  std::vector<double> copy_vec_first(vec.begin(), vec.begin() + size_copy);
  std::vector<double> copy_vec_second(vec.begin() + size_copy, vec.end());

  floatRadixSort(&copy_vec_first);
  floatRadixSort(&copy_vec_second);

  ASSERT_NO_THROW(batcherMerge(copy_vec_first, copy_vec_second));
}

TEST(kuklin_a_betcher_mergesort, correct_merge_vec_eq_size) {
  auto vec = getRandVec(10, -100., 100.);
  auto size_copy = vec.size() / 2;
  std::vector<double> copy_vec_first(vec.begin(), vec.begin() + size_copy);
  std::vector<double> copy_vec_second(vec.begin() + size_copy, vec.end());

  floatRadixSort(&copy_vec_first);
  floatRadixSort(&copy_vec_second);
  floatRadixSort(&vec);

  auto merged_vec = batcherMerge(copy_vec_first, copy_vec_second);
  ASSERT_EQ(merged_vec, vec);
}

TEST(kuklin_a_betcher_mergesort, correct_merge_vec_eq_diff_size) {
  auto vec = getRandVec(13, -100., 100.);
  auto size_copy = vec.size() / 2;
  std::vector<double> copy_vec_first(vec.begin(), vec.begin() + size_copy);
  std::vector<double> copy_vec_second(vec.begin() + size_copy, vec.end());

  floatRadixSort(&copy_vec_first);
  floatRadixSort(&copy_vec_second);
  floatRadixSort(&vec);
  auto merged_vec = batcherMerge(copy_vec_first, copy_vec_second);

  ASSERT_EQ(merged_vec, vec);
}

TEST(kuklin_a_betcher_mergesort, correct_merge_3_vec) {
  auto vec = getRandVec(20, -100., 100.);
  auto size_copy = vec.size() / 3;
  std::vector<double> copy_vec_first(vec.begin(), vec.begin() + size_copy);
  std::vector<double> copy_vec_second(vec.begin() + size_copy,
                                      vec.begin() + 2 * size_copy);
  std::vector<double> copy_vec_third(vec.begin() + 2 * size_copy, vec.end());

  floatRadixSort(&copy_vec_first);
  floatRadixSort(&copy_vec_second);
  floatRadixSort(&copy_vec_third);
  floatRadixSort(&vec);
  auto tmp_vec = batcherMerge(copy_vec_first, copy_vec_second);
  auto merged_vec = batcherMerge(tmp_vec, copy_vec_third);

  ASSERT_EQ(merged_vec, vec);
}

TEST(kuklin_a_betcher_mergesort, correct_merge_4_vec) {
  auto vec = getRandVec(24, -100., 100.);
  auto size_copy = vec.size() / 4;
  std::vector<double> copy_vec_first(vec.begin(), vec.begin() + size_copy);
  std::vector<double> copy_vec_second(vec.begin() + size_copy,
                                      vec.begin() + 2 * size_copy);
  std::vector<double> copy_vec_third(vec.begin() + 2 * size_copy,
                                     vec.begin() + 3 * size_copy);
  std::vector<double> copy_vec_fourth(vec.begin() + 3 * size_copy,
                                     vec.end());

  floatRadixSort(&copy_vec_first);
  floatRadixSort(&copy_vec_second);
  floatRadixSort(&copy_vec_third);
  floatRadixSort(&copy_vec_fourth);
  floatRadixSort(&vec);
  auto first_half = batcherMerge(copy_vec_first, copy_vec_second);
  auto second_half = batcherMerge(copy_vec_third, copy_vec_fourth);
  auto merged_vec = batcherMerge(first_half, second_half);

  ASSERT_EQ(merged_vec, vec);
}

TEST(kuklin_a_betcher_mergesort, parallel_sort) {
  auto vec = getRandVec(12, -100., 100.);

  ASSERT_NO_THROW(floatRadixSortParallel(&vec));
}

TEST(kuklin_a_betcher_mergesort, parallel_sort_eq_sequence_v1) {
  auto seq_vec = getRandVec(17, -150., 150.);
  vector_d par_vec = seq_vec;

  floatRadixSort(&seq_vec);
  floatRadixSortParallel(&par_vec);

  ASSERT_EQ(seq_vec, par_vec);
}

TEST(kuklin_a_betcher_mergesort, parallel_sort_eq_sequence_v2) {
  auto seq_vec = getRandVec(21, -200., 200.);
  vector_d par_vec = seq_vec;

  floatRadixSort(&seq_vec);
  floatRadixSortParallel(&par_vec);

  ASSERT_EQ(seq_vec, par_vec);
}

TEST(kuklin_a_betcher_mergesort, parallel_sort_eq_sequence_v3) {
  auto seq_vec = getRandVec(39, -240., 240.);
  vector_d par_vec = seq_vec;

  floatRadixSort(&seq_vec);
  floatRadixSortParallel(&par_vec);

  ASSERT_EQ(seq_vec, par_vec);
}

TEST(kuklin_a_betcher_mergesort, parallel_sort_faster_sequence) {
  auto seq_vec = getRandVec(100, -100., 100.);
  vector_d par_vec = seq_vec;

  floatRadixSort(&seq_vec);
  floatRadixSortParallel(&par_vec);

  ASSERT_EQ(seq_vec, par_vec);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
