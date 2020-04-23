#pragma once

#include "statistic.hpp"

#include <functional>
#include <cstdlib>
#include <vector>

class Distribution
{
public:
    Distribution() = default;

    void setInversedCumulativeFunction (std::function<double(double )> inversedCumulativeFunction);

    auto getValue(double x) const -> double;

    auto experiment(int count) const -> Statistic;

    ~Distribution() = default;

private:
    std::function<double(double )> m_inversedCumulativeFunction;
};