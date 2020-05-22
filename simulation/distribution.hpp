// Copyright Lebedev Alexander 2020
#pragma once

#include "statistic.hpp"

#include <functional>
#include <cstdlib>
#include <vector>

class Distribution
{
    friend class Experement;
public:
    Distribution() = default;

    ~Distribution() = default;

    void setInversedCumulativeFunction (std::function<double(double )> inversedCumulativeFunction);

    void setCumulativeFunction (std::function<double(double )> cumulativeFunction);

    [[nodiscard]] auto getValue(double x) const -> double;

    [[nodiscard]] auto experiment(int count) const -> Statistic;
private:
    std::function<double(double )> m_inversedCumulativeFunction;
    std::function<double(double )> m_cumulativeFunction;
};