// Copyright 2022 Lebedev Alexey
#include <gtest/gtest.h>
#include <random>
#include "./convex_hull.h"


// image parameters
static const cv::Size2d image_size(720, 720);
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


TEST_F(ConvexHullTEST, Test_uniform_dist_2_objects) {
    fill_image_random_uniform(&test_image, { 100, 300, 500, 600 }, 100);
    fill_image_random_uniform(&test_image, { 500, 600, 100, 400 }, 100);
    lab1::convex_hull(test_image, &conv);
}

TEST_F(ConvexHullTEST, Test_uniform_dist_3_objects) {
    fill_image_random_uniform(&test_image, { 100, 300, 500, 600 }, 100);
    fill_image_random_uniform(&test_image, { 400, 500, 200, 300 }, 100);
    fill_image_random_uniform(&test_image, { 500, 600, 100, 400 }, 100);
    lab1::convex_hull(test_image, &conv);
}

TEST_F(ConvexHullTEST, Test_polygon) {
    std::vector<cv::Point2d> vertexes{ {100, 200}, {100, 300}, {200, 500}, {300, 500},
                                       {400, 300}, {400, 200}, {300, 100}, {200, 100} };
    for (const auto& v : vertexes) {
        test_image.at<uint8_t>(v) = 255;
    }
    lab1::convex_hull(test_image, &conv);
    ASSERT_EQ(vertexes, conv);
}

TEST_F(ConvexHullTEST, Test_line) {
    std::vector<cv::Point2d> vertexes{ {100, 300}, {200, 300}, {300, 300}, {400, 300} };
    for (const auto& v : vertexes) {
        test_image.at<uint8_t>(v) = 255;
    }
    lab1::convex_hull(test_image, &conv);
    std::vector<cv::Point2d> expected = { vertexes.front(), vertexes.back() };
    ASSERT_EQ(expected, conv);
}

TEST_F(ConvexHullTEST, Test_empty) {
    lab1::convex_hull(test_image, &conv);
    ASSERT_TRUE(conv.empty());
}
