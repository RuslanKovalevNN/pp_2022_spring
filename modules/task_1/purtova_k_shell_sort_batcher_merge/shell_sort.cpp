// Copyright 2022 Purtova Ksenia
#include "../../../modules/task_1/purtova_k_shell_sort_batcher_merge/shell_sort.h"
#include <iostream>
#include <vector>

#include <random>
#include <ctime>

std::vector<int> VectorRandomizer(int size) {
    std::vector<int> vec(size);

    std::mt19937 engine;
    engine.seed(static_cast<int>(time(nullptr)));

    for (int i = 0; i < size; i++)
        vec[i] = engine();

    return vec;
}

std::vector<int> Shell(const std::vector<int>& arr, int n) {
    std::vector<int> A = arr;
    for (int step = n / 2; step > 0; step /= 2) {
        for (int i = step; i < n; i++) {
            for (int j = i - step; j >= 0 && A[j] > A[j + step]; j -= step) {
                int x = A[j];
                A[j] = A[j + step];
                A[j + step] = x;
            }
        }
    }
    return A;
}

std::vector<int> MergerEvenOdd(const std::vector<int>& arr1, const std::vector<int>& arr2, int i1, int i2, int size) {
    std::vector <int> array_result(size);
    int i = 0;
    int arr1_size = arr1.size();
    int arr2_size = arr2.size();
    while ((i1 < arr1_size) && (i2 < arr2_size)) {
        if (arr1[i1] <= arr2[i2]) {
            array_result[i] = arr1[i1];
            i++;
            i1 += 2;
        } else {
            array_result[i] = arr2[i2];
            i++;
            i2 += 2;
        }
    }

    if (i1 >= arr1_size) {
        while (i2 < arr2_size) {
            array_result[i] = arr2[i2];
            i++;
            i2 +=2;
        }
    }
    if (i2 >= arr2_size) {
        while (i1 < arr1_size) {
            array_result[i] = arr1[i1];
            i++;
            i1 += 2;
        }
    }

    return array_result;
}

std::vector<int> BatcherEvenNumber(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    int arr1_size = arr1.size();
    int arr2_size = arr2.size();
    int size_result = arr1_size/2 + arr2_size/2 + arr1_size%2 + arr2_size%2;

    std::vector <int> array_result(size_result);

    int i1 = 0, i2 = 0;

    array_result = MergerEvenOdd(arr1, arr2, i1, i2, size_result);

    return array_result;
}

std::vector<int> BatcherOddNumber(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    int arr1_size = arr1.size();
    int arr2_size = arr2.size();
    int size_result = arr1_size / 2 + arr2_size / 2;

    std::vector <int> array_result(size_result);

    int i1 = 1, i2 = 1;

    array_result = MergerEvenOdd(arr1, arr2, i1, i2, size_result);

    return array_result;
}

std::vector<int> BatcherMerger(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    int arr1_size = arr1.size();
    int arr2_size = arr2.size();
    int size_result = arr1_size + arr2_size;
    std::vector<int> array_result(size_result);
    int i1 = 0, i2 = 0, i = 0;

    while ((i1 != arr1_size) && (i2 != arr2_size)) {
        if (arr1[i1] <= arr2[i2]) {
            array_result[i] = arr1[i1];
            i1++;
        } else {
            array_result[i] = arr2[i2];
            i2++;
        }
        i++;
    }
    if (i1 == arr1_size) {
        for (int j = i2; j < arr2_size; j++)
            array_result[arr1_size + j] = arr2[j];
    } else {
        for (int j = i1; j < arr1_size; j++)
            array_result[arr2_size + j] = arr1[j];
    }
    return array_result;
}

std::vector<int> ShellWithBatcher(const std::vector<int>& A, int n) {
    int half = n / 2;
    std::vector<int> arr1(half + 1);
    arr1 = { A.begin(), A.end() - half };
    std::vector<int> arr2(half);
    arr2 = { A.end() - half, A.end() };

    int arr1_size = arr1.size();
    int arr2_size = arr2.size();

    arr1 = Shell(arr1, arr1_size);
    arr2 = Shell(arr2, arr2_size);

    std::vector<int> even = BatcherEvenNumber(arr1, arr2);
    std::vector<int> odd = BatcherOddNumber(arr1, arr2);
    std::vector<int> merger = BatcherMerger(even, odd);
    return merger;
}
