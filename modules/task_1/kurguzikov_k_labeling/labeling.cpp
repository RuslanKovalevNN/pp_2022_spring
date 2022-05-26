// Copyright 2022 Kurguzikov Kirill

#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/kurguzikov_k_labeling/labeling.h"



std::vector<uint32_t> getRandomBinaryImage(int height, int width) {
    if (height < 1 || width < 1) {
        throw "height or width < 1 error";
    }

    std::mt19937 gen;
    gen.seed(time(0));

    std::vector<uint32_t> image(height * width);
    for (int i = 0; i < height * width; ++i)
        image[i] = gen() % 2;

    return image;
}

inline std::vector<uint32_t> markComponentsBlock(std::vector<uint32_t> image, int height, int width, uint32_t curr) {
        int elemBColumn = 0;
        int elemCRow = 0;
        uint32_t A, B, C;
        for (int row = 0; row < height; ++row) {
            for (int column = 0; column < width; ++column) {
                elemCRow = column - 1;
                if (elemCRow < 0) {
                    elemCRow = 0;
                    B = 0;
                } else {
                    B = image[row * width + elemCRow];
                }
                elemBColumn = row - 1;
                if (elemBColumn < 0) {
                    elemBColumn = 0;
                    C = 0;
                } else {
                    C = image[elemBColumn * width + column];
                }
                A = image[row * width + column];
                if (A == 0) {
                } else if (B == 0 && C == 0) {
                    ++curr;
                    image[row * width + column] = curr;
                } else if (B != 0 && C == 0) {
                    image[row * width + column] = B;
                } else if (B == 0 && C != 0) {
                    image[row * width + column] = C;
                } else if (B != 0 && C != 0) {
                    if (B == C) {
                        image[row * width + column] = B;
                    } else {
                        image[row * width + column] = B;
                        for (int i = 0; i < height; ++i) {
                            for (int j = 0; j < width; ++j) {
                                if (image[i * width + j] == C) {
                                    image[i * width + j] = B;
                                }
                            }
                        }
                    }
                }
            }
        }
        return image;
}
inline std::vector<uint32_t> renumberComponents(std::vector<uint32_t> image, int height, int width) {
    std::vector<uint32_t> source = std::vector<uint32_t>();
    std::vector<uint32_t> result = std::vector<uint32_t>();

    int count = 0;
    int size = height * width;

    for (int i = 0; i < size; ++i) {
        if (image[i] != 0 && std::find(source.begin(), source.end(), image[i]) == source.end()) {
            source.push_back(image[i]);
            ++count;
            result.push_back(count);
        }
    }
    for (int i = 0; i < size; ++i) {
        if (image[i] != 0) {
            image[i] = result[std::distance(source.begin(), std::find(source.begin(), source.end(), image[i]))];
        }
    }
    return image;
}
inline std::vector<uint32_t> rotateImage(std::vector<uint32_t> image, int height, int width, bool clockwise) {
    std::vector<uint32_t> rotatedImage(height * width);
    if (clockwise) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                rotatedImage[j * height + height - 1 - i] = image[i * width + j];
            }
        }
    } else {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                rotatedImage[(width - j - 1) * height + i] = image[i * width + j];
            }
        }
    }
    return rotatedImage;
}
std::vector<uint32_t> markComponentsNotParall(std::vector<uint32_t> image, int height, int width) {
    image = markComponentsBlock(image, height, width);
    image = renumberComponents(image, height, width);
    return image;
}
