// Copyright 2018 Nesterov Alexander
#ifndef MODULES_TEST_TASKS_TEST_STD_OPS_STD_H_
#define MODULES_TEST_TASKS_TEST_STD_OPS_STD_H_

#include <vector>
#include <string>

void vec_gen(std::vector<int>* vec, int len);
std::vector<int> Odd_Even_Merge_Parallel(const std::vector<int>& arr, int len);
std::vector<int> Odd_Even_Merge(const std::vector<int>& arr, int len);

#endif  // MODULES_TEST_TASKS_TEST_STD_OPS_STD_H_
