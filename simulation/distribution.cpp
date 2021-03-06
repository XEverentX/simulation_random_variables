// Copyright Lebedev Alexander 2020
#include "distribution.hpp"

void Distribution::setInversedCumulativeFunction(std::function<double(double )> inversedCumulativeFunction)
{
    m_inversedCumulativeFunction = inversedCumulativeFunction;
}

void Distribution::setCumulativeFunction(std::function<double(double )> cumulativeFunction)
{
    m_cumulativeFunction = cumulativeFunction;
}

auto Distribution::getValue(double x) const -> double
{
    return m_inversedCumulativeFunction(x);
}

auto Distribution::experiment(int count) const -> Statistic
{
    time_t seed = time(0);
    srand(static_cast<uint32_t>(seed));

    Statistic statistic(count, seed);

    for (int i = 0; i < count; i++)
    {
        auto uniformEvent = static_cast<double>(rand()) / RAND_MAX;
        auto mappedEvent = m_inversedCumulativeFunction(uniformEvent);

        statistic.addEvent(mappedEvent);
    }

    return statistic;
}