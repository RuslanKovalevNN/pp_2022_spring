// Copyright 2022 Kovalev Ruslan

#include <tbb/tbb.h>
#include <random>
#include <vector>
#include <iostream>

#include "../../../modules/task_3/kovalev_r_odd_even_sort_tbb/odd_even_sort_tbb.h"


void copy_vectors(std::vector<int>* arr_1, std::vector<int>* arr_2, int sz) {
  for (int i = 0; i < sz; i++) {
    arr_2->at(i) = arr_1->at(i);
  }
}

void vec_gen(std::vector<int>* vec, int len) {
  std::random_device dev;
  std::mt19937 gen(dev());
  for (int i = 0; i < len; i++) {
    vec->at(i) = gen() % 10000;
  }
}

bool check(std::vector<int>* arr_1, std::vector<int>* arr_2, int sz) {
  for (int i = 0; i < sz; i++) {
    if (arr_1->at(i) != arr_2->at(i)) {
      return false;
    }
  }
  return true;
}

void Exchange(int* first, int* second) {
  if (first > second) {
    std::swap(first, second);
  }
}

void Odd_Even_Split(std::vector<int>* arr, std::vector<int>* odd, std::vector<int>* even,
                    int size) {
  for (int i = 0; i < size / 2; i++) {
    odd->at(i) = arr->at(2 * i + 1);
    even->at(i) = arr->at(2 * i);
  }
}

void Merge(std::vector<int>* res, std::vector<int>* arr_1, std::vector<int>* arr_2,
                       int sz_1, int sz_2) {
  int i = 0;
  int j = 0;
  int k = 0;
  while (i < sz_1 && j < sz_2) {
    if (arr_1->at(i) < arr_2->at(j))
      res->at(k++) = arr_1->at(i++);
    else
      res->at(k++) = arr_2->at(j++);
  }
  while (i < sz_1) res->at(k++) = arr_1->at(i++);
  while (j < sz_2) res->at(k++) = arr_2->at(j++);
}


void Odd_Even_Split_Parallel(std::vector<int>* arr, std::vector<int>* odd,
                               std::vector<int>* even, int size) {
  tbb::parallel_for(tbb::blocked_range<int>(0, size/2),
                    [&](const tbb::blocked_range<int>& range) {
                      for (int i = range.begin(); i != range.end(); i++) {
                        odd->at(i) = arr->at(2 * i + 1);
                        even->at(i) = arr->at(2 * i);
                      }
  });
}

void Odd_Even_Join(std::vector<int>* arr, std::vector<int>* odd, std::vector<int>* even,
                   int size) {
  for (int i = 0; i < size / 2; i++) {
    arr->at(2 * i + 1) = odd->at(i);
    arr->at(2 * i) = even->at(i);
  }
}

void Odd_Even_Join_Parallel(std::vector<int>* arr, std::vector<int>* odd, std::vector<int>* even,
                   int size) {
  tbb::parallel_for(tbb::blocked_range<int>(0, size / 2),
                    [&](const tbb::blocked_range<int>& range) {
                      for (int i = range.begin(); i != range.end(); i++) {
                        arr->at(2*i+1) = odd->at(i);
                        arr->at(2*i) = even->at(i);
                      }
                    });
}

int getMax(std::vector<int>* arr, int sz) {
  int max = arr->at(0);
  for (int i = 0; i < sz; i++) {
    if (arr->at(i) > max) max = arr->at(i);
  }
  return max;
}

int ParalleGetMax(std::vector<int>* arr, int sz) {
  int max = arr->at(0);
  tbb::parallel_for(tbb::blocked_range<int>(0, sz),
                    [&](const tbb::blocked_range<int>& range) {
                      for (int i = range.begin(); i != range.end(); i++) {
                        if (arr->at(i) > max) max = arr->at(i);
                      }
  });
  return max;
}

