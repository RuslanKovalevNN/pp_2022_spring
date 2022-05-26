// Copyright 2022 Lukashuk Diana
#include "../../../modules/task_3/lukashuk_d_simpson/simpson.h"

typedef std::vector<double> VEC_T;

double simpson(const FUNC_T& f, const BORDER_T& borders,
               const std::vector<int>& steps) {
  int iter = 1;
  int dimen = static_cast<int>(steps.size());
  double integral = 0;
  int pow_6 = static_cast<int>(std::pow(6, dimen));
  VEC_T h(dimen);
  std::vector<VEC_T> param(dimen, VEC_T(6));
  VEC_T args(dimen);
  for (int i = 0; i < dimen; i++) {
    h[i] = (borders[i].second - borders[i].first) / steps[i];
    iter *= steps[i];
  }
  for (int i = 0, x = i; i < iter; i++, x = i) {
    for (int d = 0; d < dimen; d++) {
      param[d][0] = borders[d].first + (x % steps[d]) * h[d];
      param[d][1] = param[d][0] + h[d] / 2;
      param[d][4] = param[d][3] = param[d][2] = param[d][1];
      param[d][5] = param[d][0] + h[d];
      x /= steps[d];
    }
    for (int j = 0, x = j; j < pow_6; j++, x = j) {
      for (int d = 0; d < dimen; d++) {
        args[d] = param[d][x % 6];
        x /= 6;
      }
      integral += f(args);
    }
  }
  for (int i = 0; i < dimen; i++) {
    integral *= h[i] / 6.0;
  }
  return integral;
}

double simpson_par(const FUNC_T& f, const BORDER_T& borders,
                   const std::vector<int>& steps) {
  int iter = 1;
  int dimen = static_cast<int>(steps.size());
  int pow_6 = static_cast<int>(std::pow(6, dimen));
  VEC_T h(dimen);
  for (int i = 0; i < dimen; i++) {
    h[i] = (borders[i].second - borders[i].first) / steps[i];
    iter *= steps[i];
  }
  double integral = tbb::parallel_reduce(
      tbb::blocked_range<int>(0, iter, iter / 4), 0.0,
      [&](tbb::blocked_range<int> dim, double local_res) {
        std::vector<VEC_T> param(dimen, VEC_T(6));
        std::vector<double> args(dimen);
        for (auto i = dim.begin(); i < dim.end(); i++) {
          int x = i;
          for (int d = 0; d < dimen; d++) {
            param[d][0] = borders[d].first + (x % steps[d]) * h[d];
            param[d][1] = param[d][0] + h[d] / 2;
            param[d][4] = param[d][3] = param[d][2] = param[d][1];
            param[d][5] = param[d][0] + h[d];
            x /= steps[d];
          }
          for (int j = 0; j < pow_6; j++) {
            x = j;
            for (int d = 0; d < dimen; d++) {
              args[d] = param[d][x % 6];
              x /= 6;
            }
            local_res += f(args);
          }
        }
        return local_res;
      },
      std::plus<double>());
  for (int i = 0; i < dimen; i++) {
    integral *= h[i] / 6.0;
  }
  return integral;
}
