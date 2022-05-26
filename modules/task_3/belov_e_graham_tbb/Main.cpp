// Copyright 2022 Belov Egor

#include <gtest/gtest.h>
#include <cstdlib>
#include <iostream>

#include "../../../modules/task_3/belov_e_graham_tbb/graham.h"

std::vector<Point> Array = RandPoint(5000);

TEST(Graham_Alg, Graham_100_Test) {
  std::vector<Point> Q = RandPoint(100);
  std::vector<Point> hull = TbbGraham(Q);
  std::vector<Point> hull1 = Graham(Q.begin(), Q.end());
  ASSERT_EQ(hull, hull1);
}

TEST(Graham_Alg, Graham_1000_Test) {
  std::vector<Point> Q = RandPoint(1000);
  std::vector<Point> hull = TbbGraham(Q);
  std::vector<Point> hull1 = Graham(Q.begin(), Q.end());
  ASSERT_EQ(hull, hull1);
}/**/

TEST(Graham_Alg, Graham_Seq) {
  std::vector<Point> Q = Array;
  std::vector<Point> hull1 = Graham(Q.begin(), Q.end());
  ASSERT_EQ(hull1, hull1);
}
/**/
TEST(Graham_Alg, Graham_Tbb) {
  std::vector<Point> Q = Array;
  std::vector<Point> hull = TbbGraham(Q);
  ASSERT_EQ(hull, hull);
}

TEST(Graham_Alg, Graham_Array) {
  std::vector<Point> Q = Array;
  std::vector<Point> hull = TbbGraham(Q);
  std::vector<Point> hull1 = Graham(Q.begin(), Q.end());
  ASSERT_EQ(hull, hull1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