void countingSort(std::vector<int>* arr, int size, int place) {
  const int max = 10;
  std::vector<int> output(size, 0);
  std::vector<int> count(max, 0);
  for (int i = 0; i < size; i++) count[(arr->at(i) / place) % 10]++;
  for (int j = 1; j < max; j++) count[j] += count[j - 1];
  for (int i = size - 1; i >= 0; i--) {
    output[count[(arr->at(i) / place) % 10] - 1] = arr->at(i);
    count[(arr->at(i) / place) % 10]--;
  }
  for (int i = 0; i < size; i++) arr->at(i) = output[i];
}

void countingSortParallel(std::vector<int>* arr, int size, int place) {
  const int max = 10;
  std::vector<int> output(size, 0);
  std::vector<int> count(max, 0);

  tbb::mutex pushMutex_1;
  tbb::parallel_for(tbb::blocked_range<int>(0, size, 10),
                    [&](const tbb::blocked_range<int>& range) {
                      for (int i = range.begin(); i < range.end(); i++) {
                        pushMutex_1.lock();
                        count[(arr->at(i) / place) % 10]++;
                        pushMutex_1.unlock();
                      }
    });

  tbb::mutex pushMutex_2;
  tbb::parallel_for(tbb::blocked_range<int>(1, max, 10),
                    [&](const tbb::blocked_range<int>& range) {
                      for (int i = range.begin(); i < range.end(); i++) {
                        pushMutex_2.lock();
                        count[i] = count[i] + count[i - 1];
                        pushMutex_2.unlock();
                      }
                    });

  for (int i = size - 1; i >= 0; i--) {
    output[count[(arr->at(i) / place) % 10] - 1] = arr->at(i);
    count[(arr->at(i) / place) % 10]--;
  }
  tbb::parallel_for(tbb::blocked_range<int>(0, size),
                    [&](const tbb::blocked_range<int>& range) {
                      for (int i = range.begin(); i < range.end(); i++) {
                        arr->at(i) = output[i];
                      }
    });
}

void Odd_Even_Merge(std::vector<int>* arr, int len) {
  int odd_len = len / 2;
  int even_len = len - odd_len;
  std::vector<int> Odd(odd_len);
  std::vector<int> Even(even_len);
  Odd_Even_Split(arr, &Odd, &Even, len);
  getSequantialSort(&Odd, odd_len);
  getSequantialSort(&Even, even_len);
  Odd_Even_Join(arr, &Odd, &Even, len);
  Merge(arr, &Odd, &Even, odd_len, even_len);
  for (int i = 1; i < len - 1; i += 2) {
    if (arr->at(i) > arr->at(i + 1)) {
      swap(arr[i], arr[i + 1]);
    }
  }
}

void getSortParallel(std::vector<int>* arr, int sz) {
  int max = ParalleGetMax(arr, sz);
  for (int place = 1; max / place > 0; place *= 10)
    countingSortParallel(arr, sz, place);
}

void Odd_Even_Merge_Parallel(std::vector<int>* arr, int len) {
  int odd_len = len / 2;
  int even_len = len - odd_len;

  std::vector<int> Odd(odd_len);
  std::vector<int> Even(even_len);

  Odd_Even_Split_Parallel(arr, &Odd, &Even, len);
  getSortParallel(&Odd, odd_len);
  getSortParallel(&Even, even_len);
  Merge(arr, &Odd, &Even, odd_len, even_len);

  tbb::parallel_for(tbb::blocked_range<int>(0 , len-1, 2),
                    [&](const tbb::blocked_range<int>& range) {
                      for (int i = range.begin(); i != range.end(); i++) {
                        if (arr->at(i) > arr->at(i + 1)) {
                          std::swap(arr->at(i), arr->at(i + 1));
                        }
                      }
    });
}


void getSequantialSort(std::vector<int>* arr, int sz) {
  int max = getMax(arr, sz);
  for (int place = 1; max / place > 0; place *= 10)
    countingSort(arr, sz, place);
}
