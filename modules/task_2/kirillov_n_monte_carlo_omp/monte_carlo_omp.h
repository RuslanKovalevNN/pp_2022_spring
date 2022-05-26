// Copyright 2022 Kirillov Nikita
#ifndef MODULES_TASK_2_KIRILLOV_N_MONTE_CARLO_OMP_MONTE_CARLO_OMP_H_
#define MODULES_TASK_2_KIRILLOV_N_MONTE_CARLO_OMP_MONTE_CARLO_OMP_H_

#include <functional>
#include <utility>
#include <vector>

double SeqMonteCarloIntegration(
    const std::function<double(const std::vector<double>)>& integrand,
    const std::vector<std::pair<double, double>>& intervals, const size_t& N);

double ParallelMonteCarloIntegration(
    const std::function<double(const std::vector<double>)>& integrand,
    const std::vector<std::pair<double, double>>& intervals, const int& N);

#endif  // MODULES_TASK_2_KIRILLOV_N_MONTE_CARLO_OMP_MONTE_CARLO_OMP_H_
