// Copyright 2022 Andric Maria
#ifndef MODULES_TASK_2_ANDRIC_M_MONTECARLO_MONTECARLO_H_
#define MODULES_TASK_2_ANDRIC_M_MONTECARLO_MONTECARLO_H_

#include <omp.h>

#include <random>

#include <vector>

double MonteCarloSeq(double(*func)(const std::vector < double > &),
  const std::vector < double > & left,
    const std::vector < double > & right,
      uint64_t steps, int seed = 0);

double MonteCarloOmp(double(*func)(const std::vector < double > &),
  const std::vector < double > & left,
    const std::vector < double > & right,
      uint64_t steps, int threadnum, int seed = 0);

#endif  // MODULES_TASK_2_ANDRIC_M_MONTECARLO_MONTECARLO_H_





