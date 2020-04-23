#include <distribution.hpp>
#include <utils.hpp>

#include <iostream>
#include <functional>
#include <cmath>

int main() {
    double lambda = 0.;
    double alpha  = 0.;
    int    count  = 0;

    util::initParameters(lambda, count);
    alpha = 2.0 * (1 / lambda - 1);

    auto inversedCumulativeFunction = [=] (double x) -> double {
        if (!util::belongsTo<double>(x, 0., 1.))
        {
            throw 5;
        }

        if (util::belongsTo<double>(x, 0., -alpha / 2.))
        {
            return alpha - sqrt(-2. * alpha * x);
        } else
        {
            return log(-lambda * (x - 2.)) / lambda;
        }
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