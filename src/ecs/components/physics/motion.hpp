#pragma once

#include <utility>

struct Motion {
    std::pair<double, double> position;
    std::pair<double, double> velocity;
    std::pair<double, double> acceleration;
};