#include "statistic.hpp"

Statistic::Statistic(int count)
        : m_count(count)
{
    // Empty constructor
}

Statistic::Statistic(int count, time_t seed)
        : m_count(count), m_seed(seed)
{
    // Empty constructor
}

void Statistic::setSeed(time_t seed)
{
    m_seed = seed;
}

void Statistic::setCount(int count)
{
    m_count = count;
}

void Statistic::addEvent(double event)
{
    m_events[event]++;
}

std::vector<double> Statistic::getEventsList() const
{
    std::vector<double> eventsList;
    for (auto x : m_events)
    {
        eventsList.push_back(x.first);
    }

    return eventsList;
}