#include "RPN.hpp"

RPN::RPN(){}
RPN::~RPN(){}

RPN::RPN(const RPN &other)
{
    *this = other;
}
RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
        _num_stack = other._num_stack;
    }
    return *this;
}

void RPN::push(long num) {
    _num_stack.push(num);
}

void RPN::calc(char ope) {
    long first_operand;
    long second_operand;
    long res;

    second_operand = _num_stack.top();
    _num_stack.pop();
    first_operand = _num_stack.top();
    _num_stack.pop();
    if (ope == '+') {
        res = first_operand + second_operand;
    } else if (ope == '-')
    {
        res = first_operand - second_operand;
    } else if (ope == '*')
    {
        res = first_operand * second_operand;
    } else 
    {
        if (second_operand == 0)
            throw std::runtime_error("Error: divided by zero");
        res = first_operand / second_operand;
    }
    if (res > INT_MAX)
        throw std::runtime_error("Error: greater than INT_MAX are not accepted.");
    _num_stack.push(res);
}

bool RPN::isEnoughSize() {
    return _num_stack.size() >= 2;
}

void RPN::displayResult() {
    if (_num_stack.size() != 1) {
        throw std::runtime_error("Error: syntax invalid");
    }
    std::cout << _num_stack.top() << std::endl;
    _num_stack.pop();
}
