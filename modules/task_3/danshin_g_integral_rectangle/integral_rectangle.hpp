// Copyright 2022 Gleb "belgad" Danshin
#ifndef MODULES_TASK_3_DANSHIN_G_INTEGRAL_RECTANGLE_INTEGRAL_RECTANGLE_HPP_
#define MODULES_TASK_3_DANSHIN_G_INTEGRAL_RECTANGLE_INTEGRAL_RECTANGLE_HPP_

#include <functional>

using Function = std::function<double(double*)>;

double Integrate(size_t, double*, double*, double*, Function, size_t = 0);

double IntegrateSequence(size_t, double*, double*, double*, Function);

#endif  // MODULES_TASK_3_DANSHIN_G_INTEGRAL_RECTANGLE_INTEGRAL_RECTANGLE_HPP_
