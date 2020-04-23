#include "utils.hpp"

#include <iostream>

namespace util
{
    static inline void initParameters(double &lambda, int &count)
    {
        std::cout << "Please, enter the parametr(s):\n";

        std::cout << "Lambda = ";
        std::cin >> lambda;
        std::cout << "\n";

        std::cout << "Count = ";
        std::cin >> count;
        std::cout << "\n";
    }

    template<typename Type>
    auto inline belongsTo(Type x, Type lowBoundary, Type highBoundary) -> bool
    {
        return (x >= lowBoundary && x <= highBoundary);
    }
}
