// Copyright 2022 Andrich Maria
#include <functional>

#include <ctime>

#include <random>

#include <string>

#include <algorithm>

#include <iostream>

#include <vector>

#include "../../3rdparty/unapproved/unapproved.h"

#include "../../../modules/task_4/andrich_m_montecarlo/monte_carlo.h"

double seqMonteCarlo(double(*f)(const std::vector < double > &),
  const std::vector < double > & a,
    const std::vector < double > & b, int steps) {
  if (steps <= 0)
    throw "integral is negative";
  double res = 0.0;
  std::mt19937 gen;
  gen.seed(static_cast < unsigned int > (time(0)));

  int mult = a.size();
  double S = 1;
  for (int i = 0; i < mult; i++)
    S *= (b[i] - a[i]);

  std::vector < std::uniform_real_distribution < double >> r(mult);
  std::vector < double > r1(mult);
  for (int i = 0; i < mult; i++)
    r[i] = std::uniform_real_distribution < double > (a[i], b[i]);

  for (int i = 0; i < steps; ++i) {
    for (int j = 0; j < mult; ++j)
      r1[j] = r[j](gen);
    res += f(r1);
  }

  res *= S / steps;
  return res;
}

double stdMonteCarlo(double(*f)(const std::vector < double > &),
  const std::vector < double > & a,
    const std::vector < double > & b, int steps) {
  if (steps <= 0)
    throw "integral is negative";
  double res = 0.0;
  auto mult = a.size();
  std::vector < std::uniform_real_distribution < double >> r(mult);
  for (size_t i = 0; i < mult; i++)
    r[i] = std::uniform_real_distribution < double > (a[i], b[i]);

  auto num_threads = std::thread::hardware_concurrency();
  std::vector < std::thread > threads;
  std::vector < double > local_res(num_threads);
  auto start = 0;
  size_t k = steps % num_threads;

  for (size_t i = 0; i < num_threads; ++i) {
    my_range range;
    if (k > i) {
      range.start = start;
      range.end = start + (steps / num_threads) + 1;
      start += (steps / num_threads) + 1;
    } else {
      range.start = start;
      range.end = start + (steps / num_threads);
      start += (steps / num_threads);
    }
    threads.emplace_back([ & , range, i]() {
      std::mt19937 gen;
      gen.seed(static_cast < unsigned int > (time(0)));
      std::vector < double > r1(mult);
      local_res[i] = 0;
      for (int k = range.start; k < range.end; ++k) {
        for (size_t j = 0; j < mult; ++j)
          r1[j] = r[j](gen);
        local_res[i] += f(r1);
      }
    });
  }

  for (auto & thread : threads) {
    thread.join();
  }

  for (size_t i = 0; i < num_threads; ++i) {
    res += local_res[i];
  }

  double S = 1;
  for (size_t i = 0; i < mult; i++)
    S *= (b[i] - a[i]);
  res *= S / steps;

  return res;
}
