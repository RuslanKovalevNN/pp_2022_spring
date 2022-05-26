// Copyright 2022 Ivanov Arkady
#ifndef MODULES_TASK_2_IVANOV_A_RADIX_BATCHERS_MERGESORT_OMP_RBMS_H_
#define MODULES_TASK_2_IVANOV_A_RADIX_BATCHERS_MERGESORT_OMP_RBMS_H_

#include <stdint.h>
#include <omp.h>
#include <vector>
#include <random>
#include <algorithm>
#include <utility>
#include <iostream>

// <RadixSortPart>
template <class T>
std::vector<int> createAndPrepareCounters(std::vector<T>* data, int offset, int count) {
    std::vector<int> counters(256 * sizeof(T));
    std::fill_n(counters.data(), counters.size(), 0);
    unsigned char* start = reinterpret_cast<unsigned char*>(
        data->data() + offset);
    unsigned char* stop = reinterpret_cast<unsigned char*>(
        data->data() + offset + count);

    while (start != stop) {
        for (int i = 0; i < static_cast<int>(sizeof(T)); i++) {
            counters[*start + 256 * i]++;
            start++;
        }
    }

    for (int i = 0; i < static_cast<int>(sizeof(T)); i++) {
        int sum = 0;
        if (counters[256 * i] == count)
            continue;
        for (int j = 0; j < 256; j++) {
            int tmp = counters[256 * i + j];
            counters[256 * i + j] = sum;
            sum += tmp;
        }
    }
    return counters;
}

template<class T>
void radixSort(std::vector<T>* data, int offset, int count) {
    std::vector<int> counters =
        createAndPrepareCounters(data, offset, count);

    std::vector<T> res(count);
    int j;
    for (j = 0; j < static_cast<int>(sizeof(T)); j++) {
        int* countersPtr = counters.data() + 256 * j;
        if (*countersPtr == count)
            break;

        T* dPtr, * rPtr;
        unsigned char* dataPtr;
        if (j % 2 == 0) {
            dPtr = data->data() + offset;
            dataPtr = reinterpret_cast<unsigned char*>(
                data->data() + offset);
            rPtr = res.data();
        } else {
            dPtr = res.data();
            dataPtr = reinterpret_cast<unsigned char*>(res.data());
            rPtr = data->data() + offset;
        }
        dataPtr += j;

        for (int i = 0; i < count; i++) {
            rPtr[*(countersPtr + *dataPtr)] = dPtr[i];
            *(countersPtr + *dataPtr) = *(countersPtr + *dataPtr) + 1;
            dataPtr += sizeof(T);
        }
    }

    if (j % 2 == 1) {
        for (int i = 0; i < count; i++)
            data->operator[](i + offset) = res[i];
    }
}
// </RadixSortPart>

// <BatchersMergePart>
template<class T>
void mergeFragments(std::vector<T>* data, std::vector<T>* result,
    int offset1, int size1, int offset2, int size2, bool isLeft) {

    if (isLeft) {
        T* firstPtr = data->data() + offset1;
        int usedFirst = 0;

        T* secondPtr = data->data() + offset2;
        int usedSecond = 0;

        for (int i = 0; i < size1; i++) {
            if (usedFirst < size1 && usedSecond < size2) {
                if (*firstPtr < *secondPtr) {
                    result->operator[](i) = *firstPtr;
                    firstPtr++;
                    usedFirst++;
                } else {
                    result->operator[](i) = *secondPtr;
                    secondPtr++;
                    usedSecond++;
                }
            } else if (usedFirst < size1 && usedSecond >= size2) {
                result->operator[](i) = *firstPtr;
                firstPtr++;
                usedFirst++;
            } else if (usedFirst >= size1 && usedSecond < size2) {
                result->operator[](i) = *secondPtr;
                secondPtr++;
                usedSecond++;
            } else {
                throw "Impossible exception";
            }
        }
        return;
    }

    // if isLeft = false
    T* firstPtr = data->data() + offset1 + size1 - 1;
    int usedFirst = 0;

    T* secondPtr = data->data() + offset2 + size2 - 1;
    int usedSecond = 0;

    for (int i = size2 - 1; i >= 0; i--) {
        if (usedFirst < size1 && usedSecond < size2) {
            if (*firstPtr > *secondPtr) {
                result->operator[](i) = *firstPtr;
                firstPtr--;
                usedFirst++;
            } else {
                result->operator[](i) = *secondPtr;
                secondPtr--;
                usedSecond++;
            }
        } else if (usedFirst < size1 && usedSecond >= size2) {
            result->operator[](i) = *firstPtr;
            firstPtr--;
            usedFirst++;
        } else if (usedFirst >= size1 && usedSecond < size2) {
            result->operator[](i) = *secondPtr;
            secondPtr--;
            usedSecond++;
        } else {
            throw "Impossible exception";
        }
    }
}

