// Copyright 2022 Kuklin Andrey
#ifndef MODULES_TASK_4_KUKLIN_A_BATCHER_MERGESORT_BATCHER_MERGESORT_H_
#define MODULES_TASK_4_KUKLIN_A_BATCHER_MERGESORT_BATCHER_MERGESORT_H_

#include <vector>

using vector_d = std::vector<double>;

std::vector<double> getRandVec(size_t vec_size, double lower_bound,
                               double upper_bound);
void genDigitCounters(vector_d* source_vec, size_t elem_num);
void radixPass(vector_d* source_vec,
               const std::vector<vector_d>& digitCounters);
void floatRadixSort(vector_d* source_vec);
void evenSplitter(vector_d* res_vec, const vector_d& first_vec,
                  const vector_d& second_vec);
void oddSplitter(vector_d* res_vec, const vector_d& first_vec,
                 const vector_d& second_vec);
void batcherComparator(vector_d* res_vec);
vector_d batcherMerge(const vector_d& first_vec, const vector_d& second_vec);
void floatRadixSortParallel(vector_d* source_vec);

#endif  // MODULES_TASK_4_KUKLIN_A_BATCHER_MERGESORT_BATCHER_MERGESORT_H_
