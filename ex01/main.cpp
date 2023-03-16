#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <cctype>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout << "Error: need text file in args" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    RPN rpn;
    
    std::istringstream iss(argv[1]);
    std::string token;
    while (iss >> token) {
        if (std::isdigit(token.at(0)) && token.size() == 1) {
            int num = std::atoi(token.c_str());
            rpn.push(num);
            // std::cout << "Read integer: " << num << std::endl;
        } else if (token.size() == 1 && (token.at(0) == '+' || token.at(0) == '-' || token.at(0) == '*' || token.at(0) == '/')) {
            // std::cout << "Read operator: " << token.at(0) << std::endl;
            try
            {
                if (rpn.isEnoughSize()) 
                    rpn.calc(token.at(0));
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                std::exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << "Error: encountered invalid token: " << token << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    try {
        rpn.displayResult();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::exit(EXIT_FAILURE);
    }
    return 0;
}
