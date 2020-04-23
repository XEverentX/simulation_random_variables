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

    void setSeed(time_t seed) noexcept;

    void setCount(int count) noexcept;

    void addEvent(double event);

    [[nodiscard]] std::vector<double> getEventsList() const;

    ~Statistic() = default;
protected:
    std::map<double, int> m_events;
    time_t                m_seed;
    int                   m_count;
};