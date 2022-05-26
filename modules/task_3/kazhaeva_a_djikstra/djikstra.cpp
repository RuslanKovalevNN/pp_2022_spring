// Copyright 2022 Kazhaeva Anastasia
#include "../../../modules/task_3/kazhaeva_a_djikstra/djikstra.h"

#include <tbb/tbb.h>
#include <algorithm>
#include <random>
#include <utility>
#include <vector>

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

std::vector<std::vector<int>> parallelDjikstra(int numThreads,
    const std::vector<std::vector<int>>& matrix) {
    int const size = static_cast<int>(matrix.size());
    int grainSize = size / numThreads;
    std::vector<std::vector<int>> result(size,
        std::vector<int>(size, 0));

    tbb::task_scheduler_init init(numThreads);
    tbb::parallel_for(tbb::blocked_range<int>(0, size, grainSize),
        [&](const tbb::blocked_range<int>& r) {
            for (int top = r.begin(); top < r.end(); ++top) {
                auto tmp = djikstra(top, matrix);
                for (int i = 0; i < size; ++i) {
                    result[top][i] = tmp[i];
                }
            }
        });
    return result;
}
