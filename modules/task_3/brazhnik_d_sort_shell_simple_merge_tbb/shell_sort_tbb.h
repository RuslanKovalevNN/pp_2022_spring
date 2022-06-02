// Copyright 2022 Brazhnik Dmitry

#ifndef MODULES_TASK_3_BRAZHNIK_D_SORT_SHELL_SIMPLE_MERGE_TBB_SHELL_SORT_TBB_H_
#define MODULES_TASK_3_BRAZHNIK_D_SORT_SHELL_SIMPLE_MERGE_TBB_SHELL_SORT_TBB_H_

#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <random>
#include <ctime>
#include <numeric>
#include <string>

std::vector<int> getRandom(int N, int seed = 0);
std::vector<int> SortShell(const std::vector<int>& a, int size);
std::vector<std::vector<int>> division(const std::vector<int>& a, unsigned int n);
std::vector<int> Merge(const std::vector<std::vector<int>>& a, int n, int size);
std::vector<int> Merge_of_two_vectors(const std::vector<int>& a, const std::vector<int>& b);
std::vector<int> Shell_with_merge(const std::vector<int>& a, int n, int size);
std::vector<int> Shell_with_merge_tbb(const std::vector<int>& a, int n, int size);

#endif  // MODULES_TASK_3_BRAZHNIK_D_SORT_SHELL_SIMPLE_MERGE_TBB_SHELL_SORT_TBB_H_
