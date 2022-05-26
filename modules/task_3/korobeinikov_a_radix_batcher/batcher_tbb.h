// Copyright 2022 Korobeinikov Alexandr

#ifndef MODULES_TASK_3_KOROBEINIKOV_A_RADIX_BATCHER_BATCHER_TBB_H_
#define MODULES_TASK_3_KOROBEINIKOV_A_RADIX_BATCHER_BATCHER_TBB_H_

#include <tbb/task.h>
#include <tbb/blocked_range.h>
#include <vector>

class EvenSplitter :public tbb::task {
 private:
    double* mas;
    double* tmp;
    int size1;
    int size2;
 public:
    EvenSplitter(double* _mas, double* _tmp, int _size1,
        int _size2) : mas(_mas), tmp(_tmp),
        size1(_size1), size2(_size2)
    {}    tbb::task* execute();
};

class OddSplitter :public tbb::task {
 private:
    double* mas;
    double* tmp;
    int size1;
    int size2;
 public:
    OddSplitter(double* _mas, double* _tmp, int _size1,
        int _size2) : mas(_mas), tmp(_tmp),
        size1(_size1), size2(_size2)
    {}    tbb::task* execute();
};

class SimpleComparator {
 private:
    double* mas;
 public:
    explicit SimpleComparator(double* _mas) : mas(_mas)
    {}    void operator()(const tbb::blocked_range<int>& r) const;
};

class RadixParallelSorter :public tbb::task {
 private:
    double* mas;
    double* tmp;
    int size;
    int portion;
 public:
    RadixParallelSorter(double* _mas, double* _tmp, int _size,
        int _portion) : mas(_mas), tmp(_tmp),
        size(_size), portion(_portion)
    {}
    tbb::task* execute();
};

void TbbParallelSort(double* inp, int size,
    int nThreads);

std::vector<double> CountingSort(std::vector<double> vec, size_t num_byte);

void RadixSort(double* vec, int left, int right);

void getRandomArray(double* arr, int size);

bool checkCorrectnessOfSort(double* arr, int size);

#endif  // MODULES_TASK_3_KOROBEINIKOV_A_RADIX_BATCHER_BATCHER_TBB_H_
