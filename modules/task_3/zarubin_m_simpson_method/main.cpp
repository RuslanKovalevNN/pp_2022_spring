// Copyright 2022 Zarubin Mikhail

#include <gtest/gtest.h>
#include <tbb/tick_count.h>
#include "./simpson_method.h"


TEST(SimpsonMethod, can_run_simpson_method_parallel) {
    std::vector<double> leftsBorders = { 1, 2 };
    std::vector<double> rightBorders = { 11, 9 };
    std::function<double(std::vector<double>)> func =
        [](std::vector<double> args) { return args[0] * args[1]; };
    sizeType dimension = 2;
    std::vector<sizeType> countParts = { 8, 4 };

    ASSERT_NO_THROW(simpsonMethodParallel(dimension, leftsBorders, rightBorders,
        func, countParts));
}

TEST(SimpsonMethod, simpos_method_parallel_works_correctly_with_one_variable) {
    std::vector<double> leftsBorders = { 2 };
    std::vector<double> rightBorders = { 4 };
    std::function<double(std::vector<double>)> funcOneVariable =
        [](std::vector<double> args) { return args[0]; };
    sizeType dimension = 1;
    std::vector<sizeType> countParts(1, 10);

    double expectedResult = 6.0;
    double result = simpsonMethodParallel(dimension, leftsBorders, rightBorders,
        funcOneVariable, countParts);

    ASSERT_NEAR(expectedResult, result, 0.001);
}

TEST(SimpsonMethod, simpos_method_parallel_works_correctly_with_two_variable) {
    std::vector<double> leftsBorders = { 2, -1 };
    std::vector<double> rightBorders = { 4, 5 };
    std::function<double(std::vector<double>)> funcTwoVariable =
        [](std::vector<double> args) { return args[0] * args[1]; };
    sizeType dimension = 2;
    std::vector<sizeType> countParts(2, 4);

    double expectedResult = 72.0;
    double result = simpsonMethodParallel(dimension, leftsBorders, rightBorders,
        funcTwoVariable, countParts);

    ASSERT_NEAR(expectedResult, result, 0.001);
}

TEST(SimpsonMethod, simpos_method_parallel_works_correctly_with_three_variable) {
    std::vector<double> leftsBorders = { 2, -1, 0 };
    std::vector<double> rightBorders = { 4, 5, 3 };
    std::function<double(std::vector<double>)> funcThreeVariable =
        [](std::vector<double> args) { return args[0] * args[1] * args[2]; };
    sizeType dimension = 3;
    std::vector<sizeType> countParts(3, 3);

    double expectedResult = 324.0;
    double result = simpsonMethodParallel(dimension, leftsBorders, rightBorders,
        funcThreeVariable, countParts);

    ASSERT_NEAR(expectedResult, result, 0.001);
}

TEST(SimpsonMethod, simpos_method_parallel_works_correctly_with_four_variable) {
    std::vector<double> leftsBorders = { 2, -1, 0, -3 };
    std::vector<double> rightBorders = { 4, 5, 3, 1 };
    std::function<double(std::vector<double>)> funcFourVariable =
        [](std::vector<double> args) { return args[0] * args[1] * args[2] * args[3]; };
    sizeType dimension = 4;
    std::vector<sizeType> countParts(4, 2);

    double expectedResult = -1296.0;
    double result = simpsonMethodParallel(dimension, leftsBorders, rightBorders,
        funcFourVariable, countParts);

    ASSERT_NEAR(expectedResult, result, 0.001);
}

TEST(SimpsonMethod, simpos_method_parallel_works_correctly_with_five_variable) {
    std::vector<double> leftsBorders = { 2, -1, 0, -3, 1 };
    std::vector<double> rightBorders = { 4, 5, 3, 1, 2 };
    std::function<double(std::vector<double>)> funcFiveVariable =
        [](std::vector<double> args) { return args[0] * args[1] * args[2] * args[3] * args[4]; };
    sizeType dimension = 5;
    std::vector<sizeType> countParts(5, 2);

    double expectedResult = -1944.0;
    double result = simpsonMethodParallel(dimension, leftsBorders, rightBorders,
        funcFiveVariable, countParts);

    ASSERT_NEAR(expectedResult, result, 0.001);
}

TEST(DISABLED_SimpsonMethod, boost_test) {
    std::vector<double> leftsBorders = { 2, -1, 0, -3, 1 };
    std::vector<double> rightBorders = { 4, 5, 3, 1, 2 };
    std::function<double(std::vector<double>)> funcFiveVariable =
        [](std::vector<double> args) { return args[0] * args[1] * args[2] * args[3] * args[4]; };
    sizeType dimension = 5;
    std::vector<sizeType> countParts(5, 7);

    auto startSeq = tbb::tick_count::now();
    simpsonMethodSeq(dimension, leftsBorders, rightBorders, funcFiveVariable, countParts);
    auto finishSeq = tbb::tick_count::now();

    auto startParallel = tbb::tick_count::now();
    simpsonMethodParallel(dimension, leftsBorders, rightBorders, funcFiveVariable, countParts);
    auto finishParallel = tbb::tick_count::now();

    auto seqTime = (finishSeq - startSeq).seconds();
    auto parallelTime = (finishParallel - startParallel).seconds();
    auto boost = seqTime / parallelTime;

    printf("seqTime = %lf\nparallelTime = %lf\nboost = %lf\n", seqTime, parallelTime, boost);
}
