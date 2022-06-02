// Copyright 2022 Zarubin Mikhail

#include <random>
#include "../../../modules/task_1/zarubin_m_simpson_method/simpson_method.h"

struct Partition {
    double left;
    double center;
    double right;

    Partition() = default;
    Partition(double _left, double _center, double _right) :
        left(_left),
        center(_center),
        right(_right)
    {};
};

double simpsonMethod(sizeType dimension,
    std::vector<double> leftBorders, std::vector<double> rightBorders,
    std::function<double(std::vector<double>)> function, std::vector<sizeType> countParts) {
    std::vector<double> coeffs(dimension);
    sizeType iterCount = 1;

    for (sizeType i = 0; i < dimension; i++) {
        coeffs[i] = (rightBorders[i] - leftBorders[i]) / countParts[i];
        iterCount *= countParts[i];
    }

    double integralValue = 0.0;
    sizeType count = static_cast<sizeType>(std::pow(6, dimension));
    std::vector<Partition> partitions(dimension);
    std::vector<double> args(dimension);

    for (sizeType i = 0; i < iterCount; i++) {
        sizeType temp = i;
        for (sizeType j = 0; j < dimension; j++) {
            double left = leftBorders[j] + temp % countParts[j] * coeffs[j];
            double right = leftBorders[j] + temp % countParts[j] * coeffs[j] + coeffs[j];
            double center = (right + left) / 2;

            partitions[j] = Partition(left, center, right);

            temp /= countParts[j];
        }

        for (sizeType k = 0; k < count; k++) {
            temp = k;

            for (sizeType j = 0; j < dimension; j++) {
                switch (temp % 6) {
                case 1:
                    args[j] = partitions[j].right; break;
                case 5:
                    args[j] = partitions[j].left; break;
                default:
                    args[j] = partitions[j].center; break;
                }

                temp /= 6;
            }

            integralValue += function(args);
        }
    }

    for (sizeType i = 0; i < dimension; i++) {
        integralValue *= (coeffs[i] / 6);
    }

    return integralValue;
}
