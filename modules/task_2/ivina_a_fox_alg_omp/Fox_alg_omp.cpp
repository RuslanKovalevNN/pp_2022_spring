// Copyright 2022 Ivina Anastasiya
#include "../../../modules/task_2/ivina_a_fox_alg_omp/Fox_alg_omp.h"

#include <omp.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

Matrix FillMatrixRandom(const Matrix &m) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1000.0);
  Matrix matrix{m};
  if (matrix.size() > 0) {
    for (size_t i = 0; i < matrix.size(); i++) {
      for (size_t j = 0; j < matrix[0].size(); j++) {
        matrix[i][j] = dis(gen);
      }
    }
  } else {
    throw "Invalid matrix size";
  }

  return matrix;
}

void PrintMatrix(const Matrix &matrix) {
  const size_t row = matrix.size();
  const size_t col = matrix[0].size();
  for (size_t i = 0; i < row; i++) {
    for (size_t j = 0; j < col; j++) {
      std::cout << matrix[i][j] << std::setw(4) << "  ";
    }
    std::cout << std::endl;
  }
}

Matrix DenseMatrixMultiplication(const Matrix &a, const Matrix &b) {
  if (a[0].size() != b.size()) {
    throw "Matrices with different sizes cannot be multiplied";
  }
  const size_t row = a.size();
  const size_t col = b[0].size();
  Matrix c(row, MatrixRow(col, 0));

  for (size_t i = 0; i < row; i++) {
    for (size_t j = 0; j < col; j++) {
      for (size_t k = 0; k < a[0].size(); k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return c;
}

Matrix BlockMatrixMultiplication(const Matrix &a, const Matrix &b) {
  if (a.size() != b.size()) {
    throw "Matrices with different sizes cannot be multiplied";
  }
  const size_t row = a.size();
  const size_t col = b[0].size();
  Matrix c(row, MatrixRow(col, 0));
  const size_t block_size = std::sqrt(row);
  for (size_t ii = 0; ii < row; ii += block_size) {
    for (size_t jj = 0; jj < row; jj += block_size) {
      for (size_t i = 0; i < row; i++) {
        for (size_t j = ii;
             j < ((ii + block_size) > row ? row : (ii + block_size)); j++) {
          double temp = 0;
          for (size_t k = jj;
               k < ((jj + block_size) > row ? row : (jj + block_size)); k++) {
            temp += a[i][k] * b[k][j];
          }
          c[i][j] += temp;
        }
      }
    }
  }
  return c;
}

Matrix Fox(const Matrix &a, const Matrix &b, const size_t thread_num) {
  if (a.size() != b.size()) {
    throw "Matrices with different sizes cannot be multiplied";
  }

  const size_t MatrixSize = a.size();  // number of rows or coloumnt

  Matrix c(MatrixSize, MatrixRow(MatrixSize, 0));
  auto newA = a;
  auto newB = b;
  MatrixRow temp(MatrixSize, 0);

  auto process = [](const TasksForProcess &tasks, Matrix &newA,
                    const Matrix &newB, const int stage, Matrix &c,
                    MatrixRow &temp, const Matrix &a) {
    const int n = a.size();
    for (const auto coordinat : tasks) {
      int i = coordinat.i;
      int j = coordinat.j;
      int jj = (i + stage) % n;
      newA[i][j] = a[i][jj];
      c[i][j] += newA[i][j] * newB[i][j];
    }
  };

  auto process_B = [](const TasksForProcess &tasks, Matrix &newB,
                      MatrixRow &temp) {
    const auto n = newB.size();
    for (const auto coordinat : tasks) {
      const auto i = coordinat.i;
      const auto j = coordinat.j;

      if (i == 0) {
        temp[j] = newB[i][j];
        newB[i][j] = newB[i + 1][j];
      } else if (i == (n - 1)) {
        newB[i][j] = temp[j];
      } else {
        newB[i][j] = newB[i + 1][j];
      }
    }
  };

  const size_t ProcessNum = thread_num;  // number of process
  const size_t number_of_tasks = (MatrixSize * MatrixSize) / ProcessNum;

  TasksForManyProcesses tasks;
  for (size_t i = 0; i < MatrixSize; ++i) {
    for (size_t j = 0; j < MatrixSize; ++j) {
      Cij new_task{i, j};
      if (tasks.empty()) {
        TasksForProcess t{{new_task}};
        tasks.push_back(t);
      } else if (tasks.back().size() < number_of_tasks) {
        tasks.back().push_back(new_task);
      } else if (tasks.size() < ProcessNum) {
        TasksForProcess t{{new_task}};
        tasks.push_back(t);
      } else {
        tasks.back().push_back(new_task);
      }
    }
  }

  for (size_t stage = 0; stage < MatrixSize; stage++) {
#pragma omp parallel num_threads(thread_num) shared(c, newA, newB, temp, a, stage)
    {
      int tid = omp_get_thread_num();
      process(tasks[tid], newA, newB, stage, c, temp, a);

#pragma omp barrier
#pragma omp master
      {
        for (const auto task : tasks) {
          process_B(task, newB, temp);
        }
      }
    }
  }
  return c;
}
