// Copyright 2022 Kazhaeva Anastasia
#ifndef MODULES_TASK_4_KAZHAEVA_A_DJIKSTRA_DJIKSTRA_H_
#define MODULES_TASK_4_KAZHAEVA_A_DJIKSTRA_DJIKSTRA_H_

#include <string>
#include <vector>

std::vector<std::vector<int>> randomVectorDjikstra(const int count);

std::vector<int> djikstra(const int top,
const std::vector<std::vector<int>>& matrix);

std::vector<std::vector<int>> sequentialDjikstra(
const std::vector<std::vector<int>>& matrix);

std::vector<std::vector<int>> parallelDjikstra(int numThreads,
const std::vector<std::vector<int>>& matrix);



#endif  // MODULES_TASK_4_KAZHAEVA_A_DJIKSTRA_DJIKSTRA_H_
