// Copyright 2022 Groshev Nickolay
#include <time.h>
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "./integration_monte_carlo.h"

std::function<double(const std::vector<double>&)> f1 = [](const std::vector<double>& x) {
  return 2 * x[0];
};

std::function<double(const std::vector<double>&)> f2 = [](const std::vector<double>& x) {
  return 3 * x[0] + 2 * x[1];
};

std::function<double(const std::vector<double>&)> f3 = [](const std::vector<double>& x) {
  return x[0] + x[1] + x[2];
};

std::function<double(const std::vector<double>&)> f4 = [](const std::vector<double>& x) {
  return x[0] * x[0] + 1.5 * x[1] + sin(x[2]);
};


TEST(Integration_Monte_Carlo_Seq, n_is_0) {
  double low = 0.0, top = 10.0;
  ASSERT_ANY_THROW(getIntegralSequential(-1, { low }, {top}, f1));
}


TEST(Integration_Monte_Carlo_Seq, dimension_is_1) {
  double low = 0.0, top = 3.0;
  clock_t start = clock();
  double res = getIntegralSequential(200000, { low }, { top }, f1);
  clock_t end = clock();
  double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
  printf("Sequence algorithm: %f seconds\n", seconds);
  ASSERT_NEAR(res, 9.0, 1);
}

TEST(Integration_Monte_Carlo_Seq, dimension_is_2) {
  std::vector<double>low = { -1.0, 1.0 };
  std::vector<double>top = { 0.0, 2.0 };
  clock_t start = clock();
  double res = getIntegralSequential(200000, low, top, f2);
  clock_t end = clock();
  double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
  printf("Sequence algorithm: %f seconds\n", seconds);
  ASSERT_NEAR(res, 1.5, 1);
}

TEST(Integration_Monte_Carlo_Seq, mdimension_is_3_v1) {
  std::vector<double>low = { -4.0, 0.0, 1.5 };
  std::vector<double>top = { -3.0, 5.0, 3.0 };
  clock_t start = clock();
  double res = getIntegralSequential(200000, low, top, f3);
  clock_t end = clock();
  double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
  printf("Sequence algorithm: %f seconds\n", seconds);
  ASSERT_NEAR(res, 9.375, 0.1);
}

TEST(Integration_Monte_Carlo_Seq, dimension_is_3_v2) {
  std::vector<double>low = { 0.15, 0.0, 1.5 };
  std::vector<double>top = { 1.0, 2.0, 3.0 };
  clock_t start = clock();
  double res = getIntegralSequential(200000, low, top, f4);
  clock_t end = clock();
  double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
  printf("Sequence algorithm: %f seconds\n", seconds);
  ASSERT_NEAR(res, 6.62486548705585, 0.1);
}


TEST(Integration_Monte_Carlo_TBB, n_is_0) {
  double low = 0.0, top = 10.0;
  ASSERT_ANY_THROW(getIntegralTBB(-1, {low}, {top}, f1));
}

TEST(Integration_Monte_Carlo_TBB, dimension_is_1) {
  double low = 0.0, top = 3.0;
  clock_t start_seq = clock();
  double res_seq = getIntegralSequential(100000, {low}, {top}, f1);
  clock_t end_seq = clock();
  double seconds_seq = static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;
  printf("Sequence algorithm: %f seconds\n", seconds_seq);

  clock_t start_tbb = clock();
  double res_tbb = getIntegralTBB(100000, {low}, {top}, f1);
  clock_t end_tbb = clock();
  double seconds_tbb = static_cast<double>(end_tbb - start_tbb) / CLOCKS_PER_SEC;
  printf("TBB algorithm: %f seconds\n", seconds_tbb);
  printf("boost RATE: %f \n", seconds_seq / seconds_tbb);

  ASSERT_NEAR(res_seq, res_tbb, 0.2);
}

TEST(Integration_Monte_Carlo_TBB, dimension_is_2) {
  std::vector<double> low = {-1.0, 1.0};
  std::vector<double> top = {0.0, 2.0};
  clock_t start_seq = clock();
  double res_seq = getIntegralSequential(100000, {low}, {top}, f2);
  clock_t end_seq = clock();
  double seconds_seq =
      static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;
  printf("Sequence algorithm: %f seconds\n", seconds_seq);

  clock_t start_tbb = clock();
  double res_tbb = getIntegralTBB(100000, {low}, {top}, f2);
  clock_t end_tbb = clock();
  double seconds_tbb =
      static_cast<double>(end_tbb - start_tbb) / CLOCKS_PER_SEC;
  printf("TBB algorithm: %f seconds\n", seconds_tbb);
  printf("boost RATE: %f \n", seconds_seq / seconds_tbb);
  ASSERT_NEAR(res_seq, res_tbb, 0.2);
}

TEST(Integration_Monte_Carlo_TBB, mdimension_is_3_v1) {
  std::vector<double> low = {-4.0, 0.0, 1.5};
  std::vector<double> top = {-3.0, 3.3, 3.0};
  clock_t start_seq = clock();
  double res_seq = getIntegralSequential(100000, {low}, {top}, f3);
  clock_t end_seq = clock();
  double seconds_seq =
      static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;
  printf("Sequence algorithm: %f seconds\n", seconds_seq);

  clock_t start_tbb = clock();
  double res_tbb = getIntegralTBB(100000, {low}, {top}, f3);
  clock_t end_tbb = clock();
  double seconds_tbb =
      static_cast<double>(end_tbb - start_tbb) / CLOCKS_PER_SEC;
  printf("TBB algorithm: %f seconds\n", seconds_tbb);
  printf("boost RATE: %f \n", seconds_seq / seconds_tbb);
  ASSERT_NEAR(res_seq, res_tbb, 0.2);
}

TEST(Integration_Monte_Carlo_TBB, dimension_is_3_v2) {
  std::vector<double> low = {0.15, 0.0, 1.5};
  std::vector<double> top = {1.0, 2.0, 3.0};
  clock_t start_seq = clock();
  double res_seq = getIntegralSequential(100000, {low}, {top}, f4);
  clock_t end_seq = clock();
  double seconds_seq =
      static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;
  printf("Sequence algorithm: %f seconds\n", seconds_seq);

  clock_t start_tbb = clock();
  double res_tbb = getIntegralTBB(100000, {low}, {top}, f4);
  clock_t end_tbb = clock();
  double seconds_tbb =
      static_cast<double>(end_tbb - start_tbb) / CLOCKS_PER_SEC;
  printf("TBB algorithm: %f seconds\n", seconds_tbb);
  printf("boost RATE: %f \n", seconds_seq / seconds_tbb);
  ASSERT_NEAR(res_seq, res_tbb, 0.2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
