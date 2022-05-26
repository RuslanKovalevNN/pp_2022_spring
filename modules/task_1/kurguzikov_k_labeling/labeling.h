// Copyright 2022 Kurguzikov Kirill
#ifndef MODULES_TASK_1_KURGUZIKOV_K_LABELING_LABELING_H_
#define MODULES_TASK_1_KURGUZIKOV_K_LABELING_LABELING_H_

#include <vector>


std::vector<uint32_t> getRandomBinaryImage(int height, int width);
inline std::vector<uint32_t> markComponentsBlock(
    std::vector<uint32_t> image, int height, int width, uint32_t curr = 1);
std::vector<uint32_t> markComponentsNotParall(std::vector<uint32_t> image, int height, int width);

inline std::vector<uint32_t> renumberComponents(std::vector<uint32_t> image, int height, int width);
inline std::vector<uint32_t> rotateImage(std::vector<uint32_t> image, int height, int width, bool clockwise);


#endif  // MODULES_TASK_1_KURGUZIKOV_K_LABELING_LABELING_H_
