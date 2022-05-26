// Copyright 2022 Groshev Nickolay
#ifndef MODULES_TASK_1_GROSHEV_N_MONTE_CARLO_INTEGRALS_INTEGRATION_MONTE_CARLO_H_
#define MODULES_TASK_1_GROSHEV_N_MONTE_CARLO_INTEGRALS_INTEGRATION_MONTE_CARLO_H_

#include <vector>
#include <functional>

double getIntegralSequential(int n, const std::vector<double>& low, const std::vector<double>& top,
  const std::function<double(const std::vector<double>&)>& f);

#endif  // MODULES_TASK_1_GROSHEV_N_MONTE_CARLO_INTEGRALS_INTEGRATION_MONTE_CARLO_H_
