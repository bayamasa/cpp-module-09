#include "RPN.hpp"

RPN::RPN(){}
RPN::~RPN()
{
}
RPN::RPN(const RPN &other)
{
    *this = other;
}
RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
    }
    return *this;
}

void RPN::push(int num) {
    _num_stack.push(num);
}

void RPN::calc(char ope) {
    int first_operand;
    int second_operand;
    int res;

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
            throw std::runtime_error("Math Error: divided by zero");
        res = first_operand / second_operand;
    }
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