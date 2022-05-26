// Copyright 2022 Belyaev Ilya
#include <tbb/tbb.h>
#include <random>
#include <climits>
#include <functional>
#include <algorithm>
#include <stdexcept>

#include "../../../modules/task_3/belyaev_i_hoare_sort_simple_tbb/hoare_sort_tbb.h"

int partition(std::vector<int> *v, int low, int high) {
    int pivot = v->at(high);
    int smallerElementIndex = low - 1;

    for (int i = low; i < high; ++i) {
        if (v->at(i) < pivot) {
            std::swap(v->at(++smallerElementIndex), v->at(i));
        }
    }

    std::swap(v->at(smallerElementIndex + 1), v->at(high));

    return smallerElementIndex + 1;
}

void hoareSort(std::vector<int> *v, int low, int high) {
    if (low < high) {
        int partitionIndex = partition(v, low, high);
        hoareSort(v, low, partitionIndex - 1);
        hoareSort(v, partitionIndex + 1, high);
    }
}

std::vector<int> merge(const std::vector<int> &vec1,
                       const std::vector<int> &vec2) {
    std::vector<int> merged(vec1.size() + vec2.size());
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < static_cast<int>(vec1.size())
        && j < static_cast<int>(vec2.size())) {
        if (vec1[i] < vec2[j]) {
            merged[k] = vec1[i];
            i++;
        } else {
            merged[k] = vec2[j];
            j++;
        }
        k++;
    }
    while (i < static_cast<int>(vec1.size())) {
        merged[k] = vec1[i];
        k++;
        i++;
    }
    while (j < static_cast<int>(vec2.size())) {
        merged[k] = vec2[j];
        k++;
        j++;
    }

    return merged;
}

void runHoareSort(std::vector<int> *v, int numThreads) {
    if (static_cast<int>(v->size()) < numThreads) {
        hoareSort(v, 0, v->size() - 1);
        return;
    }
    if (v->size() == 1) {
        return;
    }
    tbb::task_scheduler_init init(numThreads);

    int elementsPerSegment = v->size() / numThreads;

    std::vector<std::vector<int>> segments;
    std::vector<int> segment;

    for (int i = 0; i < numThreads; ++i) {
        if (i == numThreads - 1) {
            segment.insert(segment.end(),
                           v->begin() + i * elementsPerSegment,
                           v->end());
        } else {
            segment.insert(segment.end(),
                           v->begin() + i * elementsPerSegment,
                           v->begin() + (i + 1) * elementsPerSegment);
        }
        segments.push_back(segment);
        segment.clear();
    }

    tbb::parallel_for(
        tbb::blocked_range<size_t>(0, segments.size(), 1),
        [&segments](const tbb::blocked_range<size_t> &range) {
            for (size_t i = range.begin(); i != range.end(); ++i) {
                hoareSort(&segments[i], 0, segments[i].size() - 1);
            }
        },
        tbb::simple_partitioner());

    *v = segments[0];
    for (size_t i = 1; i < segments.size(); ++i) {
        *v = merge(*v, segments[i]);
    }
}

std::vector<int> getRandomVector(int size, int type) {
    std::vector<int> newVec(size);

    std::random_device dev;
    std::mt19937 randomGenerator(dev());

    if (type == 1) {
        std::uniform_int_distribution<int> randomValue(1, INT_MAX);

        for (int &item : newVec) {
            item = randomValue(randomGenerator);
        }
    } else if (type >= 0 && type <= 3) {
        std::uniform_int_distribution<int> randomValue(INT_MIN, INT_MAX);

        for (int &item : newVec) {
            item = randomValue(randomGenerator);
        }

        if (type == 2) {
            sort(newVec.begin(), newVec.end());
        } else if (type == 3) {
            sort(newVec.begin(), newVec.end(), std::greater<int>());
        }
    } else {
        throw std::invalid_argument("not vector");
    }

    return newVec;
}
