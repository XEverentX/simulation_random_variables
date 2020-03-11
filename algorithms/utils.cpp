#include "utils.hpp"

#include <iostream>

void initParametrs(double &lambda, double &alpha, int &count)
{
    std::cout << "Please, enter the parametr(s):\n";

    std::cout << "Lambda = ";
    std::cin >> lambda;
    std::cout << "\n";

    std::cout << "Count = ";
    std::cin >> count;
    std::cout << "\n";

    alpha = -2.0 - (2.0 / lambda);
}
