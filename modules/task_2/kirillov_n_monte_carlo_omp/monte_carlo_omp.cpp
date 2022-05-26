// Copyright 2022 Kirillov Nikita
#include "../../../modules/task_2/kirillov_n_monte_carlo_omp/monte_carlo_omp.h"

#include <omp.h>

#include <ctime>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

double SeqMonteCarloIntegration(
    const std::function<double(const std::vector<double>)>& integrand,
    const std::vector<std::pair<double, double>>& intervals, const size_t& N) {
  if (N <= 0) throw std::runtime_error("Number of dots must be more than 0");

  size_t num_dims = intervals.size();
  if (num_dims <= 0)
    throw std::runtime_error("Number of dims must be more than 0");

  std::mt19937 gen(time(0));

  std::uniform_real_distribution<double> dist(0.0, 1.0);

  std::vector<double> point(num_dims);
  double sum = 0.0;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < num_dims; j++)
      point[j] = intervals[j].first +
                 (intervals[j].second - intervals[j].first) * dist(gen);
    sum += integrand(point);
  }

  double mes = 1.0;
  for (size_t i = 0; i < num_dims; i++) {
    mes *= intervals[i].second - intervals[i].first;
  }

  double result = (sum * mes) / N;
  return result;
}

double ParallelMonteCarloIntegration(
    const std::function<double(const std::vector<double>)>& integrand,
    const std::vector<std::pair<double, double>>& intervals, const int& N) {
  if (N <= 0) throw std::runtime_error("Number of dots must be more than 0");

  const int num_dims = intervals.size();
  if (num_dims <= 0)
    throw std::runtime_error("Number of dims must be more than 0");

  std::uniform_real_distribution<double> dist(0.0, 1.0);

  double sum = 0.0;
#pragma omp parallel reduction(+ : sum)
  {
    std::mt19937 gen(time(0));
    std::vector<double> point(num_dims);

#pragma omp for
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < num_dims; j++)
        point[j] = intervals[j].first +
                   (intervals[j].second - intervals[j].first) * dist(gen);
      sum += integrand(point);
    }
  }

  double mes = 1.0;
  for (int i = 0; i < num_dims; i++) {
    mes *= intervals[i].second - intervals[i].first;
  }

  double result = (sum * mes) / N;
  return result;
}
