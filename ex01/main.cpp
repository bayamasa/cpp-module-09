#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <cctype>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout << "Error: need one args" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    RPN rpn;
    
    std::string input = argv[1];
    for (size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];
        if (std::isdigit(ch)) {
            int num = ch - '0';
            rpn.push(num);
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            try
            {
                if (rpn.isEnoughSize()) 
                    rpn.calc(ch);
                else 
                    std::runtime_error("Error: syntax error");
            }
            catch(const std::exception& e)
            {
                std::cout << e.what() << '\n';
                std::exit(EXIT_FAILURE);
            }
        } else if (std::isspace(ch)) {
            continue;
        } else {
            std::cout << "Error: encountered invalid token: " << ch << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    try {
        rpn.displayResult();
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        std::exit(EXIT_FAILURE);
    }
    return 0;
}
