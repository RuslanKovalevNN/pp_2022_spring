// Copyright 2022 Samoiluk Anastasiya
#include "../../../modules/task_4/samoiluk_a_vert_gaussian/vert_gaussian.h"

const int min_pix = 0;
const int max_pix = 255;
const int radius = 1;
const double sigma = 1.0;

std::vector<std::vector<double>> createGaussian() {
    int size = 2 * radius + 1;
    std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
    double norm = 0;

    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++) {
            kernel[i + radius][j + radius] =
                exp(-(i * i + j * j) / (2 * sigma * sigma))
                / (2 * M_PI * sigma * sigma);
            norm += kernel[i + radius][j + radius];
        }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            kernel[i][j] /= norm;
    return kernel;
}

std::vector<std::vector<int>> GaussianFilter_Seq(
    const std::vector<std::vector<int>> &sourceImg) {
    std::vector<std::vector<int>> resultImg(sourceImg.size(),
        std::vector<int>(sourceImg[0].size()));

    std::vector<std::vector<double>> kernel = createGaussian();

    for (std::vector<int>::size_type i = 0; i < sourceImg.size(); i++) {
        for (std::vector<int>::size_type j = 0; j < sourceImg[0].size(); j++) {
            resultImg[i][j] = newPixelColor(sourceImg, i, j, kernel);
        }
    }
    return resultImg;
}

std::vector<std::vector<int>> GaussianFilter_Thread(
    const std::vector<std::vector<int>> &sourceImg) {
    std::vector<std::vector<int>> resultImg(sourceImg.size(),
        std::vector<int>(sourceImg[0].size()));

    std::vector<std::vector<double>> kernel = createGaussian();

    int thread_num = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(thread_num);

    int start, finish;
    int size = sourceImg[0].size() / thread_num;
    int rem = sourceImg[0].size() % thread_num;
    for (int i = 0; i < thread_num; i++) {
        start = i * size;
        finish = start + size;
        if (i == thread_num - 1) {
            finish += rem;
        }
        threads[i] = std::thread(
            [&](int start, int finish) {
                for (int j = start; j < finish; j++) {
                    for (std::vector<int>::size_type i = 0;
                            i < sourceImg.size(); i++) {
                        resultImg[i][j] =
                            newPixelColor(sourceImg, i, j, kernel);
                    }
                }
            }, start, finish);
    }

    for (int i = 0; i < thread_num; i++) {
        threads[i].join();
    }

    return resultImg;
}

int newPixelColor(const std::vector<std::vector<int>> &sourceImg, int x,
    int y, const std::vector<std::vector<double>> &kernel) {
    double result = 0;
    int width = sourceImg.size();
    int height = sourceImg[0].size();
    for (int j = -radius; j <= radius; j++)
        for (int i = -radius; i <= radius; i++) {
            int idX = checkValue(x + i, 0, width - 1);
            int idY = checkValue(y + j, 0, height - 1);
            int neighborColor = sourceImg[idX][idY];
            result += neighborColor * kernel[i + radius][j + radius];
        }
    return checkValue(static_cast<int>(result), min_pix, max_pix);
}

int checkValue(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

std::vector<std::vector<int>> getRandomImg(int width, int height) {
    if (width < 1 || height < 1)
        throw "Wrong size";
    std::vector<std::vector<int>> matrix(width, std::vector<int>(height));
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++)
            matrix[i][j] = static_cast<int>(gen() % max_pix);
    }
    return matrix;
}
