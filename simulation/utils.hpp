// Copyright Lebedev Alexander 2020
#pragma once

namespace util
{
    static inline void initParameters(double &lambda, int &count, int argc, char **argv);

    template<typename Type = double>
    auto inline belongsTo(Type x, Type lowBoundary, Type highBoundary) -> bool;

    template<typename Type>
    auto inline sqr(Type x) -> Type;

    template<typename Type>
    auto inline pow(Type x, uint32_t n) -> Type;
}

#include "utils.cxx"
