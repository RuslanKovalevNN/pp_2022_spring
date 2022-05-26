// Copyright 2022 Kovalev Ruslan
#ifndef MODULES_TASK_3_KOVALEV_R_ODD_EVEN_SORT_TBB_ODD_EVEN_SORT_TBB_H_
#define MODULES_TASK_3_KOVALEV_R_ODD_EVEN_SORT_TBB_ODD_EVEN_SORT_TBB_H_

#include <vector>
#include <string>

void vec_gen(std::vector<int>* vec, int len);
int getMax(std::vector<int>* arr, int sz);
int ParalleGetMax(std::vector<int>* arr, int sz);
void Odd_Even_Merge(std::vector<int>* arr, int len);
void Odd_Even_Merge_Parallel(std::vector<int>* arr, int len);
void countingSortParallel(std::vector<int>* arr, int size, int place);
void getSequantialSort(std::vector<int>* arr, int sz);

void countingSort(std::vector<int>* arr, int size, int place);

void getSortParallel(std::vector<int>* arr, int sz);


#endif  // MODULES_TASK_3_KOVALEV_R_ODD_EVEN_SORT_TBB_ODD_EVEN_SORT_TBB_H_
