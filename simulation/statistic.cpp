// Copyright Lebedev Alexander 2020
#include <algorithm>

#include "statistic.hpp"
#include <utils.hpp>

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

void Statistic::setParameters(double alpha, double lambda)
{
    m_alpha  = alpha;
    m_lambda = lambda;
}

void Statistic::addEvent(double event)
{
    m_events.push_back(event);
}

std::vector<double> Statistic::getEventsList(const bool shouldBeSorted) const
{
    if (shouldBeSorted)
    {
        auto result = m_events;
        std::sort(result.begin(), result.end());
        
        return result;
    }
    return m_events;
}

void inline Statistic::calcSampleMean()
{
    m_sampleMean = 0.;
    
    for (auto x : m_events)
    {
        m_sampleMean += x;
    }
    m_sampleMean /= m_count;
}

void inline Statistic::calcSampleDispersion()
{
    m_sampleDispersion = 0.;

    for (auto x : m_events)
    {
        m_sampleDispersion += util::sqr(x - m_sampleMean);
    }
    m_sampleDispersion /= m_count;
}

void inline Statistic::calcScale()
{
    m_scale = m_events[m_count - 1] - m_events[0];
}

void inline Statistic::calcSampleMedian()
{
    auto n2 = m_count >> 2;
    m_sampleMedian = (m_count % 2 ? m_events[n2 + 1] : (m_events[n2] + m_events[n2 + 1]) / 2.);
}

void inline Statistic::calcExpectedValue()
{
    m_theoreticalExpectedValue = 1. / util::sqr(m_lambda) - util::sqr(m_alpha) / 6.;
}

void inline Statistic::calcDispersion()
{
    auto l = m_lambda;
    auto a = m_alpha;

    m_theoreticalDispersion = -util::pow(a, 3) / 12. + 2. / util::pow(l, 3) - 1. / util::pow(l, 4) + a * a / (3. * l * l) - util::pow(a, 4) / 36.;
}

void Statistic::calculate()
{
    std::sort(m_events.begin(), m_events.end());

    calcSampleMean();

    calcSampleDispersion();

    calcScale();

    calcSampleMedian();

    calcExpectedValue();

    calcDispersion();
}