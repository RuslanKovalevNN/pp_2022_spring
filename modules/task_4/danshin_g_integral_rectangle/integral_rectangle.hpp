// Copyright 2022 Gleb "belgad" Danshin
#ifndef MODULES_TASK_4_DANSHIN_G_INTEGRAL_RECTANGLE_INTEGRAL_RECTANGLE_HPP_
#define MODULES_TASK_4_DANSHIN_G_INTEGRAL_RECTANGLE_INTEGRAL_RECTANGLE_HPP_

#include <functional>
#include <thread>  // NOLINT [build/c++11]

using Function = std::function<double(double*)>;

double Integrate(size_t dim, double* step, double* lower, double* upper,
                 Function func,
                 size_t thread_num = std::thread::hardware_concurrency());
void IntegrateThread(size_t dim, double* step, double* lower, int* size,
                     Function func, int start, int end, double* result);

double IntegrateSequence(size_t dim, double* step, double* lower, double* upper,
                         Function func);

#endif  // MODULES_TASK_4_DANSHIN_G_INTEGRAL_RECTANGLE_INTEGRAL_RECTANGLE_HPP_
