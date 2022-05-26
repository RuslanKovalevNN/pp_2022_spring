// Copyright 2022 Samoiluk Anastasiya
#ifndef MODULES_TASK_4_SAMOILUK_A_VERT_GAUSSIAN_VERT_GAUSSIAN_H_
#define MODULES_TASK_4_SAMOILUK_A_VERT_GAUSSIAN_VERT_GAUSSIAN_H_
#define _USE_MATH_DEFINES

#include <vector>
#include<random>
#include<cmath>
#include <ctime>
#include "../../3rdparty/unapproved/unapproved.h"

std::vector<std::vector<double>> createGaussian();
std::vector<std::vector<int>> GaussianFilter_Seq(
    const std::vector<std::vector<int>> &sourceImg);
std::vector<std::vector<int>> GaussianFilter_Thread(
    const std::vector<std::vector<int>> &sourceImg);
int newPixelColor(const std::vector<std::vector<int>> &sourceImg,
    int x, int y, const std::vector<std::vector<double>> &kernel);
int checkValue(int value, int min, int max);
std::vector<std::vector<int>> getRandomImg(int width, int height);

template<class T>
bool imgEquivalent(const std::vector<std::vector<T>> &sourceImg,
    const std::vector<std::vector<T>> &resultImg) {
    int sourceW = sourceImg.size();
    int sourceH = sourceImg[0].size();
    int resultW = resultImg.size();
    int resultH = resultImg[0].size();

    if (sourceW != resultW || sourceH != resultH) return false;
    for (int i = 0; i < sourceW; i++) {
        for (int j = 0; j < sourceH; j++) {
            if (sourceImg[i][j] != resultImg[i][j])
                return false;
        }
    }
    return true;
}

#endif  // MODULES_TASK_4_SAMOILUK_A_VERT_GAUSSIAN_VERT_GAUSSIAN_H_

