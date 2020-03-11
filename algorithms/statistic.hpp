#pragma once

#include <vector>
#include <ctime>
#include <map>
class Statistic {
public:
    Statistic(int count = 0);

    Statistic(int count, time_t seed);

    void setSeed(time_t seed);

    void setCount(int count);

    void addEvent(double event);

    std::vector<double> getEventsList() const;

private:
    std::map<double, int> m_events;
    time_t                m_seed;
    int                   m_count;
};