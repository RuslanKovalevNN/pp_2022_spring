// Copyright 2022 Lebedev Alexey
#ifndef MODULES_TASK_2_LEBEDEV_A_CONVEX_HULL_UTILS_H_
#define MODULES_TASK_2_LEBEDEV_A_CONVEX_HULL_UTILS_H_


#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>


#define CV_8UC1 0

namespace lab2 {
namespace image_utils {
struct Point2d {
    double x, y;
    Point2d() : x(0.), y(0.) {}
    Point2d(double _x, double _y) : x(_x), y(_y) {}
    bool operator == (const Point2d& p) const {
        return x == p.x && y == p.y;
    }
};

struct Size2d {
    size_t width, height;
    Size2d() : width(0), height(0) {}
    Size2d(size_t _width, size_t _height) : width(_width), height(_height) {}
};

struct Scalar {
    uint8_t value;
    Scalar() = default;
    explicit Scalar(uint8_t _value) : value(_value) {}
};

class Mat {
 private:
     Size2d _size;
     std::shared_ptr<std::vector<uint8_t>> _data;

 public:
     Mat() {}
     Mat(const Size2d& size, int type, const Scalar& s) : _size(size),
         _data(std::make_shared<std::vector<uint8_t>>(size.height* size.width, s.value)) {}

     Mat& operator=(const Mat& other) {
         if (this == &other) {
             return *this;
         }
         this->_data = other._data;
         this->_size = other._size;
         return *this;
     }

     template<typename T>
     uint8_t& at(const Point2d& p) {
         if (p.y >= _size.height || p.x >= _size.width) {
             throw std::out_of_range("Incorrect coorinates!");
         }
         return _data->at(_size.width * p.y + p.x);
     }

     template<typename T>
     const uint8_t& at(const Point2d& p) const {
         if (p.y >= _size.height || p.x >= _size.width) {
             throw std::out_of_range("Incorrect coorinates!");
         }
         return _data->at(_size.width * p.y + p.x);
     }

     Size2d size() const {
         return _size;
     }

     Mat clone() const {
         Mat cloned(_size, 0, Scalar(0));
         std::copy(_data->begin(), _data->end(), cloned._data->begin());
         return cloned;
     }
};

inline void findNonZero(const Mat& mat, const std::vector<Point2d>& output) {
    const_cast<std::vector<Point2d>&>(output).clear();
    for (size_t i = 0; i < mat.size().width; i++) {
        for (size_t j = 0; j < mat.size().height; j++) {
            Point2d p(i, j);
            if (mat.at<uint8_t>(p)) {
                const_cast<std::vector<Point2d>&>(output).push_back(p);
            }
        }
    }
}

inline void circle(const Mat& mat, const Point2d& p, size_t rad, const Scalar& color, int thickness = 1) {
    // not implemented
}

inline void line(const Mat& mat, const Point2d& begin, const Point2d& end, const Scalar& color) {
    // not implemented
}

inline void hconcat(const std::vector<Mat>& src, const Mat& output) {
    // not implemented
}

inline void imwrite(const std::string& file_name, const Mat& mat) {
    // not implemented
}

}  // namespace image_utils
};  // namespace lab2


#endif  // MODULES_TASK_2_LEBEDEV_A_CONVEX_HULL_UTILS_H_
