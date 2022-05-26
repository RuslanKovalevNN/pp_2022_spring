// Copyright 2022 Kazhaeva Anastasia
#include <gtest/gtest.h>

#include <vector>

#include "./djikstra.h"

TEST(Kazhaeva_Parallel_Deicstra, Test_ASSERT_NO_THROW) {
    std::vector<std::vector<int>> b = {
                  {0, 1, 7, 6, 3},
                  {1, 0, 3, 5, 4},
                  {7, 3, 0, 10, 5},
                  {6, 5, 10, 0, 4},
                  {3, 4, 5, 4, 0}
    };
  ASSERT_NO_THROW(djikstra(0, b));
}

TEST(Kazhaeva_Parallel_Deicstra, Test_ASSERT_NO_THROW_2) {
    std::vector<std::vector<int>> b = {
                  {0, 1, 7, 6, 3},
                  {1, 0, 3, 5, 4},
                  {7, 3, 0, 10, 5},
                  {6, 5, 10, 0, 4},
                  {3, 4, 5, 4, 0}
    };
  ASSERT_NO_THROW(parallelDjikstra(5, b));
}

TEST(Kazhaeva_Parallel_Deicstra, Test_ASSERT_NO_THROW_3) {
    std::vector<std::vector<int>> b = {
                  {0, 1, 7, 6, 3},
                  {1, 0, 3, 5, 4},
                  {7, 3, 0, 10, 5},
                  {6, 5, 10, 0, 4},
                  {3, 4, 5, 4, 0}
    };
    ASSERT_NO_THROW(sequentialDjikstra(b));
}

TEST(Kazhaeva_Parallel_Deicstra, Test_Deicstra_1) {
    std::vector<std::vector<int>> b = {
                    {0, 1, 7, 6, 3},
                    {1, 0, 3, 5, 4},
                    {7, 3, 0, 10, 5},
                    {6, 5, 10, 0, 4},
                    {3, 4, 5, 4, 0}
    };
    const std::vector<std::vector<int>> result1 = sequentialDjikstra(b);
    const std::vector<std::vector<int>> result2 = parallelDjikstra(4, b);
    ASSERT_EQ(result1 == result2, true);
}

TEST(Kazhaeva_Parallel_Deicstra, Test_Deicstra_2) {
    std::vector<std::vector<int>> b = {
                    {0, 1, 7, 6, 3},
                    {1, 0, 3, 5, 4},
                    {7, 3, 0, 10, 5},
                    {6, 5, 10, 0, 4},
                    {3, 4, 5, 4, 0}
    };
    const std::vector<std::vector<int>> result1 = sequentialDjikstra(b);
    const std::vector<std::vector<int>> result2 = parallelDjikstra(4, b);

    ASSERT_EQ(result1 == result2, true);
}

TEST(Kazhaeva_Parallel_Deicstra, Test_Deicstra_3) {
    std::vector<std::vector<int>> b = randomVectorDjikstra(50);
    ASSERT_NO_THROW(parallelDjikstra(4, b));
}

TEST(Kazhaeva_Parallel_Deicstra, Test_Deicstra_4) {
    std::vector<std::vector<int>> b = {
                    {0, 1, 7, 6, 3},
                    {1, 0, 3, 5, 4},
                    {7, 3, 0, 10, 5},
                    {6, 5, 10, 0, 4},
                    {3, 4, 5, 4, 0}
    };
    const std::vector<std::vector<int>> result1 = sequentialDjikstra(b);
    const std::vector<std::vector<int>> result2 = parallelDjikstra(4, b);

    ASSERT_EQ(result1 == result2, true);
}

TEST(Kazhaeva_Parallel_Deicstra, Test_Deicstra_5) {
    std::vector<std::vector<int>> b = randomVectorDjikstra(50);
    ASSERT_NO_THROW(parallelDjikstra(4, b));
}

TEST(Kazhaeva_Parallel_Deicstra, Test_Deicstra_6) {
    std::vector<std::vector<int>> b = randomVectorDjikstra(70);
    ASSERT_NO_THROW(parallelDjikstra(4, b));
}
