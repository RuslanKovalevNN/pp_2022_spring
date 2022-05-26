// Copyright 2022 Andrich Maria
#ifndef MODULES_TASK_3_ANDRICH_M_MONTECARLO_MONTE_CARLO_H_
#define MODULES_TASK_3_ANDRICH_M_MONTECARLO_MONTE_CARLO_H_

#include <vector>

#include <string>

double seqMonteCarlo(double(*f)(const std::vector < double > &),
  const std::vector < double > & a,
    const std::vector < double > & b, int s);

double tbbMonteCarlo(double(*f)(const std::vector < double > &),
  const std::vector < double > & a,
    const std::vector < double > & b, int s);

#endif  // MODULES_TASK_3_ANDRICH_M_MONTECARLO_MONTE_CARLO_H_

