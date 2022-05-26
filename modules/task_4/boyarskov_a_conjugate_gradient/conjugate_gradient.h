// Copyright 2022 Boyarskov Anton
#ifndef MODULES_TASK_4_BOYARSKOV_A_CONJUGATE_GRADIENT_CONJUGATE_GRADIENT_H_
#define MODULES_TASK_4_BOYARSKOV_A_CONJUGATE_GRADIENT_CONJUGATE_GRADIENT_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

const double NEARZERO = 1.0e-10;  // interpretation of "zero"

using vec = std::vector<double>;  // vector
using matrix = std::vector<vec>;  // matrix (=collection of (row) vectors)

// Prototypes
vec generateRandomVector(int size);
matrix generateMatrix(vec v);
void print(const std::string& title, const vec& V);
void print(const std::string& title, const matrix& A);
void printError(const vec& B, const vec& check, int n);
double scalarProduct(const vec& V, const vec& U);
vec matrixTimesVector(const matrix& A, const vec& V);
vec conjugateGradientSolver(const matrix& A, const vec& V);
vec conjugateGradientSolverParallel(const matrix& A, const vec& V);

#endif  // MODULES_TASK_4_BOYARSKOV_A_CONJUGATE_GRADIENT_CONJUGATE_GRADIENT_H_
