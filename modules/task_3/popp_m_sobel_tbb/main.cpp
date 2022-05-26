// Copyright 2022 Popp Maksim

#include <gtest/gtest.h>
#include <omp.h>

#include <iostream>
#include <vector>

#include "../../../modules/task_3/popp_m_sobel_tbb/popp_m_sobel_tbb.h"

TEST(imageStructure, canCompareImages) {
  image<int> img1({1, 2, 3, 4}, 2, 2);
  image<int> img2({1, 2, 3, 4}, 2, 2);
  image<int> img3({1, 0, 3, 4}, 2, 2);
  image<int> img4({1, 2, 3, 4}, 1, 4);

  ASSERT_TRUE(img1 == img1);
  ASSERT_TRUE(img1 == img2);

  ASSERT_FALSE(img1 == img3);
  ASSERT_FALSE(img1 == img4);
}

TEST(imageStructure, canCreateRandomMatrix) {
  ASSERT_NO_THROW(randImage(5, 5));
}

TEST(imageStructure, randMatrixWithNullSize) {
  ASSERT_ANY_THROW(randImage(0, 0));
}

TEST(imageStructure, createMatrixWithIncorrectSize) {
  ASSERT_ANY_THROW(image<int>({1, 2, 3, 4}, 1, 2));
}

TEST(seqSobelFilter, emptyMatrix) { ASSERT_ANY_THROW(image<uint8_t>(0, 0)); }

TEST(seqSobelFilter, sobelNoThrow) {
  auto img = randImage(5, 5);
  ASSERT_NO_THROW(sobelSequence(img));
}

TEST(seqSobelFilter, sobelChangeMatrix) {
  auto img = randImage(5, 5);
  auto res = sobelSequence(img);
  ASSERT_EQ(img._columns, res._columns);
  ASSERT_EQ(img._rows, res._rows);
  ASSERT_NE(img._matrix, res._matrix);
}

TEST(parallelSobelFilter, sobelChangeMatrix) {
  auto img = randImage(5, 5);
  auto res = sobelTbb(img);
  ASSERT_EQ(img._columns, res._columns);
  ASSERT_EQ(img._rows, res._rows);
  ASSERT_NE(img._matrix, res._matrix);
}

TEST(parallelSobelFilter, seqAndParIsEqual) {
  auto img = randImage(100, 100);

  auto startPar = omp_get_wtime();
  auto parRes = sobelTbb(img);
  auto stopPar = omp_get_wtime();

  auto startSeq = omp_get_wtime();
  auto seqRes = sobelSequence(img);
  auto stopSeq = omp_get_wtime();

  std::cout << "Sequnce: " << stopSeq - startSeq << "\n"
            << "Parallel: " << stopPar - startPar << "\n"
            << "Eff: "
            << (stopSeq - startSeq) / static_cast<double>(stopPar - startPar)
            << "\n";

  ASSERT_EQ(parRes, seqRes);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
