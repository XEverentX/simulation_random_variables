// Copyright Lebedev Alexander 2020
#pragma once

#include <vector>
#include <ctime>
#include <map>
class Statistic final
{
public:
    Statistic(int count = 0);

    Statistic(int count, time_t seed);

    Statistic(Statistic &other) = default;

    Statistic(Statistic &&other);

    ~Statistic() = default;

    void setSeed(time_t seed) noexcept;

    void setCount(int count) noexcept;

    void addEvent(double event);

    [[nodiscard]] std::vector<double> getEventsList(const bool shouldBeSorted = true) const;
protected:
    std::vector<double> m_events;
    time_t              m_seed;
    int                 m_count;
};