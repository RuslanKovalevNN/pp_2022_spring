//  Copyright 2022 Purtova Ksenia
#ifndef MODULES_TASK_1_PURTOVA_K_SHELL_SORT_BATCHER_MERGE_SHELL_SORT_H_
#define MODULES_TASK_1_PURTOVA_K_SHELL_SORT_BATCHER_MERGE_SHELL_SORT_H_

#include <vector>

std::vector<int> Shell(const std::vector<int>& A, int n);
std::vector <int> MergerEvenOdd(const std::vector<int>& arr1, const std::vector<int>& arr2, int i1, int i2);
std::vector<int> BatcherEvenNumber(const std::vector<int>& arr1, const std::vector<int>& arr2);
std::vector<int> BatcherOddNumber(const std::vector<int>& arr1, const std::vector<int>& arr2);
std::vector<int> BatcherMerger(const std::vector<int>& arr1, const std::vector<int>& arr2);
std::vector<int> ShellWithBatcher(const std::vector<int>& A, int n);
std::vector<int> VectorRandomizer(int size);
#endif  //  MODULES_TASK_1_PURTOVA_K_SHELL_SORT_BATCHER_MERGE_SHELL_SORT_H_
