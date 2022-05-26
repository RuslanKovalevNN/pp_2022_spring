// Copyright 2022 Vanyushkov Maxim
#include "../../../modules/task_4/vanyushkov_m_shell_sort_odd_even_merge/sort.h"
#include <random>
// #include "../../../3rdparty/unapproved/unapproved.h"

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
    unsigned PROC_SIZE = 4;
    unsigned delta = vec->size() / PROC_SIZE;
    std::vector<std::vector<int>> proc_res(PROC_SIZE);
    std::thread* t = new std::thread[PROC_SIZE];
    for (unsigned rank = 0; rank < PROC_SIZE; rank++) {
        auto end = vec->begin() + (rank + 1) * delta;
        if (PROC_SIZE - 1 == rank) {
            end = vec->end();
        }
        proc_res[rank] = { vec->begin() + rank * delta, end };
        t[rank] = std::thread(ShellSortSequantial, &proc_res[rank]);
    }
    for (unsigned rank = 0; rank < PROC_SIZE; rank++) {
        // if (t[rank].joinable()) t[rank].join();
        t[rank].join();
    }
    *vec = proc_res[0];
    for (vec_size_t i = 1; i < proc_res.size(); i++) {
        *vec = merge(*vec, proc_res[i]);
    }
    delete[] t;
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
