// Copyright 2022 George Amberson
#ifndef MODULES_TASK_4_STEPANOV_HOAR_WITH_O_D_BATCHER_STEPANOV_HOAR_SORT_WITH_ODD_EVEN_BATCHER_MERGE_H_
#define MODULES_TASK_4_STEPANOV_HOAR_WITH_O_D_BATCHER_STEPANOV_HOAR_SORT_WITH_ODD_EVEN_BATCHER_MERGE_H_
#include <omp.h>
#include <vector>
#include <list>
#include <algorithm>
#include <thread> //NOLINT
std::vector<float>* create_random_vector(int size_n);
void hoar_sort_with_batch_merge(std::vector<float>* vec);
void hoar_sort_with_batch_merge_std(std::vector<float>* vec);
#endif  // MODULES_TASK_4_STEPANOV_HOAR_WITH_O_D_BATCHER_STEPANOV_HOAR_SORT_WITH_ODD_EVEN_BATCHER_MERGE_H_
