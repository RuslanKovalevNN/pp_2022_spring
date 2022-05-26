// Copyright 2022 Ivanov Arkady
#ifndef MODULES_TASK_3_IVANOV_A_RADIX_BATCHERS_MERGESORT_TBB_RBMS_H_
#define MODULES_TASK_3_IVANOV_A_RADIX_BATCHERS_MERGESORT_TBB_RBMS_H_

#include <stdint.h>
#include <tbb/parallel_for_each.h>
#include <tbb/task_scheduler_init.h>
#include <tbb/blocked_range.h>
#include <tbb/task_group.h>
#include <tbb/spin_mutex.h>

#include <vector>
#include <random>
#include <algorithm>
#include <utility>
#include <iostream>
#include <condition_variable>  // NOLINT [build/c++11]
#include <mutex>  // NOLINT [build/c++11]


/*
* Barrier class
* In parallel code can't be called sequentially
* or there will be a possibility of a deadlock +
* barrier crossing of single thread
* NOT TO DO: {
*       // work
*       barrier.wait();
*       // work
*       barrier.wait();
* }
*
* insted use 2 alternating barriers: {
*       // work
*       barrier1.wait();
*       // work
*       barrier2.wait();
*       // work
*       barrier1.wait();
*       // work
*       barrier2.wait();
*       // etc
* }
*/
class Barrier {
 private:
    const unsigned int threadCount;
    volatile unsigned int threadsWaiting;
    std::condition_variable waitVariable;
    std::mutex mutex;
    volatile bool isLocked;

 public:
    Barrier() = delete;
    Barrier(const Barrier& c) = delete;
    Barrier& operator=(const Barrier& c) = delete;

    explicit Barrier(unsigned int n) :
        threadCount(n),
        threadsWaiting(0),
        isLocked(true) {}


    void wait() {
        std::unique_lock<std::mutex> lk(mutex);
        ++threadsWaiting;
        if (threadsWaiting >= threadCount) {
            threadsWaiting = 0;
            isLocked = false;

            lk.unlock();
            waitVariable.notify_all();
        } else {
            while (isLocked && threadsWaiting != 0)
                waitVariable.wait(lk);
            isLocked = true;  // to make reusable
        }
    }
};

int partner(int nodeIndex, int mergeStage, int mergeStageStep);

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

// <TBB REALISATION>
template<class T>
void mergeFragments(T* data, T* res, T* partnerData,
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
void radixBatchersMergesort_tbb(std::vector<T>* data, int degree) {
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


    tbb::task_scheduler_init init(numThreads);
    tbb::task_group group;
    Barrier b1(numThreads), b2(numThreads), b3(numThreads);

    for (int selfID = 0; selfID < numThreads; selfID++) {
        group.run([selfID, &b1, &b2, &b3, from, to, data,
            blockSize, degree, mainData]() {
                // sort step
                radixSort<T>(data, selfID * blockSize, blockSize);

                // barrier
                b3.wait();

                // merge step
                // Batcher's merge network realisation
                int partnerID;

                for (int stage = 1; stage <= degree; stage++) {
                    for (int step = 1; step <= stage; step++) {
                        partnerID = partner(selfID, stage, step);

                        mergeFragments(from[selfID], to[selfID], from[partnerID], blockSize, selfID, partnerID);
                        b1.wait();

                        if (selfID != partnerID)
                            std::swap(from[selfID], to[selfID]);
                        b2.wait();

                        if (stage == degree && step == degree) {
                            for (int i = 0; i < blockSize; i++)
                                mainData[selfID * blockSize + i] = from[selfID][i];
                        }
                    }
                }
                b3.wait();
            });
    }
    group.wait();

    delete[] from;
    delete[] to;

    if (isResized)
        data->resize(oldSize);
}
// </TBB REALISATION>

#endif  // MODULES_TASK_3_IVANOV_A_RADIX_BATCHERS_MERGESORT_TBB_RBMS_H_