int partner(int nodeIndex, int mergeStage, int mergeStageStep);
// </BatchersMergePart>

// <ServiceFunctions>
template<class T>
T getRandValue(T from, T to) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(from, to);
    return dist(gen);
}

template<class T>
void fillVecWithRandValues(T* data, int size, T from, T to) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(from, to);
    for (int i = 0; i < size; i++) {
        data[i] = dist(gen);
    }
}

template<class T>
bool isStrictAscending(T* data, int size, T startValue) {
    for (int i = 0; i < size; i++)
        if (data[i] != startValue++)
            return false;
    return true;
}

template<class T>
bool isStrictDescending(T* data, int size, T startValue) {
    for (int i = 0; i < size; i++)
        if (data[i] != startValue--)
            return false;
    return true;
}

template<class T>
void fillStrictAscending(T* data, int size, T startValue) {
    for (int i = 0; i < size; i++)
        data[i] = startValue++;
}

template<class T>
void fillStrictDescending(T* data, int size, T startValue) {
    for (int i = 0; i < size; i++)
        data[i] = startValue--;
}

template<class T>
void printVector(const std::vector<T>& vec) {
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

template<class T>
bool isAscending(T* data, int size) {
    for (int i = 1; i < size; i++) {
        if (data[i - 1] > data[i])
            return false;
    }
    return true;
}

template<class T>
bool isVecSame(const std::vector<T>& v1, const std::vector<T>& v2) {
    if (v1.size() != v2.size())
        return false;
    for (size_t i = 0; i < v1.size(); i++)
        if (v1[i] != v2[i])
            return false;
    return true;
}
// </ServiceFunctions>

// <OMP REALISATION>
// ---------------------------<VER 1>---------------------------
template<class T>
void _parallelMerge(std::vector<T>* data, std::vector<T>* fragment,
    int blockSize, int selfID, int partnerID) {
    if (selfID == partnerID)
        return;

    bool isLeft = selfID < partnerID;
    int leftID = (isLeft) ? selfID : partnerID;
    int rightID = (isLeft) ? partnerID : selfID;

    mergeFragments<T>(data, fragment,
        leftID * blockSize, blockSize,
        rightID * blockSize, blockSize,
        isLeft);
}

// 2^degree = number of threads in use to sort
template<class T>
void radixBatchersMergeSort(std::vector<T>* data, int degree) {
    if (degree == 0) {  // numThreads = 1
        radixSort<T>(data, 0, data->size());
        return;
    }

    int numThreads = 1 << degree;
    if (numThreads > static_cast<int>(data->size())) {
        radixSort<T>(data, 0, data->size());
        return;
    }

    size_t oldSize = data->size();
    bool isResized = false;
    if (oldSize % numThreads != 0) {
        data->resize(oldSize + (numThreads - oldSize % numThreads), ~0);
        isResized = true;
    }

    int size = static_cast<int>(data->size());
    int blockSize = size / numThreads;

    #pragma omp parallel num_threads(numThreads)
    {
        int selfID = omp_get_thread_num();
        // sort step
        radixSort<T>(data, selfID * blockSize, blockSize);

        #pragma omp barrier

        // merge step
        // Batcher's merge network realisation
        int partnerID;
        std::vector<T> fragment(blockSize);

        for (int stage = 1; stage <= degree; stage++) {
            for (int step = 1; step <= stage; step++) {
                partnerID = partner(selfID, stage, step);

                // merge, but merge result will be in fragments of threads
                _parallelMerge<T>(data, &fragment,
                    blockSize, selfID, partnerID);

                // barrier to prevent data corruption
                #pragma omp barrier

                // copying fragments to data
                for (int i = 0; i < blockSize; i++)
                    data->operator[](selfID* blockSize + i) = fragment[i];

                // barrier to prevent data corruption
                #pragma omp barrier
                {}
            }
        }
    }

    if (isResized)
        data->resize(oldSize);
}
// ---------------------------</VER 1>---------------------------

// ---------------------------<VER 2>---------------------------
template<class T>
void _parallelMerge_v2(T* data, T* res,
    int blockSize, int selfID, int partnerID) {
    if (selfID == partnerID)
        return;

    bool isLeft = selfID < partnerID;
    int leftID = (isLeft) ? selfID : partnerID;
    int rightID = (isLeft) ? partnerID : selfID;

    int offset1 = leftID * blockSize;
    int offset2 = rightID * blockSize;

    if (isLeft) {
        T* firstPtr = data + offset1;
        int usedFirst = 0;

        T* secondPtr = data + offset2;
        int usedSecond = 0;

        for (int i = 0; i < blockSize; i++) {
            if (usedFirst < blockSize && usedSecond < blockSize) {
                if (*firstPtr < *secondPtr) {
                    res[offset1 + i] = *firstPtr;
                    firstPtr++;
                    usedFirst++;
                } else {
                    res[offset1 + i] = *secondPtr;
                    secondPtr++;
                    usedSecond++;
                }
            } else if (usedFirst < blockSize && usedSecond >= blockSize) {
                res[offset1 + i] = *firstPtr;
                firstPtr++;
                usedFirst++;
            } else if (usedFirst >= blockSize && usedSecond < blockSize) {
                res[offset1 + i] = *secondPtr;
                secondPtr++;
                usedSecond++;
            } else {
                throw "Impossible exception";
            }
        }
        return;
    }

    // if isLeft = false
    T* firstPtr = data + offset1 + blockSize - 1;
    int usedFirst = 0;

    T* secondPtr = data + offset2 + blockSize - 1;
    int usedSecond = 0;

    for (int i = blockSize - 1; i >= 0; i--) {
        if (usedFirst < blockSize && usedSecond < blockSize) {
            if (*firstPtr > *secondPtr) {
                res[offset2 + i] = *firstPtr;
                firstPtr--;
                usedFirst++;
            } else {
                res[offset2 + i] = *secondPtr;
                secondPtr--;
                usedSecond++;
            }
        } else if (usedFirst < blockSize && usedSecond >= blockSize) {
            res[offset2 + i] = *firstPtr;
            firstPtr--;
            usedFirst++;
        } else if (usedFirst >= blockSize && usedSecond < blockSize) {
            res[offset2 + i] = *secondPtr;
            secondPtr--;
            usedSecond++;
        } else {
            throw "Impossible exception";
        }
    }
}

// 2^degree = number of threads in use to sort
template<class T>
void radixBatchersMergeSort_v2(std::vector<T>* data, int degree) {
    if (degree == 0) {  // numThreads = 1
        radixSort<T>(data, 0, data->size());
        return;
    }

    int numThreads = 1 << degree;
    if (numThreads > static_cast<int>(data->size())) {
        radixSort<T>(data, 0, data->size());
        return;
    }

    size_t oldSize = data->size();
    bool isResized = false;
    if (oldSize % numThreads != 0) {
        data->resize(oldSize + (numThreads - oldSize % numThreads), ~0);
        isResized = true;
    }

    int size = data->size();
    int blockSize = size / numThreads;

    std::vector<T> res(size);
    int stepsMade = 0;

    T* from = data->data();
    T* to = res.data();
    T* tmp;

    #pragma omp parallel num_threads(numThreads)
    {
        int selfID = omp_get_thread_num();
        // sort step
        radixSort<T>(data, selfID * blockSize, blockSize);

        #pragma omp barrier

        // merge step
        // Batcher's merge network realisation
        int partnerID;

        for (int stage = 1; stage <= degree; stage++) {
            for (int step = 1; step <= stage; step++) {
                partnerID = partner(selfID, stage, step);

                _parallelMerge_v2(from, to, blockSize, selfID, partnerID);

                if (selfID == partnerID) {
                    for (int i = 0; i < blockSize; i++)
                        to[selfID * blockSize + i] = from[selfID * blockSize + i];
                }

                #pragma omp barrier
                #pragma omp single
                {
                    tmp = from;
                    from = to;
                    to = tmp;
                    stepsMade++;
                }
            }
        }
    }

    if (stepsMade % 2 == 1)
        memmove(data->data(), res.data(), data->size() * sizeof(T));

    if (isResized)
        data->resize(oldSize);
}
// ---------------------------</VER 2>---------------------------

// ---------------------------<VER 3>---------------------------
template<class T>
void _parallelMerge_v3(T* data, T* res, T* partnerData,
    int blockSize, int selfID, int partnerID) {
    if (selfID == partnerID)
        return;

    bool isLeft = selfID < partnerID;

    if (isLeft) {
        T* firstPtr = data;
        int usedFirst = 0;

        T* secondPtr = partnerData;
        int usedSecond = 0;

        for (int i = 0; i < blockSize; i++) {
            if (usedFirst < blockSize && usedSecond < blockSize) {
                if (*firstPtr < *secondPtr) {
                    res[i] = *firstPtr;
                    firstPtr++;
                    usedFirst++;
                } else {
                    res[i] = *secondPtr;
                    secondPtr++;
                    usedSecond++;
                }
            } else if (usedFirst < blockSize && usedSecond >= blockSize) {
                res[i] = *firstPtr;
                firstPtr++;
                usedFirst++;
            } else if (usedFirst >= blockSize && usedSecond < blockSize) {
                res[i] = *secondPtr;
                secondPtr++;
                usedSecond++;
            } else {
                throw "Impossible exception";
            }
        }
        return;
    }

    // if isLeft = false
    T* firstPtr = data + blockSize - 1;
    int usedFirst = 0;

    T* secondPtr = partnerData + blockSize - 1;
    int usedSecond = 0;

    for (int i = blockSize - 1; i >= 0; i--) {
        if (usedFirst < blockSize && usedSecond < blockSize) {
            if (*firstPtr > *secondPtr) {
                res[i] = *firstPtr;
                firstPtr--;
                usedFirst++;
            } else {
                res[i] = *secondPtr;
                secondPtr--;
                usedSecond++;
            }
        } else if (usedFirst < blockSize && usedSecond >= blockSize) {
            res[i] = *firstPtr;
            firstPtr--;
            usedFirst++;
        } else if (usedFirst >= blockSize && usedSecond < blockSize) {
            res[i] = *secondPtr;
            secondPtr--;
            usedSecond++;
        } else {
            throw "Impossible exception";
        }
    }
}


// 2^degree = number of threads in use to sort
template<class T>
void radixBatchersMergeSort_v3(std::vector<T>* data, int degree) {
    if (degree == 0) {  // numThreads = 1
        radixSort<T>(data, 0, data->size());
        return;
    }

    int numThreads = 1 << degree;
    if (numThreads > static_cast<int>(data->size())) {
        radixSort<T>(data, 0, data->size());
        return;
    }

    size_t oldSize = data->size();
    bool isResized = false;
    if (oldSize % numThreads != 0) {
        data->resize(oldSize + (numThreads - oldSize % numThreads), ~0);
        isResized = true;
    }

    int size = data->size();
    int blockSize = size / numThreads;

    std::vector<T> res(size);

    T** from = new T * [numThreads];
    T** to = new T * [numThreads];

    for (int i = 0; i < numThreads; i++) {
        from[i] = data->data() + blockSize * i;
        to[i] = res.data() + blockSize * i;
    }
    T* mainData = data->data();

    #pragma omp parallel num_threads(numThreads)
    {
        int selfID = omp_get_thread_num();
        // sort step
        radixSort<T>(data, selfID * blockSize, blockSize);

        #pragma omp barrier

        // merge step
        // Batcher's merge network realisation
        int partnerID;

        for (int stage = 1; stage <= degree; stage++) {
            for (int step = 1; step <= stage; step++) {
                partnerID = partner(selfID, stage, step);

                _parallelMerge_v3(from[selfID], to[selfID], from[partnerID], blockSize, selfID, partnerID);
                #pragma omp barrier

                if (selfID != partnerID)
                    std::swap(from[selfID], to[selfID]);
                #pragma omp barrier

                if (stage == degree && step == degree) {
                    for (int i = 0; i < blockSize; i++)
                        mainData[selfID * blockSize + i] = from[selfID][i];
                }
            }
        }
        #pragma omp barrier
        {}
    }
    delete[] from;
    delete[] to;
    if (isResized)
        data->resize(oldSize);
}
// </OMP REALISATION>

#endif  // MODULES_TASK_2_IVANOV_A_RADIX_BATCHERS_MERGESORT_OMP_RBMS_H_
