// Copyright 2022 Lukashuk Diana
#ifndef MODULES_TASK_3_LUKASHUK_D_SIMPSON_SIMPSON_H_
#define MODULES_TASK_3_LUKASHUK_D_SIMPSON_SIMPSON_H_

#include <tbb/tbb.h>

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

typedef double (*FUNC_T)(const std::vector<double>&);
typedef std::vector<std::pair<double, double>> BORDER_T;

double simpson(const FUNC_T& f, const BORDER_T& borders,
               const std::vector<int>& steps);

double simpson_par(const FUNC_T& f, const BORDER_T& borders,
                   const std::vector<int>& steps);

#endif  // MODULES_TASK_3_LUKASHUK_D_SIMPSON_SIMPSON_H_
