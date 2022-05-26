// Copyright 2022 Kim Nikita
#ifndef MODULES_TASK_3_KIM_N_RADIX_SORT_RADIX_SORT_H_
#define MODULES_TASK_3_KIM_N_RADIX_SORT_RADIX_SORT_H_

#include <tbb/task.h>
#include <vector>
#include <deque>

class RootTask : public tbb::task {
 public:
    RootTask() {}
    tbb::task* execute();
};

class RadixTask : public tbb::task {
 public:
    int max_value;
    const int size;
    const int* start;
    std::vector<int>* res;
    RadixTask(const int* start_, const int size_,  std::vector<int>* res_, int max_value_) :
      max_value(max_value_), size(size_), start(start_), res(res_) {}
    tbb::task* execute();
};

std::vector<int> getRandomVector(int size);

int getMax(std::vector<int> input_vec, int size);

void getMergedVector(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>* res);

std::vector<int> countSort(const std::vector<int>& input_vec, int size, int place);

std::vector<int> radixSort(const std::vector<int>& input_vec, int size);

std::vector<int> radixSortParallel(const std::vector<int>& input_vec, int size);

#endif  // MODULES_TASK_3_KIM_N_RADIX_SORT_RADIX_SORT_H_
