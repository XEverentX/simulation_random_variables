#include "./../algorithms/distribution.hpp"
#include "./../algorithms/utils.hpp"

#include <iostream>
#include <functional>
#include <cmath>

int main() {
    double lambda = 0.;
    double alpha  = 0.;
    int    count  = 0;

    initParametrs(lambda, alpha, count);

    auto inversedCumulativeFunction = [=] (double x) -> double {
        return -log(lambda * x) / lambda;
    };

    Distribution distribution;
    distribution.setInversedCumulativeFunction(inversedCumulativeFunction);

    auto statistic = distribution.experiment(count);

    auto v = statistic.getEventsList();

    for (auto x : v)
    {
        std::cout << x << " ";
    }
}