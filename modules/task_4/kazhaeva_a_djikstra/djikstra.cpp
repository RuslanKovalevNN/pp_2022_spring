// Copyright 2022 Kazhaeva Anastasia
#include "../../../modules/task_4/kazhaeva_a_djikstra/djikstra.h"

#include <algorithm>
#include <random>
#include <utility>
#include <vector>

#include "../../../3rdparty/unapproved/unapproved.h"


std::vector<std::vector<int>> randomVectorDjikstra(const int size) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
    std::random_device dev;
    std::mt19937 gen(dev());
    for (int i = 0; i < size; ++i) {
        matrix[i][i] = 0;
        for (int j = i + 1; j < size; ++j) {
            matrix[i][j] = gen() % 100;
            matrix[j][i] = matrix[i][j];
        }
    }
    return matrix;
}

std::vector<int> djikstra(const int start,
const std::vector<std::vector<int>>& matrix) {
    const int INF = 1000000000;
    int const size = static_cast<int>(matrix.size());
    std::vector<int> d(size, INF);
    std::vector<int> v(size, 1);
    int temp, minindex, min;
    d[start] = 0;
    do {
        minindex = INF;
        min = INF;
        for (int i = 0; i < size; i++) {
            if ((v[i] == 1) && (d[i] < min)) {
                min = d[i];
                minindex = i;
            }
        }
        if (minindex != INF) {
            for (int i = 0; i < size; i++) {
                if (matrix[minindex][i] > 0) {
                    temp = min + matrix[minindex][i];
                    if (temp < d[i]) {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < INF);


    return d;
}

std::vector<std::vector<int>> sequentialDjikstra(
const std::vector<std::vector<int>>& matrix) {
    int const size = static_cast<int>(matrix.size());
    std::vector<std::vector<int>> result(size,
        std::vector<int>(size, 0));
    std::vector<int> tmp(size);

    for (int count = 0; count < size; ++count) {
        tmp = djikstra(count, matrix);
        for (int i = 0; i < size; ++i) {
            result[count][i] = tmp[i];
        }
    }
    return result;
}

void ThreadIteration(const std::vector<std::vector<int>>& matrix,
    const int start, const int numT,
    std::vector<std::vector<int>>* result) {
    int const size = static_cast<int>(matrix.size());
    for (int i = start; i < start + numT; ++i) {
        auto tmp = djikstra(i, matrix);
        for (int j = 0; j < size; ++j) {
            (*result)[i][j]= tmp[j];
        }
    }
}

std::vector<std::vector<int>> parallelDjikstra(int numThreads,
const std::vector<std::vector<int>>& matrix) {
    std::vector<std::thread> threadVector;
    int count = 0;
    int const size = static_cast<int>(matrix.size());
    const int numT = size / numThreads;
    std::vector<std::vector<int>> result1(size,
        std::vector<int>(size, 0));
    int ost = size % numThreads;
    for (int i = 0; i < numThreads; i++) {
        if (ost > 0) {
            threadVector.push_back(
                std::thread(ThreadIteration, matrix,
count, numT + 1, &result1));
            count += numT + 1;
            ost--;
        } else {
            threadVector.push_back(
                std::thread(ThreadIteration, matrix, count, numT, &result1));
            count += numT;
        }
    }
    for (int i = 0; i < numThreads; ++i) {
        threadVector[i].join();
    }

    return result1;
}
