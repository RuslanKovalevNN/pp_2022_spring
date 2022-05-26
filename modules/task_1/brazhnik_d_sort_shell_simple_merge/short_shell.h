// Copyright 2022 Brazhnik Dmitry

#ifndef MODULES_TASK_1_BRAZHNIK_D_SORT_SHELL_SIMPLE_MERGE_SHORT_SHELL_H_
#define MODULES_TASK_1_BRAZHNIK_D_SORT_SHELL_SIMPLE_MERGE_SHORT_SHELL_H_

#include <vector>
#include <utility>

std::vector<int> getRandom(int N, int seed = 0);
std::vector<int> SortShell(const std::vector<int>& a, int size);
std::vector<std::vector<int>> division(const std::vector<int>& a, unsigned int n);
std::vector<int> Merge(const std::vector<std::vector<int>>& a, int n, int size);
std::vector<int> Merge_of_two_vectors(const std::vector<int>& a, const std::vector<int>& b);
std::vector<int> Shell_with_merge(const std::vector<int>& a, int n, int size);

#endif  // MODULES_TASK_1_BRAZHNIK_D_SORT_SHELL_SIMPLE_MERGE_SHORT_SHELL_H_
