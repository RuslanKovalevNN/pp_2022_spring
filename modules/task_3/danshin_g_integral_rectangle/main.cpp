// Copyright 2022 Gleb "belgad" Danshin
#include <cmath>
#include <chrono>  // NOLINT [build/c++11]
#include <iostream>

#include "tbb/tbb.h"
#include "gtest/gtest.h"

#include "../../../modules/task_3/danshin_g_integral_rectangle/integral_rectangle.hpp"

TEST(IntegralRectangle, Function1) {
    size_t dim = 1;
    auto step = new double{0.1};
    auto lower = new double{0.0};
    auto upper = new double{1.0};
    auto func = [](double* point) -> double {
        return point[0];
    };
    auto seq_start_time = std::chrono::system_clock::now();
    auto seq_result = IntegrateSequence(dim, step, lower, upper, func);
    auto seq_end_time = std::chrono::system_clock::now();
    auto seq_duration = std::chrono::duration_cast<std::chrono::microseconds>
        (seq_end_time - seq_start_time).count();
    auto start_time = tbb::tick_count::now();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = tbb::tick_count::now();
    auto duration = static_cast<size_t>((end_time - start_time).seconds() * 1000000);
    std::cout << "Sequence time: " << seq_duration << " us" << std::endl;
    std::cout << "Parallel time: " << duration << " us" << std::endl;
    std::cout << "Efficiency:    "
        << static_cast<double>(seq_duration) / static_cast<double>(duration)
        << std::endl;
    delete step;
    delete lower;
    delete upper;
    ASSERT_DOUBLE_EQ(result, 0.45);
    ASSERT_NEAR(result, seq_result, 0.000001);
}

TEST(IntegralRectangle, Function2Step1) {
    size_t dim = 2;
    auto step = new double[2]{0.1, 0.1};
    auto lower = new double[2]{0.0, 0.0};
    auto upper = new double[2]{1.0, 1.0};
    auto func = [](double* point) -> double {
        return point[0] * point[1];
    };
    auto seq_start_time = std::chrono::system_clock::now();
    auto seq_result = IntegrateSequence(dim, step, lower, upper, func);
    auto seq_end_time = std::chrono::system_clock::now();
    auto seq_duration = std::chrono::duration_cast<std::chrono::microseconds>
        (seq_end_time - seq_start_time).count();
    auto start_time = tbb::tick_count::now();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = tbb::tick_count::now();
    auto duration = static_cast<size_t>((end_time - start_time).seconds() * 1000000);
    std::cout << "Sequence time: " << seq_duration << " us" << std::endl;
    std::cout << "Parallel time: " << duration << " us" << std::endl;
    std::cout << "Efficiency:    "
        << static_cast<double>(seq_duration) / static_cast<double>(duration)
        << std::endl;
    delete[] step;
    delete[] lower;
    delete[] upper;
    ASSERT_DOUBLE_EQ(result, 0.2025);
    ASSERT_NEAR(result, seq_result, 0.000001);
}

TEST(IntegralRectangle, Function2Step2) {
    size_t dim = 2;
    auto step = new double[2]{0.001, 0.001};
    auto lower = new double[2]{0.0, 0.0};
    auto upper = new double[2]{1.0, 1.0};
    auto func = [](double* point) -> double {
        return point[0] * point[1];
    };
    auto seq_start_time = std::chrono::system_clock::now();
    auto seq_result = IntegrateSequence(dim, step, lower, upper, func);
    auto seq_end_time = std::chrono::system_clock::now();
    auto seq_duration = std::chrono::duration_cast<std::chrono::microseconds>
        (seq_end_time - seq_start_time).count();
    auto start_time = tbb::tick_count::now();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = tbb::tick_count::now();
    auto duration = static_cast<size_t>((end_time - start_time).seconds() * 1000000);
    std::cout << "Sequence time: " << seq_duration << " us" << std::endl;
    std::cout << "Parallel time: " << duration << " us" << std::endl;
    std::cout << "Efficiency:    "
        << static_cast<double>(seq_duration) / static_cast<double>(duration)
        << std::endl;
    delete[] step;
    delete[] lower;
    delete[] upper;
    ASSERT_NEAR(result, 0.2495, 0.0001);
    ASSERT_NEAR(result, seq_result, 0.000001);
}

TEST(IntegralRectangle, Function3Step1) {
    size_t dim = 3;
    auto step = new double[3]{0.1, 0.1, 0.1};
    auto lower = new double[3]{0.0, 0.0, 0.0};
    auto upper = new double[3]{2.0, 1.5, 1.0};
    auto func = [](double* point) -> double {
        return std::sqrt(point[0]) * point[1] + point[2];
    };
    auto seq_start_time = std::chrono::system_clock::now();
    auto seq_result = IntegrateSequence(dim, step, lower, upper, func);
    auto seq_end_time = std::chrono::system_clock::now();
    auto seq_duration = std::chrono::duration_cast<std::chrono::microseconds>
        (seq_end_time - seq_start_time).count();
    auto start_time = tbb::tick_count::now();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = tbb::tick_count::now();
    auto duration = static_cast<size_t>((end_time - start_time).seconds() * 1000000);
    std::cout << "Sequence time: " << seq_duration << " us" << std::endl;
    std::cout << "Parallel time: " << duration << " us" << std::endl;
    std::cout << "Efficiency:    "
        << static_cast<double>(seq_duration) / static_cast<double>(duration)
        << std::endl;
    delete[] step;
    delete[] lower;
    delete[] upper;
    ASSERT_NEAR(result, 3.249, 0.001);
    ASSERT_NEAR(result, seq_result, 0.000001);
}

TEST(IntegralRectangle, Function3Step2) {
    size_t dim = 3;
    auto step = new double[3]{0.01, 0.01, 0.1};
    auto lower = new double[3]{0.0, 0.0, 0.0};
    auto upper = new double[3]{2.0, 1.5, 1.0};
    auto func = [](double* point) -> double {
        return std::sqrt(point[0]) * point[1] + point[2];
    };
    auto seq_start_time = std::chrono::system_clock::now();
    auto seq_result = IntegrateSequence(dim, step, lower, upper, func);
    auto seq_end_time = std::chrono::system_clock::now();
    auto seq_duration = std::chrono::duration_cast<std::chrono::microseconds>
        (seq_end_time - seq_start_time).count();
    auto start_time = tbb::tick_count::now();
    auto result = Integrate(dim, step, lower, upper, func);
    auto end_time = tbb::tick_count::now();
    auto duration = static_cast<size_t>((end_time - start_time).seconds() * 1000000);
    std::cout << "Sequence time: " << seq_duration << " us" << std::endl;
    std::cout << "Parallel time: " << duration << " us" << std::endl;
    std::cout << "Efficiency:    "
        << static_cast<double>(seq_duration) / static_cast<double>(duration)
        << std::endl;
    delete[] step;
    delete[] lower;
    delete[] upper;
    ASSERT_NEAR(result, 3.449, 0.0001);
    ASSERT_NEAR(result, seq_result, 0.000001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
