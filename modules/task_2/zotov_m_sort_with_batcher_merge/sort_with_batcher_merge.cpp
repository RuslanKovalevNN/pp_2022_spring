// Copyright 2022 Zotov Maxim
#include <omp.h>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include "../../../modules/task_2/zotov_m_sort_with_batcher_merge/sort_with_batcher_merge.h"

const int MAX = 5000;

std::vector<int> getRandomVector(int size) {
    std::mt19937 generate;
    generate.seed(time(0));
    std::uniform_real_distribution<> uid(-MAX, MAX);
    std::vector<int> tmp;
    for (int i = 0; i < size; i++) {
        tmp.push_back(uid(generate));
    }
    return tmp;
}

int getMaxDigit(const int max) {
    int tmp = 0;
    int i = 0;
    for (i = 1; i < 10; i++) {
        tmp = max / static_cast<int>(pow(10, i));
        if (tmp == 0) {
            break;
        }
    }
    return i;
}

void  radixSort(std::vector<int>* main_data, int size, int offset) {
    std::vector<int> sorted_data[19];
    int koef = 0;
    int max_digit = getMaxDigit(MAX);
    while (koef < max_digit) {
        for (int i = offset; i < offset + size; i++) {
            int digit = (*main_data)[i] / pow(10, koef);
            digit = digit % 10;
            sorted_data[digit + 9].push_back((*main_data)[i]);
        }

        int iter = 0;
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < static_cast<int>(sorted_data[i].size()); j++) {
                (*main_data)[offset + iter] = sorted_data[i][j];
                iter++;
            }
            sorted_data[i].clear();
        }
        koef++;
    }
}

int getNumberOfIterations(int tN) {
    int k = 1;
    while (tN > std::pow(2, k)) {
        k++;
    }
    return k;
}

void splitData(std::vector<int>* data, std::vector<int>* first, int f, int f_displ, int s, int s_displ) {
    while (f < f_displ && s < s_displ) {
        if ((*data)[f] < (*data)[s]) {
            first->push_back((*data)[f]);
            f += 2;
        } else {
            first->push_back((*data)[s]);
            s += 2;
        }
    }

    if (f >= f_displ) {
        for (int j = s; j < s_displ; j += 2) {
            first->push_back((*data)[j]);
        }
    } else if (s >= s_displ) {
        for (int j = f; j < f_displ; j += 2) {
            first->push_back((*data)[j]);
        }
    }
}

void mergeData(std::vector<int>* data, std::vector<int>* first, int f, int f_displ, int s, int s_displ) {
    int i = 0;

    while (f < f_displ) {
        (*data)[f] = (*first)[i];
        f += 2;
        i++;
    }

    while (s < s_displ) {
        (*data)[s] = (*first)[i];
        s += 2;
        i++;
    }
}


void oddMerge(std::vector<int>* data, int f_size, int f_offset, int s_size, int s_offset) {
    int f = f_offset + 1, s = s_offset + 1;
    int f_displ = f_size + f_offset, s_displ = s_size + s_offset;
    std::vector<int> first;

    splitData(data, &first, f, f_displ, s, s_displ);
    mergeData(data, &first, f, f_displ, s, s_displ);
}

void evenMerge(std::vector<int>* data, int f_size, int f_offset, int s_size, int s_offset ) {
    int f = f_offset, s = s_offset;
    int f_displ = f_size + f_offset, s_displ = s_size + s_offset;
    std::vector<int> first;

    splitData(data, &first, f, f_displ, s, s_displ);
    mergeData(data, &first, f, f_displ, s, s_displ);
}

void compare(std::vector<int>* data, int size, int offset) {
    for (int i = offset; i < size + offset; i++) {
        if ((*data)[i] > (*data)[i + 1]) std::swap((*data)[i], (*data)[i + 1]);
    }
}

void parallelRadixSort(std::vector<int>* data, int size, int ThreadNum) {
    int local_size = size / ThreadNum;
    int remain = size % ThreadNum;
    std::vector<int> sendCount(ThreadNum);
    std::vector<int> displ;
    int iterator;
    int ThreadRank;
    int sum = 0;
    for (int i = 0; i < ThreadNum; i++) {
        sendCount[i] = local_size;
        if (remain > 0) {
            sendCount[i]++;
            remain--;
        }
        displ.push_back(sum);
        sum += sendCount[i];
    }

    iterator = getNumberOfIterations(ThreadNum);
    omp_set_num_threads(ThreadNum);

    #pragma omp parallel private(ThreadRank)
    {
    ThreadRank = omp_get_thread_num();
    radixSort(data, sendCount[ThreadRank], displ[ThreadRank]);
    #pragma omp barrier
    }

    for (int i = 0; i < iterator; i++) {
        omp_set_num_threads(ThreadNum);
        #pragma omp parallel private(ThreadRank)
        {
            ThreadRank = omp_get_thread_num();

            if (ThreadRank % 2 == 0 && ThreadRank + 1 < ThreadNum) {
                evenMerge(data, sendCount[ThreadRank], displ[ThreadRank],
                    sendCount[ThreadRank + 1], displ[ThreadRank + 1]);
            } else if (ThreadRank % 2 == 1) {
                oddMerge(data, sendCount[ThreadRank - 1], displ[ThreadRank - 1],
                    sendCount[ThreadRank], displ[ThreadRank]);
            }
            #pragma omp barrier
            if (ThreadRank % 2 == 0 && ThreadRank + 1 < ThreadNum) {
                compare(data, sendCount[ThreadRank], displ[ThreadRank]);
            } else if (ThreadRank % 2 == 1) {
                compare(data, sendCount[ThreadRank] - 1 , displ[ThreadRank]);
            }

            #pragma omp barrier
            #pragma omp master
            {
                for (int j = 0; j < ThreadNum - 1 ; j += 2) {
                    sendCount[j/2] = sendCount[j] + sendCount[j + 1];
                    displ[j/2] = displ[j];
                }
                if (ThreadNum % 2 == 1) {
                    sendCount[(ThreadNum - 1) / 2] = sendCount[ThreadNum - 1];
                    displ[(ThreadNum - 1) / 2] = displ[ThreadNum - 1];
                    ThreadNum = ThreadNum / 2 + 1;
                } else {
                    ThreadNum /= 2;
                }
            }
        }
    }
}
