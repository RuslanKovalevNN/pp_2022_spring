// Copyright 2022 Lebedev Alexey
#include <gtest/gtest.h>
#include <tbb/tick_count.h>
#include <random>
#include <iostream>
#include "./convex_hull.h"



template<class T>
double get_time(T input, std::vector<cv::Point2d>* output, lab3::Version v) {
    auto t1 = tbb::tick_count::now();
    lab3::convex_hull(input, output, v);
    auto t2 = tbb::tick_count::now();
    return (t2 - t1).seconds();
}


// image parameters
static const cv::Size2d image_size(1080, 1080);
static const cv::Scalar background_color(0);
static const cv::Scalar fill_color(255);

// visual parameters
static const size_t separation_width = 10;
static const cv::Mat separation(cv::Size2d(separation_width, image_size.height), CV_8UC1, fill_color);


class ConvexHullTEST : public ::testing::Test {
 protected:
    cv::Mat test_image;
    std::vector<cv::Point2d> conv;
    std::string test_name;

    // check v against Version::PARALLEL
    void check_time(lab3::Version v) {
        double t_seq = get_time(test_image, &conv, v);
        double t_parallel = get_time(test_image, &conv, lab3::Version::PARALLEL);
        std::cout << "Speed up " << t_seq / t_parallel << std::endl;
    }

    void SetUp() override {
        test_image = cv::Mat(image_size, CV_8UC1, background_color);
        test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    }
    void TearDown() override {
        auto convex_hull = test_image.clone();
        for (size_t i = 0; i < conv.size(); ++i) {
            cv::circle(convex_hull, conv[i], 2, fill_color, -1);
            if (i < conv.size() - 1) {
                cv::line(convex_hull, conv[i], conv[i + 1], fill_color);
            } else {
                cv::line(convex_hull, conv.front(), conv.back(), fill_color);
            }
        }
        cv::Mat output;
        std::vector<cv::Mat> src = { test_image, separation, convex_hull };
        cv::hconcat(src, output);
        cv::imwrite("images/" + test_name + ".png", output);
    }
};


void fill_image_random_uniform(cv::Mat* c1_image, const std::vector<size_t>& roi, size_t num_points) {
    if (roi.size() != 4) {
        throw std::logic_error("Incorrect ROI vector!");
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> w_dist(roi[0], roi[1]);
    std::uniform_int_distribution<size_t> h_dist(roi[2], roi[3]);
    for (size_t i = 0; i < num_points; ++i) {
        cv::Point2d rand_pix(w_dist(gen), h_dist(gen));
        c1_image->at<uint8_t>(rand_pix) = 255;
    }
}


void fill_points_random_uniform(std::vector<cv::Point2d>* input, size_t num_points, const std::vector<size_t>& roi) {
    if (roi.size() != 4) {
        throw std::logic_error("Incorrect ROI vector!");
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> w_dist(roi[0], roi[1]);
    std::uniform_int_distribution<size_t> h_dist(roi[2], roi[3]);
    input->clear();
    input->resize(num_points);
    for (size_t i = 0; i < num_points; ++i) {
        cv::Point2d p(w_dist(gen), h_dist(gen));
        input->push_back(p);
    }
}


TEST_F(ConvexHullTEST, Test_parallel_vs_sequential) {
    fill_image_random_uniform(&test_image, { 10, 1070, 10, 1070 }, 1000);
    check_time(lab3::Version::SEQUENTIAL);
}

TEST_F(ConvexHullTEST, Test_parallel_vs_parallel_one_thread) {
    fill_image_random_uniform(&test_image, { 10, 1070, 10, 1070 }, 1000);
    check_time(lab3::Version::PARALLEL_ONE_THREAD);
}

TEST_F(ConvexHullTEST, Test_several_ranges) {
    fill_image_random_uniform(&test_image, { 100, 300, 100, 300 }, 300);
    fill_image_random_uniform(&test_image, { 400, 600, 100, 300 }, 300);
    fill_image_random_uniform(&test_image, { 400, 600, 300, 700 }, 600);
    fill_image_random_uniform(&test_image, { 50, 400, 500, 1000 }, 200);
    fill_image_random_uniform(&test_image, { 500, 1000, 500, 1000 }, 200);
    check_time(lab3::Version::PARALLEL_ONE_THREAD);
}

TEST_F(ConvexHullTEST, Test_small_polygon) {
    std::vector<cv::Point2d> vertexes{ {100, 200}, {100, 300}, {200, 500}, {300, 500},
                                       {400, 300}, {400, 200}, {300, 100}, {200, 100} };
    for (const auto& v : vertexes) {
        test_image.at<uint8_t>(v) = 255;
    }
    lab3::convex_hull(test_image, &conv);
    ASSERT_EQ(vertexes, conv);
}

TEST_F(ConvexHullTEST, Test_empty) {
    lab3::convex_hull(test_image, &conv);
    ASSERT_TRUE(conv.empty());
}


TEST(TEST_POINTS_ONLY, Test_time) {
    std::vector<cv::Point2d> input;
    fill_points_random_uniform(&input, 1000, {0, 2000, 0, 2000});
    std::vector<cv::Point2d> input_ref(input);
    std::vector<cv::Point2d> output, output_ref;
    double t_seq = get_time(&input, &output, lab3::Version::PARALLEL_ONE_THREAD);
    double t_parallel = get_time(&input_ref, &output_ref, lab3::Version::PARALLEL);
    std::cout << "Speed up: " << t_seq / t_parallel << std::endl;
    ASSERT_EQ(output, output_ref);
}
