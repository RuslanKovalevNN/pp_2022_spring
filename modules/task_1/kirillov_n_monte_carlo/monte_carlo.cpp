// Copyright 2022 Kirillov Nikita
#include "../../../modules/task_1/kirillov_n_monte_carlo/monte_carlo.h"

#include <omp.h>

#include <ctime>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

double MonteCarloIntegration_(
    const std::function<double(const std::vector<double>)>& integrand,
    const std::vector<std::pair<double, double>>& intervals, const size_t& N) {
  if (N <= 0) throw -1;

  size_t num_dims = intervals.size();
  if (num_dims <= 0) throw -1;

  std::mt19937 gen(time(0));

  std::vector<std::uniform_real_distribution<double>> dist(num_dims);
  for (size_t i = 0; i < num_dims; i++)
    dist[i] = std::uniform_real_distribution<double>(intervals[i].first,
                                                     intervals[i].second);

  std::vector<double> point(num_dims);
  double sum = 0.0;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < num_dims; j++) point[j] = dist[j](gen);
    sum += integrand(point);
  }

  double mes = 1.0;
  for (size_t i = 0; i < num_dims; i++) {
    mes *= intervals[i].second - intervals[i].first;
  }
  double result = (sum * mes) / N;
  return result;
}
