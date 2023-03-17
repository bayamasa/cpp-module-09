#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

int main(int argc, char const *argv[])
{  
    if (argc == 1) {
        std::cout << "Error: need args" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    PmergeMe pmergeMe;
    int num;
        
    int i = 1;
    while (i < argc) {
        std::istringstream iss(argv[i]);
        if (iss >> num)
        {
            if (num <= 0)
            {
                std::cout << "Error: not a positive integer " << argv[i] << std::endl;
                std::exit(EXIT_FAILURE);
            }
            pmergeMe.addNumber(num);
        } else {
            std::cout << "Error: not a valid number" << argv[i] << std::endl;
            std::exit(EXIT_FAILURE);
        }
        i++;
    }
    pmergeMe.displayAllVectorAttr(true);
    pmergeMe.sort();
    pmergeMe.displayAllVectorAttr(false);
    pmergeMe.displayElapsedTime();
}
