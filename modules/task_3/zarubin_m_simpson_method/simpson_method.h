// Copyright 2022 Zarubin Mikhail

#ifndef MODULES_TASK_3_ZARUBIN_M_SIMPSON_METHOD_SIMPSON_METHOD_H_
#define MODULES_TASK_3_ZARUBIN_M_SIMPSON_METHOD_SIMPSON_METHOD_H_

#include <tbb/task_scheduler_init.h>
#include <functional>
#include <vector>

using sizeType = std::vector<double>::size_type;


double simpsonMethodSeq(sizeType dimension,
    std::vector<double> leftBorders, std::vector<double> rightBorders,
    std::function<double(std::vector<double>)> function, std::vector<sizeType> countParts);

double simpsonMethodParallel(sizeType dimension,
    std::vector<double> leftBorders, std::vector<double> rightBorders,
    std::function<double(std::vector<double>)> function, std::vector<sizeType> countParts,
    int processCount = tbb::task_scheduler_init::default_num_threads());

#endif  // MODULES_TASK_3_ZARUBIN_M_SIMPSON_METHOD_SIMPSON_METHOD_H_
