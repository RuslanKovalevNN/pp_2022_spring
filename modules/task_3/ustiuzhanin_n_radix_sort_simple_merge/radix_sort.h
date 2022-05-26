// Copyright 2022 Ustiuzhanin Nikita
#ifndef MODULES_TASK_3_USTIUZHANIN_N_RADIX_SORT_SIMPLE_MERGE_RADIX_SORT_H_
#define MODULES_TASK_3_USTIUZHANIN_N_RADIX_SORT_SIMPLE_MERGE_RADIX_SORT_H_

#include <tbb/tbb.h>
#include <vector>
#include <list>
#include <random>
#include <ctime>
#include <algorithm>

using std::vector;
using std::list;

void randomVector(vector<int>* data, size_t size, size_t rad);
size_t rad(size_t value);
int getNum(int val, size_t pos);
void radixSort(vector<int>* data);
vector<int> simpleMerge(const vector<int>& firstVector,
    const vector<int>& secondVector);
void radixSortTBB(vector<int>* data);

#endif  // MODULES_TASK_3_USTIUZHANIN_N_RADIX_SORT_SIMPLE_MERGE_RADIX_SORT_H_
