#ifndef RPN_HPP
# define RPN_HPP

#include <stack>

class RPN
{
private:
    std::stack<int> calc;
public:
    RPN();
    ~RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
};

#endif
