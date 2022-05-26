  //  Copyright 2022 Kurguzikov Kirill


#include <gtest/gtest.h>
#include <vector>
#include"../../../modules/task_1/kurguzikov_k_labeling/labeling.h"



TEST(Sequential_Operations, Can_Generate_Binary_Image) {
    const int height = 20;
    const int width = 10;
    std::vector<uint32_t> image = getRandomBinaryImage(height, width);
    ASSERT_EQ(static_cast<int>(image.size()), height * width);
    for (int i = 0; i < height * width; i++) {
        ASSERT_LE(image[i], static_cast<uint32_t>(1));
        ASSERT_GE(image[i], static_cast<uint32_t>(0));
    }
}

TEST(Sequential_Operations, Test_Size_1x1) {
    const int height = 1;
    const int width = 1;

    std::vector<uint32_t> image;
    image = getRandomBinaryImage(height, width);
    ASSERT_NO_THROW(std::vector<uint32_t> resultImageNotParall =
        markComponentsNotParall(image, height, width));
}

TEST(Sequential_Operations, Test) {
    const int height = 5;
    const int width = 5;
    std::vector<uint32_t> img = {
        0, 0, 0, 0, 0,
        0, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 0, 0, 0
    };
    std::vector<uint32_t> expres = {
        0, 0, 0, 0, 0,
        0, 0, 0, 1, 0,
        0, 2, 2, 0, 0,
        0, 2, 0, 0, 0,
        0, 0, 0, 0, 0,
    };
    std::vector<uint32_t> res = markComponentsNotParall(img, height, width);
    ASSERT_EQ(expres, res);
}

TEST(Sequential_Operations, Test_Size_10x10) {
    const int height = 10;
    const int width = 10;

    std::vector<uint32_t> image;
    image = getRandomBinaryImage(height, width);
    ASSERT_NO_THROW(std::vector<uint32_t> resultImageNotParall = markComponentsNotParall(image, height, width));
}

TEST(Sequential_Operations, Test_Size_15x15) {
    const int height = 15;
    const int width = 15;

    std::vector<uint32_t> image;
    image = getRandomBinaryImage(height, width);
    ASSERT_NO_THROW(std::vector<uint32_t> resultImageNotParall = markComponentsNotParall(image, height, width));
}

TEST(Sequential_Operations, Test_Size_20x20) {
    const int height = 20;
    const int width = 20;

    std::vector<uint32_t> image;
    image = getRandomBinaryImage(height, width);
    ASSERT_NO_THROW(std::vector<uint32_t> resultImageNotParall = markComponentsNotParall(image, height, width));
}

TEST(Sequential_Operations, Test_Size_25x25) {
    const int height = 25;
    const int width = 25;

    std::vector<uint32_t> image;
    image = getRandomBinaryImage(height, width);
    ASSERT_NO_THROW(std::vector<uint32_t> resultImageNotParall = markComponentsNotParall(image, height, width));
}

TEST(Sequential_Operations, Test_Size_50x50) {
    const int height = 50;
    const int width = 50;

    std::vector<uint32_t> image;
    image = getRandomBinaryImage(height, width);
    ASSERT_NO_THROW(std::vector<uint32_t> resultImageNotParall = markComponentsNotParall(image, height, width));
}

TEST(Sequential_Operations, Test_Size_100x100) {
    const int height = 100;
    const int width = 100;

    std::vector<uint32_t> image;
    image = getRandomBinaryImage(height, width);
    ASSERT_NO_THROW(std::vector<uint32_t> resultImageNotParall = markComponentsNotParall(image, height, width));
}



int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
