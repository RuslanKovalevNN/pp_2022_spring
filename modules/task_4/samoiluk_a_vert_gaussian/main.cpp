// Copyright 2022 Samoiluk Anastasiya
#include <gtest/gtest.h>
#include "./vert_gaussian.h"

TEST(Gaussian, can_create_matrix) {
    std::vector<std::vector<int>> img;

    ASSERT_NO_THROW(img = getRandomImg(10, 10));
}

TEST(Gaussian, cant_create_matrix_with_wrong_size) {
    std::vector<std::vector<int>> img;

    ASSERT_ANY_THROW(img = getRandomImg(0, 20));
    ASSERT_ANY_THROW(img = getRandomImg(15, 0));
    ASSERT_ANY_THROW(img = getRandomImg(-5, -5));
}

TEST(Gaussian, can_create_kernel) {
    std::vector<std::vector<double>> sourceKernel =
    { { 0.075113607954111511, 0.12384140315297398, 0.075113607954111511 },
      { 0.12384140315297398, 0.20417995557165811,  0.12384140315297398 },
      { 0.075113607954111511, 0.12384140315297398, 0.075113607954111511 } };

    std::vector<std::vector<double>> kernel = createGaussian();

    EXPECT_TRUE(imgEquivalent(sourceKernel, kernel));
}

TEST(Gaussian, can_process_image_1) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(10, 10);

    clock_t t_start;
    double dt_1, dt_2;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = (clock() - t_start) / 1000.0;
    std::cout << "Sequential time = " << dt_1 << std::endl;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_par =
        GaussianFilter_Thread(sourceImg);
    dt_2 = (clock() - t_start) / 1000.0;
    std::cout << "Parallel time = " << dt_2 << std::endl;

    std::cout << "eff = " << dt_1 / dt_2;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_2) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(20, 20);

    clock_t t_start;
    double dt_1, dt_2;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = (clock() - t_start) / 1000.0;
    std::cout << "Sequential time = " << dt_1 << std::endl;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_par =
        GaussianFilter_Thread(sourceImg);
    dt_2 = (clock() - t_start) / 1000.0;
    std::cout << "Parallel time = " << dt_2 << std::endl;

    std::cout << "eff = " << dt_1 / dt_2;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_3) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(30, 30);

    clock_t t_start;
    double dt_1, dt_2;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = (clock() - t_start) / 1000.0;
    std::cout << "Sequential time = " << dt_1 << std::endl;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_par =
        GaussianFilter_Thread(sourceImg);
    dt_2 = (clock() - t_start) / 1000.0;
    std::cout << "Parallel time = " << dt_2 << std::endl;

    std::cout << "eff = " << dt_1 / dt_2;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_4) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(40, 40);

    clock_t t_start;
    double dt_1, dt_2;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = (clock() - t_start) / 1000.0;
    std::cout << "Sequential time = " << dt_1 << std::endl;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_par =
        GaussianFilter_Thread(sourceImg);
    dt_2 = (clock() - t_start) / 1000.0;
    std::cout << "Parallel time = " << dt_2 << std::endl;

    std::cout << "eff = " << dt_1 / dt_2;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_5) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(100, 100);

    clock_t t_start;
    double dt_1, dt_2;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = (clock() - t_start) / 1000.0;
    std::cout << "Sequential time = " << dt_1 << std::endl;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_par =
        GaussianFilter_Thread(sourceImg);
    dt_2 = (clock() - t_start) / 1000.0;
    std::cout << "Parallel time = " << dt_2 << std::endl;

    std::cout << "eff = " << dt_1 / dt_2;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, can_process_image_6) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(50, 100);

    clock_t t_start;
    double dt_1, dt_2;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = (clock() - t_start) / 1000.0;
    std::cout << "Sequential time = " << dt_1 << std::endl;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_par =
        GaussianFilter_Thread(sourceImg);
    dt_2 = (clock() - t_start) / 1000.0;
    std::cout << "Parallel time = " << dt_2 << std::endl;

    std::cout << "eff = " << dt_1 / dt_2;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

TEST(Gaussian, big_image_1000x1000) {
    std::vector<std::vector<int>> sourceImg = getRandomImg(1000, 1000);

    clock_t t_start;
    double dt_1, dt_2;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_seq = GaussianFilter_Seq(sourceImg);
    dt_1 = (clock() - t_start) / 1000.0;
    std::cout << "Sequential time = " << dt_1 << std::endl;

    t_start = clock();
    std::vector<std::vector<int>> resultImg_par =
        GaussianFilter_Thread(sourceImg);
    dt_2 = (clock() - t_start) / 1000.0;
    std::cout << "Parallel time = " << dt_2 << std::endl;

    std::cout << "eff = " << dt_1 / dt_2;

    EXPECT_TRUE(imgEquivalent(resultImg_seq, resultImg_par));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
