// Copyright 2022 Ustiuzhanin Nikita

#include "../../../modules/task_1/ustiuzhanin_n_radix_sort_simple_merge/radix_sort.h"

void randomVector(vector<int>* data, size_t size, size_t rad) {
    if (!size)
        return;

    data->clear();
    data->resize(size);

    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<int> dist(0, pow(10, rad));
    for (size_t i = 0; i < data->size(); i++)
        data->at(i) = dist(mersenne);
}

int getNum(int val, size_t pos) {
    while (pos > 1) {
        val /= 10;
        pos--;
    }

    return val % 10;
}

size_t rad(size_t value) {
    size_t counter = 0;
    while (value != 0) {
        value /= 10;
        counter++;
    }
    return counter;
}

void radixSort(vector<int>* data) {
    if (!data->size())
        return;

    if (std::find_if(data->begin(), data->end(), [](int val) {
        return val < 0; }) != data->end())
        throw std::string("Try sort numbers less then 0");

    size_t maxRad = rad(*std::max_element(data->begin(), data->end()));

    vector<list<int>> helpList(10);

    for (size_t i = 1; i <= maxRad; i++) {
        for (int val : *data) {
            helpList[getNum(val, i)].push_back(val);
        }

        data->clear();
        for (list<int> l : helpList) {
            for (int val : l)
                data->push_back(val);
        }

        helpList.clear();
        helpList.resize(10);
    }
}
