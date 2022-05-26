// Copyright 2022 Gleb "belgad" Danshin
#include <thread>  // NOLINT [build/c++11]

#include "../../../modules/task_4/danshin_g_integral_rectangle/integral_rectangle.hpp"

double Integrate(size_t dim, double* step, double* lower, double* upper,
                 Function func, size_t thread_num) {
  double result = 0.0;
  int total = 1;
  auto size = new int[dim];
  for (size_t k = 0; k < dim; ++k) {
    total *= size[k] = static_cast<int>((upper[k] - lower[k]) / step[k]);
  }
  if (static_cast<size_t>(total) <= thread_num) {
    return IntegrateSequence(dim, step, lower, upper, func);
  }
  std::thread* threads = new std::thread[thread_num];
  double* threads_result = new double[thread_num];
  std::fill(threads_result, threads_result + thread_num, 0);
  int* edges = new int[thread_num + 1];
  for (size_t i = 0; i < thread_num; ++i) {
    edges[i] = i * total / thread_num;
  }
  edges[thread_num] = total;
  for (size_t i = 0; i < thread_num; ++i) {
    threads[i] = std::thread{IntegrateThread, dim, step, lower, size, func,
                             edges[i], edges[i + 1], threads_result + i};
  }
  for (size_t i = 0; i < thread_num; ++i) {
    threads[i].join();
    result += threads_result[i];
  }
  delete[] threads;
  delete[] threads_result;
  delete[] edges;
  for (size_t k = 0; k < dim; ++k) {
    result *= step[k];
  }
  delete[] size;
  return result;
}

void IntegrateThread(size_t dim, double* step, double* lower, int* size,
                     Function func, int start, int end, double* result) {
  *result = 0;
  auto curr_point = new double[dim];
  for (int i = start; i < end; ++i) {
    int j = i;
    for (size_t k = 0; k < dim; ++k) {
      curr_point[k] = lower[k] + static_cast<double>(j % size[k]) * step[k];
      j /= size[k];
    }
    *result += func(curr_point);
  }
  delete[] curr_point;
}

double IntegrateSequence(size_t dim, double* step, double* lower, double* upper,
                         Function func) {
  double result = 0;
  int total = 1;
  auto size = new int[dim];
  for (size_t k = 0; k < dim; ++k) {
    total *= size[k] = static_cast<int>((upper[k] - lower[k]) / step[k]);
  }
  auto curr_point = new double[dim];
  int j;
  for (int i = 0; i < total; ++i) {
    j = i;
    for (size_t k = 0; k < dim; ++k) {
      curr_point[k] = lower[k] + static_cast<double>(j % size[k]) * step[k];
        j /= size[k];
    }
    result += func(curr_point);
  }
  delete[] size;
  delete[] curr_point;
  for (size_t k = 0; k < dim; ++k) {
    result *= step[k];
  }
  return result;
}
