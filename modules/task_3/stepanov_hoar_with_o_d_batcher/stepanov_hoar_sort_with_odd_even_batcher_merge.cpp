// Copyright 2022 George Amberson
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <list>
#include "../../../modules/task_3/stepanov_hoar_with_o_d_batcher/stepanov_hoar_sort_with_odd_even_batcher_merge.h"

std::vector<float>* create_random_vector(int size_n) {
    std::vector<float>* res = new std::vector<float>(size_n);
    std::random_device dev;
    std::mt19937 gen(dev());
    for (int i = 0; i < size_n; ++i) {
        (*res)[i] = static_cast<float>(gen()) / gen();
    }
    return res;
}

std::vector<float>* odd_batcher(std::vector<float>* part1,
    const std::vector<float>* part2, std::vector<float>* vec) {
    int size1 = part1->size();
    int i1 = 1;
    int size2 = part2->size();
    int i2 = 1;
    int i = 0;
    int size_result = size1 / 2 + size2 / 2;
    std::vector <float>* mass_result = new std::vector<float>(size_result);

    while ((i1 < size1) && (i2 < size2)) {
        if ((*part1)[i1] <= (*part2)[i2]) {
            (*mass_result)[i] = (*part1)[i1];
            i1 = i1 + 2;
        } else {
            (*mass_result)[i] = (*part2)[i2];
            i2 = i2 + 2;
        }
        i = i + 1;
    }
    if (i1 >= size1) {
        for (int j = i2; j < size2; j = j + 2) {
            (*mass_result)[i] = (*part2)[j];
            i = i + 1;
        }
    }
    if (i2 >= size2) {
        for (int j = i1; j < size1; j = j + 2) {
            (*mass_result)[i] = (*part1)[j];
            i = i + 1;
        }
    }
    return mass_result;
}

std::vector<float>* even_batcher(std::vector<float>* part1,
    const std::vector<float>* part2, std::vector<float>* vec) {
    int size1 = part1->size();
    int i1 = 0;
    int size2 = part2->size();
    int i2 = 0;
    int i = 0;
    int size_result = size1 / 2 + size2 / 2 + size1 % 2 + size2 % 2;
    std::vector <float>* mass_result = new std::vector<float>(size_result);

    while ((i1 < size1) && (i2 < size2)) {
        if ((*part1)[i1] <= (*part2)[i2]) {
            (*mass_result)[i] = (*part1)[i1];
            i1 = i1 + 2;
        } else {
            (*mass_result)[i] = (*part2)[i2];
            i2 = i2 + 2;
        }
        i = i + 1;
    }
    if (i1 >= size1) {
        for (int j = i2; j < size2; j = j + 2) {
            (*mass_result)[i] = (*part2)[j];
            i = i + 1;
        }
    }
    if (i2 >= size2) {
        for (int j = i1; j < size1; j = j + 2) {
            (*mass_result)[i] = (*part1)[j];
            i = i + 1;
        }
    }
    return mass_result;
}
void odd_even_batcher_merge(std::vector<float>* part1,
    const std::vector<float>* part2,
    std::vector<float>* vec) {
    int size1 = part1->size();
    int i1 = 0;
    int size2 = part2->size();
    int i2 = 0;
    int i = 0;
    float temp;
    (*vec) = std::vector<float>(size1 + size2);
    int size_result = part1->size() + part2->size();
    while ((i1 < size1) && (i2 < size2)) {
        (*vec)[i] = (*part1)[i1];
        (*vec)[i + 1] = (*part2)[i2];
        i1 = i1 + 1;
        i2 = i2 + 1;
        i = i + 2;
    }
    if ((i1 < size1) && (i2 >= size2)) {
        for (int a = i; a < size_result; a++) {
            (*vec)[a] = (*part1)[i1];
            i1 = i1 + 1;
        }
    } else {
        for (int a = i; a < size_result; a++) {
            (*vec)[a] = (*part2)[i2];
            i2 = i2 + 1;
        }
    }
    for (int i = 1; i < size_result; i++) {
        if ((*vec)[i] < (*vec)[i - 1]) {
            temp = (*vec)[i];
            (*vec)[i] = (*vec)[i - 1];
            (*vec)[i - 1] = temp;
        }
    }
}

void hoar_sort_for_parts(std::vector<float>* vec, int first, int last) {
    int i = first, j = last;
    float tmp, x = (*vec)[(first + last) / 2];

    do {
        while ((*vec)[i] < x)
            i++;
        while ((*vec)[j] > x)
            j--;
        if (i <= j) {
            if (i < j) {
                tmp = (*vec)[i];
                (*vec)[i] = (*vec)[j];
                (*vec)[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        hoar_sort_for_parts(vec, i, last);
    if (first < j)
        hoar_sort_for_parts(vec, first, j);
}
void batch_merge(std::vector<float>* part1,
 const std::vector<float>* part2, std::vector<float>* vec) {
    std::vector<float>* even_part = even_batcher(part1, part2, vec);
    std::vector<float>* odd_part = odd_batcher(part1, part2, vec);
    odd_even_batcher_merge(even_part, odd_part, vec);
    delete even_part;
    delete odd_part;
}


void hoar_sort_with_batch_merge(std::vector<float>* vec) {
    int middle = vec->size() / 2;
    std::vector<float> p1(vec->begin(), vec->begin() + middle);
    std::vector<float>p2(vec->begin() + middle, vec->end());
    hoar_sort_for_parts(&p1, 0, p1.size() - 1);
    hoar_sort_for_parts(&p2, 0, p2.size() - 1);
    batch_merge(&p1, &p2, vec);
}

struct Functor {
    std::vector<float>* arr;
    std::vector<float> vals;
    explicit Functor(std::vector<float>* _arr) :arr(_arr) {}
    Functor(const Functor& f, tbb::split):arr(f.arr) {}
    void operator()(const tbb::blocked_range<int> &r) {
        int begin = r.begin();
        int end = r.end();
        for (int i = begin; i < end; i++) {
            vals.push_back((*arr)[i]);
        }
        hoar_sort_for_parts(&vals, 0, vals.size()-1);
    }
    void join(const Functor& f) {
        batch_merge(&vals, &(f.vals), &vals);
    }
};




void hoar_sort_with_batch_merge_tbb(std::vector<float>* vec) {
    Functor f(vec);
    tbb::parallel_reduce(
    tbb::blocked_range<int>(0, vec->size(), vec->size() / 4), f);
    (*vec) = f.vals;
}
