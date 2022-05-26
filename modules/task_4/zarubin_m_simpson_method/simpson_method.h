// Copyright 2022 Zarubin Mikhail

#ifndef MODULES_TASK_4_ZARUBIN_M_SIMPSON_METHOD_SIMPSON_METHOD_H_
#define MODULES_TASK_4_ZARUBIN_M_SIMPSON_METHOD_SIMPSON_METHOD_H_

#include <functional>
#include <vector>

const double ERROR = 0.001;

using sizeType = std::vector<double>::size_type;


double simpsonMethodSeq(sizeType dimension,
    std::vector<double> leftBorders, std::vector<double> rightBorders,
    std::function<double(std::vector<double>)> function, std::vector<sizeType> countParts);

double simpsonMethodParallel(sizeType dimension,
    std::vector<double> leftBorders, std::vector<double> rightBorders,
    std::function<double(std::vector<double>)> function, std::vector<sizeType> countParts,
    sizeType threadsCount = 12);

#endif  // MODULES_TASK_4_ZARUBIN_M_SIMPSON_METHOD_SIMPSON_METHOD_H_

