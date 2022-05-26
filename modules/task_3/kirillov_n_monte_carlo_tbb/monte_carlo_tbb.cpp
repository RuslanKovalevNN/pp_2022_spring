// Copyright 2022 Kirillov Nikita
#include "../../../modules/task_3/kirillov_n_monte_carlo_tbb/monte_carlo_tbb.h"

#include <tbb/tbb.h>

#include <random>
#include <stdexcept>
#include <vector>

double SeqMonteCarloIntegration(
    const std::function<double(const std::vector<double>)>& integrand,
    const std::vector<std::pair<double, double>>& intervals, const size_t& N) {
  if (N <= 0) throw std::runtime_error("Number of points must be more than 0");

  size_t num_dims = intervals.size();
  if (num_dims <= 0)
    throw std::runtime_error("Number of dims must be more than 0");

  std::random_device rd;
  std::mt19937 gen(rd());

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

class Integration {
 private:
  const std::function<double(const std::vector<double>)>& integrand;
  const std::vector<std::pair<double, double>>& intervals;
  double sum;
  std::uniform_real_distribution<double> dist =
      std::uniform_real_distribution<double>(0.0, 1.0);
  std::random_device rd;
  std::mt19937 gen = std::mt19937(rd());

 public:
  Integration(const std::function<double(const std::vector<double>)>& integ,
              const std::vector<std::pair<double, double>>& interv)
      : integrand(integ), intervals(interv), sum(0.0) {}

  Integration(Integration& i, tbb::split)
      : integrand(i.integrand), intervals(i.intervals), sum(0.0) {}

  void operator()(const tbb::blocked_range<int>& r) {
    size_t num_dims = intervals.size();
    std::vector<double> point(num_dims);
    for (auto i = r.begin(); i != r.end(); i++) {
      for (size_t j = 0; j < num_dims; j++)
        point[j] = intervals[j].first +
                   (intervals[j].second - intervals[j].first) * dist(gen);
      sum += integrand(point);
    }
  }

  void join(const Integration& i) { sum += i.sum; }

  double getSum() { return sum; }
};

double ParallelMonteCarloIntegration(
    const std::function<double(const std::vector<double>)>& integrand,
    const std::vector<std::pair<double, double>>& intervals, const int& N) {
  if (N <= 0) throw std::runtime_error("Number of points must be more than 0");

  const size_t num_dims = intervals.size();
  if (num_dims <= 0)
    throw std::runtime_error("Number of dims must be more than 0");

  Integration integr(integrand, intervals);
  tbb::parallel_reduce(tbb::blocked_range<int>(0, N), integr);

  double mes = 1.0;
  for (size_t i = 0; i < num_dims; i++)
    mes *= intervals[i].second - intervals[i].first;

  double sum = integr.getSum();
  double result = (sum * mes) / N;
  return result;
}
