// Copyright 2022 Zaitsev Alexander
#include "../../../modules/task_3/zaitsev_a_matrix_cannon_block_mult_tbb/matrix.h"

// zaitsev_a_matrix_cannon_block_mult_omp.h
std::vector<std::vector<double>> get_Matrix(double number, size_t size) {
  std::vector<std::vector<double>> matrix(size, std::vector<double>(size));
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      matrix[i][j] = i * number;
    }
  }
  return matrix;
}

void shift_to_Left(std::vector<std::vector<double>> *matrix, size_t position,
                   size_t count_of_block, size_t size_of_block) {
  std::vector<std::vector<double>> tmp_matrix(
      size_of_block, std::vector<double>(size_of_block));

  for (size_t i = 0; i < size_of_block; ++i) {
    for (size_t j = 0; j < size_of_block; ++j) {
      tmp_matrix[i][j] = matrix->at(i + size_of_block * position).at(j);
    }
  }
  for (size_t k = 0; k < count_of_block - 1; ++k) {
    for (size_t i = 0; i < size_of_block; ++i) {
      for (size_t j = 0; j < size_of_block; ++j) {
        matrix->at(i + size_of_block * position).at(j + size_of_block * k) =
            matrix->at(i + size_of_block * position)
                .at(j + size_of_block * (k + 1));
      }
    }
  }
  for (size_t i = 0; i < size_of_block; ++i) {
    for (size_t j = 0; j < size_of_block; ++j) {
      matrix->at(i + size_of_block * position)
          .at(j + size_of_block * (count_of_block - 1)) = tmp_matrix[i][j];
    }
  }
}

void shift_to_Up(std::vector<std::vector<double>> *matrix, size_t position,
                 size_t count_of_block, size_t size_of_block) {
  std::vector<std::vector<double>> tmp_matrix(
      size_of_block, std::vector<double>(size_of_block));

  for (size_t i = 0; i < size_of_block; ++i) {
    for (size_t j = 0; j < size_of_block; ++j) {
      tmp_matrix[i][j] = matrix->at(i).at(j + size_of_block * position);
    }
  }
  for (size_t i = 0; i < count_of_block - 1; ++i) {
    for (size_t j = 0; j < size_of_block; ++j) {
      for (size_t k = 0; k < size_of_block; ++k) {
        matrix->at(j + size_of_block * i).at(k + size_of_block * position) =
            matrix->at(j + size_of_block * (i + 1))
                .at(k + size_of_block * position);
      }
    }
  }
  for (size_t i = 0; i < size_of_block; ++i) {
    for (size_t j = 0; j < size_of_block; ++j) {
      matrix->at(i + size_of_block * (count_of_block - 1))
          .at(j + size_of_block * position) = tmp_matrix[i][j];
    }
  }
}

void multiply_to_Block(std::vector<std::vector<double>> first_block,
                       std::vector<std::vector<double>> second_block,
                       std::vector<std::vector<double>> res_block,
                       size_t shift_l, size_t shift_r, size_t size_of_block) {
  for (size_t i = 0; i < size_of_block; i++)
    for (size_t j = 0; j < size_of_block; j++)
      for (size_t k = 0; k < size_of_block; k++)
        res_block[i + size_of_block * shift_l][j + size_of_block * shift_r] +=
            first_block[i + size_of_block * shift_l]
                       [size_of_block * shift_r + k] *
            second_block[k + size_of_block * shift_l]
                        [j + size_of_block * shift_r];
}

std::vector<std::vector<double>> cannon_mult_alg_Seq(
    std::vector<std::vector<double>> first_multiplier,
    std::vector<std::vector<double>> second_multiplier, size_t size_of_block,
    size_t count_of_block, size_t size) {
  std::vector<std::vector<double>> composition(size,
                                               std::vector<double>(size, 0.0));
  for (size_t i = 1; i < count_of_block; ++i) {
    for (size_t j = 0; j < i; ++j) {
      shift_to_Left(&first_multiplier, i, count_of_block, size_of_block);
      shift_to_Up(&second_multiplier, i, count_of_block, size_of_block);
    }
  }
  for (size_t i = 0; i < count_of_block; ++i) {
    for (size_t j = 0; j < count_of_block; ++j) {
      for (size_t k = 0; k < count_of_block; ++k) {
        multiply_to_Block(first_multiplier, second_multiplier, composition, j,
                          k, size_of_block);
      }
    }
    for (size_t l = 0; l < count_of_block; ++l) {
      shift_to_Left(&first_multiplier, l, count_of_block, size_of_block);
      shift_to_Up(&second_multiplier, l, count_of_block, size_of_block);
    }
  }
  return composition;
}

std::vector<std::vector<double>> cannon_mult_alg_TBB(
    std::vector<std::vector<double>> first_multiplier,
    std::vector<std::vector<double>> second_multiplier, size_t size_of_block,
    size_t count_of_block, size_t size) {
  std::vector<std::vector<double>> composition(size,
                                               std::vector<double>(size, 0.0));
  tbb::parallel_for(
      tbb::blocked_range<size_t>(1, count_of_block),
      [&](const tbb::blocked_range<size_t> &range) {
        for (size_t i = 1; i < count_of_block; ++i) {
          for (size_t j = 0; j < i; ++j) {
            shift_to_Left(&first_multiplier, i, count_of_block, size_of_block);
            shift_to_Up(&second_multiplier, i, count_of_block, size_of_block);
          }
        }
      });
  for (size_t i = 0; i < count_of_block; ++i) {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, count_of_block),
                      [&](const tbb::blocked_range<size_t> &range) {
                        for (size_t j = 0; j < count_of_block; ++j) {
                          for (size_t k = 0; k < count_of_block; ++k) {
                            multiply_to_Block(first_multiplier,
                                              second_multiplier, composition, j,
                                              k, size_of_block);
                          }
                        }
                      });
    tbb::parallel_for(
        tbb::blocked_range<size_t>(0, count_of_block),
        [&](const tbb::blocked_range<size_t> &range) {
          for (size_t l = 0; l < count_of_block; ++l) {
            shift_to_Left(&first_multiplier, l, count_of_block, size_of_block);
            shift_to_Up(&second_multiplier, l, count_of_block, size_of_block);
          }
        });
  }
  return composition;
}
