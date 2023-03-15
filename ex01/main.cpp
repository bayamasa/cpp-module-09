#include "RPN.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout << "Error: need text file in args" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    std::string exp(argv[1]);
    std::string::iterator itr = exp.begin();
    unsigned long i = 0;
    while (i < exp.length())
    {
        std::cout << *itr << std::endl;
        itr++;
        i++;
    }
    
    return 0;
}
