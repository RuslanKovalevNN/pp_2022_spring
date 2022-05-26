// Copyright 2022 Remizova Antonina
#ifndef MODULES_TASK_4_REMIZOVA_A_HOAR_BATCHER_HOAR_BATCHER_H_
#define MODULES_TASK_4_REMIZOVA_A_HOAR_BATCHER_HOAR_BATCHER_H_

#include <random>
#include <vector>
#include <ctime>

std::vector<double> getRandVector(int size);
bool isSortCorrectly(const std::vector <double>& vec);
void hoarSort(std::vector <double>* vec, int left, int right);
std::vector<double> evenBatcherSort(const std::vector<double>& vec1, const std::vector<double>& vec2);
std::vector<double> oddBatcherSort(const std::vector<double>& vec1, const std::vector<double>& vec2);
std::vector<double> oddEvenBatcherSort(const std::vector<double>& vec1, const std::vector<double>& vec2);
std::vector<double> mergeBatcherSeq(const std::vector<double>& vec, int middle);
std::vector<double> hoarBatcherSeq(const std::vector<double>& vec, int size);
std::vector<double> hoarBatcherPar(const std::vector<double>& vec, int size);

#endif  // MODULES_TASK_4_REMIZOVA_A_HOAR_BATCHER_HOAR_BATCHER_H_
