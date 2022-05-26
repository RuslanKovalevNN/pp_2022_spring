// Copyright 2022 Vanyushkov Maxim
#include "../../../modules/task_3/vanyushkov_m_shell_sort_odd_even_merge/sort.h"
#include <random>

typedef std::vector<int>::size_type vec_size_t;

std::vector<int> getRandomVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = gen() % size;
    }
    return vec;
}

// Shell sort with Hibbard's step
// https://www.cyberforum.ru/cpp-beginners/thread2430694.html
void ShellSortSequantial(std::vector<int>* vec) {
    vec_size_t size = vec->size();
    vec_size_t k = 1;
    while ((k << 1 | 1) < size) {  // 2 * k + 1 < size
        k = (k << 1) | 1;  // k = 2 * k + 1
    }
    for (; k > 0; k >>= 1) {  // k /= 2
        for (vec_size_t i = k; i < size; i++) {
            int t = (*vec)[i];
            vec_size_t j = i;
            for (; (j >= k) && (t < (*vec)[j - k]); j -= k) {
                (*vec)[j] = (*vec)[j - k];
            }
            (*vec)[j] = t;
        }
    }
}

std::vector<int> merge(const std::vector<int>& vec_1,
                       const std::vector<int>& vec_2) {
    std::vector<int> vec_res(vec_1.size() + vec_2.size());
    size_t i = 0, j = 0, k = 0;
    while (i < vec_1.size() && j < vec_2.size()) {
        vec_res[k++] = (vec_1[i] < vec_2[j] ? vec_1[i++] : vec_2[j++]);
    }
    while (i < vec_1.size()) {
        vec_res[k++] = vec_1[i++];
    }
    while (j < vec_2.size()) {
        vec_res[k++] = vec_2[j++];
    }
    return vec_res;
}

void ShellSortParallel(std::vector<int>* vec) {
    std::vector<std::vector<int>> proc_res;
    tbb::mutex push_mutex;
    tbb::parallel_for(
        tbb::blocked_range<std::vector<int>::iterator>(
            vec->begin(), vec->end(), vec->size() / 3),
        [&](tbb::blocked_range<std::vector<int>::iterator> iter) {
            std::vector<int> temp_vec = { iter.begin(), iter.end() };
            ShellSortSequantial(&temp_vec);
            push_mutex.lock();
            proc_res.push_back(std::move(temp_vec));
            push_mutex.unlock();
        });
    *vec = proc_res[0];
    for (vec_size_t i = 1; i < proc_res.size(); i++) {
        *vec = merge(*vec, proc_res[i]);
    }
}

bool checkSort(const std::vector<int>& vec) {
    vec_size_t size = vec.size();
    for (vec_size_t i = 1; i < size; i++) {
        if (vec[i - 1] > vec[i]) {
            return false;
        }
    }
    return true;
}
