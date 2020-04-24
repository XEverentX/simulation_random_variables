// Copyright Lebedev Alexander 2020
#include "utils.hpp"

#include <iostream>

namespace util
{
    static inline void initParameters(double &lambda, int &count, int argc, char **argv)
    {
        if (argc > 1)
        {
            for(int i = 2; i < argc; i += 2)
            {
                switch(argv[i - 1][1])
                {
                    case 'l':
                        lambda = atof(argv[i]);
                        break;
                    case 'c':
                        count = atoi(argv[i]);
                        break;
                }
            }
            return;
        }
        
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
