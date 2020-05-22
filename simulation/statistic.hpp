// Copyright Lebedev Alexander 2020
#pragma once

#include <vector>
#include <ctime>
#include <map>
class Statistic final
{
    friend class Experement;
public:
    Statistic(int count = 0);

    Statistic(int count, time_t seed);

    Statistic(Statistic &other) = default;

    Statistic(Statistic &&other);

    ~Statistic() = default;

    void setSeed(time_t seed) noexcept;

    void setCount(int count) noexcept;

    void setParameters(double alpha, double lambda);

    void addEvent(double event);

    void calculate();

    double getHistSegmentsLen(uint32_t count) const;

    [[nodiscard]] std::vector<double> getEventsList(const bool shouldBeSorted = true) const;

    std::vector<double> m_events;
    
protected:
    void inline calcSampleMean();

    void inline calcSampleDispersion();

    void inline calcScale();

    void inline calcSampleMedian();

    void inline calcExpectedValue();
    
    void inline calcDispersion();

    time_t              m_seed;
    int                 m_count;
    double              m_alpha;
    double              m_lambda;
    double              m_sampleMean;
    double              m_sampleDispersion;
    double              m_sampleMedian;
    double              m_scale;
    double              m_theoreticalExpectedValue;
    double              m_theoreticalDispersion;
};