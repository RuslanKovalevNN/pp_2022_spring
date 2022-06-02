// Copyright 2022 Kovalev Ruslan
#ifndef MODULES_TASK_2_KOVALEV_R_RADIX_SORT_OMP_KOVALEV_R_RADIX_SORT_OMP_H_
#define MODULES_TASK_2_KOVALEV_R_RADIX_SORT_OMP_KOVALEV_R_RADIX_SORT_OMP_H_

#include <string>
#include <vector>

void vec_gen(std::vector<int>& vec, int len);
std::vector<int> Odd_Even_Merge(const std::vector<int>& arr, int len);
std::vector<int> getParallelRadixSort(const std::vector<int>& arr, int len);
void countingSortParallel(std::vector<int>* arr, int size, int place);
void countingSort(std::vector<int>* arr, int size, int place);
std::vector<int> Odd_Even_Merge_Parallel(const std::vector<int>& arr, int len);

#endif  // MODULES_TASK_2_KOVALEV_R_RADIX_SORT_OMP_KOVALEV_R_RADIX_SORT_OMP_H_
