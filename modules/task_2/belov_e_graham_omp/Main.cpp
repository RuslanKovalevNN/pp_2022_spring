// Copyright 2022 Belov Egor
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include "../../../modules/task_2/belov_e_graham_omp/graham.h"

TEST(OMP_Grahams_Algorithm, Test_1) {
  std::vector<point> tmp{{1, -7}, {3, -2}, {3, 1},  {5, 1},   {1, 3},
                         {1, 7},  {-3, 3}, {-2, 2}, {-1, -1}, {-3, -4}};
  auto grahOMP = OmpGraham(tmp.begin(), tmp.end());
  std::vector<point> res{{1, -7}, {5, 1}, {1, 7}, {-3, 3}, {-3, -4}};
  ASSERT_EQ(grahOMP, res);
}

TEST(OMP_Grahams_Algorithm, Test_2) {
  std::vector<point> tmp{{-3, 9}, {-1, 5}, {-5, 3}, {-3, 1}, {-1, -2}, {-4, -4},
                         {2, 7},  {2, 4},  {6, 4},  {3, -3}, {5, -5}};
  auto grahOMP = OmpGraham(tmp.begin(), tmp.end());
  std::vector<point> res{{5, -5}, {6, 4}, {2, 7}, {-3, 9}, {-5, 3}, {-4, -4}};
  ASSERT_EQ(grahOMP, res);
}

TEST(OMP_Grahams_Algorithm, Test_3) {
  std::vector<point> tmp{{3, 3},  {5, 1},  {8, 1},  {10, 2}, {2, -2}, {4, -3},
                         {7, -2}, {7, -4}, {-1, 1}, {-4, 2}, {-2, -3}};
  auto grahOMP = OmpGraham(tmp.begin(), tmp.end());
  std::vector<point> res{{7, -4}, {10, 2}, {3, 3}, {-4, 2}, {-2, -3}};
  ASSERT_EQ(grahOMP, res);
}

TEST(OMP_Grahams_Algorithm, Test_100_size) {
  int n = 100;
  auto tmp = RandPoint(n);
  auto grahOMP = OmpGraham(tmp.begin(), tmp.end());
  auto grah = Graham(tmp.begin(), tmp.end());
  ASSERT_EQ(grahOMP, grah);
}

TEST(OMP_Grahams_Algorithm, Test_1000_size) {
  int n = 1000;
  auto tmp = RandPoint(n);
  auto grahOMP = OmpGraham(tmp.begin(), tmp.end());
  auto grah = Graham(tmp.begin(), tmp.end());
  ASSERT_EQ(grahOMP, grah);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
