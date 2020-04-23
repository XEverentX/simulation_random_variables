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

Statistic::Statistic(Statistic &&other)
{
    m_count  = other.m_count;
    m_events = other.m_events;
    m_seed   = other.m_seed;

    other.m_count = 0;
    other.m_seed  = 0;
    other.m_events.clear();
}

void Statistic::setSeed(time_t seed) noexcept
{
    m_seed = seed;
}

void Statistic::setCount(int count) noexcept
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