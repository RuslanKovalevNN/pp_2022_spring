// Copyright 2022 Kirillov Nikita
#ifndef MODULES_TASK_1_KIRILLOV_N_MONTE_CARLO_MONTE_CARLO_H_
#define MODULES_TASK_1_KIRILLOV_N_MONTE_CARLO_MONTE_CARLO_H_

#include <functional>
#include <utility>
#include <vector>

double MonteCarloIntegration_(
    const std::function<double(const std::vector<double>)>& integrand,
    const std::vector<std::pair<double, double>>& intervals, const size_t& N);

#endif  // MODULES_TASK_1_KIRILLOV_N_MONTE_CARLO_MONTE_CARLO_H_
