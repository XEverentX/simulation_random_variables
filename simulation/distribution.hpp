#pragma once

#include "statistic.hpp"

#include <functional>
#include <cstdlib>
#include <vector>

class Distribution
{
public:
    Distribution() = default;

    ~Distribution() = default;

    void setInversedCumulativeFunction (std::function<double(double )> inversedCumulativeFunction);

    [[nodiscard]] auto getValue(double x) const -> double;

    [[nodiscard]] auto experiment(int count) const -> Statistic;
private:
    std::function<double(double )> m_inversedCumulativeFunction;
};