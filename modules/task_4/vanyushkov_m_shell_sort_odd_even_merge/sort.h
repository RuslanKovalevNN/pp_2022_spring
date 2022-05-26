// Copyright 2022 Vanyushkov Maxim
#ifndef MODULES_TASK_4_VANYUSHKOV_M_SHELL_SORT_ODD_EVEN_MERGE_SORT_H_
#define MODULES_TASK_4_VANYUSHKOV_M_SHELL_SORT_ODD_EVEN_MERGE_SORT_H_

#include <iostream>
#include <vector>
#include <chrono>  // NOLINT [build/c++11]
#include <thread>  // NOLINT [build/c++11]

std::vector<int> getRandomVector(int size);
void ShellSortSequantial(std::vector<int>* vec);
void ShellSortParallel(std::vector<int>* vec);
bool checkSort(const std::vector<int>& vec);

#endif  // MODULES_TASK_4_VANYUSHKOV_M_SHELL_SORT_ODD_EVEN_MERGE_SORT_H_
