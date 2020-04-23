#pragma once

namespace util
{
    static inline void initParameters(double &lambda, int &count);

    template<typename Type = double>
    auto inline belongsTo(Type x, Type lowBoundary, Type highBoundary) -> bool;
}

#include "utils.cxx"
