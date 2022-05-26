// Copyright 2022 Remizova Antonina
#include "../../../modules/task_3/remizova_a_hoar_batcher/hoar_batcher.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

std::vector<double> getRandVector(int size) {
    if (size < 0)
        throw "negative vector size";

    std::mt19937 gen((unsigned int)time(0));
    std::uniform_int_distribution <int> dist(-100000, 100000);
    std::vector <double> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = dist(gen);
    }
    return vec;
}

bool isSortCorrectly(const std::vector <double>& vec) {
    bool sort = std::is_sorted(vec.begin(), vec.end());
    return sort;
}

void hoarSort(std::vector <double>* vec, int l_ind, int r_ind) {
    if (l_ind >= r_ind)
        return;

    int l = l_ind, r = r_ind;
    double pvt = vec->at((l + r) / 2);

    while (l <= r) {
        while (vec->at(l) < pvt)
            l++;
        while (vec->at(r) > pvt)
            r--;
        if (l <= r) {
            std::swap(vec->at(l), vec->at(r));
            l++;
            r--;
        }
    }

    if (l < r_ind)
        hoarSort(vec, l, r_ind);
    if (l_ind < r)
        hoarSort(vec, l_ind, r);

    return;
}

std::vector<double> evenBatcherSort(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    const int size_v1 = vec1.size();
    const int size_v2 = vec2.size();
    int i = 0, j = 0, k = 0, l = 0;
    const int size_eres = vec1.size() / 2 + vec2.size() / 2 + vec1.size() % 2 + vec2.size() % 2;
    std::vector<double> eres(size_eres);
    for (; i < size_v1 && j < size_v2; k++) {
        if (vec1[i] <= vec2[j]) {
            eres[k] = vec1[i];
            i += 2;
        } else {
            eres[k] = vec2[j];
            j += 2;
        }
    }
    if (i >= size_v1) {
        for (l = j; l < size_v2; l += 2, k++)
            eres[k] = vec2[l];
    } else {
        for (l = i; l < size_v1; l += 2, k++)
            eres[k] = vec1[l];
    }

    return eres;
}

std::vector<double> oddBatcherSort(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    const int size_v1 = vec1.size();
    const int size_v2 = vec2.size();
    int i = 1, j = 1, k = 0, l = 0;
    const int size_ores = vec1.size() / 2 + vec2.size() / 2;
    std::vector<double> ores(size_ores);
    for (; i < size_v1 && j < size_v2; k++) {
        if (vec1[i] <= vec2[j]) {
            ores[k] = vec1[i];
            i += 2;
        } else {
            ores[k] = vec2[j];
            j += 2;
        }
    }
    if (i >= size_v1) {
        for (l = j; l < size_v2; l += 2, k++)
            ores[k] = vec2[l];
    } else {
        for (l = i; l < size_v1; l += 2, k++)
            ores[k] = vec1[l];
    }

    return ores;
}

std::vector<double> oddEvenBatcherSort(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    int size_oeres = vec1.size() + vec2.size();
    std::vector<double> oeres(size_oeres);

    for (size_t i = 0; i < vec1.size(); i++)
        oeres[i] = vec1[i];

    for (int i = vec1.size(), j = 0; i < size_oeres; i++, j++)
        oeres[i] = vec2[j];

    return oeres;
}

std::vector<double> mergeBatcherSeq(const std::vector<double>& vec, int middle) {
    int size_res = vec.size();
    std::vector <double> res(size_res);
    int buf;

    for (int i = 0; i < size_res - middle; i++) {
        res[i * 2] = vec[i];
        res[i * 2 + 1] = vec[middle + i];
    }

    if (middle * 2 - size_res >= 1)
        res[size_res - 1] = vec[middle - 1];

    if (middle * 2 - size_res == 2)
        res[size_res - 2] = vec[middle - 2];

    for (int i = 1; i < size_res; i++) {
        if (res[i] < res[i - 1]) {
            buf = res[i - 1];
            res[i - 1] = res[i];
            res[i] = buf;
        }
    }

    return res;
}

std::vector<double> mergeBatcherPar(const std::vector<double>& vec, int middle) {
    int size_res = vec.size();
    std::vector <double> res(size_res);
    int buf;
    tbb::parallel_for(tbb::blocked_range<int>(0, static_cast<int>(res.size() - middle)),
        [&](tbb::blocked_range<int> r) {
            for (int i = r.begin(); i < r.end(); ++i) {
                res[i * 2] = vec[i];
                res[i * 2 + 1] = vec[middle + i];
            }
        });

    if (middle * 2 - size_res >= 1)
        res[size_res - 1] = vec[middle - 1];

    if (middle * 2 - size_res == 2)
        res[size_res - 2] = vec[middle - 2];

    for (int i = 1; i < size_res; i++) {
        if (res[i] < res[i - 1]) {
            buf = res[i - 1];
            res[i - 1] = res[i];
            res[i] = buf;
        }
    }

    return res;
}

std::vector<double> hoarBatcherSeq(const std::vector<double>& vec, int size) {
    int k = size / 2;
    std::vector<double> vec1;
    vec1.assign(vec.begin(), vec.end() - k);
    std::vector<double> vec2;
    hoarSort(&vec1, 0, vec1.size() - 1);
    vec2.assign(vec.end() - k, vec.end());
    hoarSort(&vec2, 0, vec2.size() - 1);
    std::vector<double>even = evenBatcherSort(vec1, vec2);
    std::vector<double>odd = oddBatcherSort(vec1, vec2);
    std::vector<double>res_oe = oddEvenBatcherSort(even, odd);
    std::vector<double>sort_res = mergeBatcherSeq(res_oe, even.size());
    return sort_res;
}

std::vector<double> hoarBatcherPar(const std::vector<double>& vec, int size) {
    int k = size / 2;
    std::vector<double> vec1;
    vec1.assign(vec.begin(), vec.end() - k);
    std::vector<double> vec2;
    vec2.assign(vec.end() - k, vec.end());
    std::vector<double>even;
    std::vector<double>odd;

    tbb::parallel_for(tbb::blocked_range<int>(0, 2),
        [&](tbb::blocked_range<int> r) {
            for (int i = r.begin(); i < r.end(); ++i) {
                if (i == 0)
                    hoarSort(&vec1, 0, vec1.size() - 1);
                else
                    hoarSort(&vec2, 0, vec2.size() - 1);
            }
        });

    tbb::parallel_for(tbb::blocked_range<int>(0, 2),
        [&](tbb::blocked_range<int> r) {
            for (int i = r.begin(); i < r.end(); ++i) {
                if (i == 0)
                    even = evenBatcherSort(vec1, vec2);
                else
                    odd = oddBatcherSort(vec1, vec2);
            }
        });

    std::vector<double>res_oe = oddEvenBatcherSort(even, odd);
    std::vector<double>sort_res = mergeBatcherPar(res_oe, even.size());
    return sort_res;
}
