// Copyright 2022 Trevogin Kirill
#ifndef MODULES_TASK_3_TREVOGIN_K_HOAR_TBB_HOAR_H_
#define MODULES_TASK_3_TREVOGIN_K_HOAR_TBB_HOAR_H_
#include <tbb/tbb.h>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>
#include <utility>
#include <vector>

void Get_Random_Array(double* arr, int size);
int HoarePartition(double* arr, int left_index, int right_index);
void qHoareSort(double* arr, int left_index, int right_index);
int IsSorted(double* arr, int n);
void Copy_elements(double* a1, double* a2, int n);
void qHoareSortTbb(double* arr, int n);
#endif  // MODULES_TASK_3_TREVOGIN_K_HOAR_TBB_HOAR_H_
