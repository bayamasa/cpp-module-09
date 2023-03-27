#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <string>
#include <exception>
#include <iostream>

class RPN
{
private:
    std::stack<long> _num_stack;
public:
    RPN();
    ~RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    void push(long num);
    void calc(char ope);
    bool isEnoughSize();
    void displayResult();
};

#endif
