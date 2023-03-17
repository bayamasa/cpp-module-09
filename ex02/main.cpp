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
    size_t num;
        
    int i = 1;
    while (i < argc) {
        std::istringstream iss(argv[i]);
        if (iss >> num)
        {
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
}
