#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>

class PmergeMe
{
private:
    std::vector<size_t> _vector_array;
    std::list<size_t> _list_array;
public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    void addNumber(int number);
    void displayAllVectorAttr(bool isBefore);
};

#endif
