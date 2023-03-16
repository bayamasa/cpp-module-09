#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}
PmergeMe::~PmergeMe()
{
}
PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
    }
    return *this;
}

void PmergeMe::addNumber(int num) {
    _vector_array.push_back(num);
    _list_array.push_back(num);
}

void PmergeMe::displayAllVectorAttr(bool isBefore) {
    if (isBefore)
        std::cout << "Before: ";
    else 
        std::cout << "After: ";
    
    std::vector<size_t>::const_iterator itr = _vector_array.begin();
    while (itr != _vector_array.end())
        std::cout << *itr++ << " ";
    
    std::cout << std::endl;
}
