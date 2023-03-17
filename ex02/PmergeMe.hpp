#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <deque>
#include <algorithm>
#include <ctime>

class PmergeMe
{
private:
    std::vector<size_t> _vector_array;
    std::deque<size_t> _deque_array;
    double _vector_sort_time;
    double _deque_sort_time;
    
public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    void addNumber(int number);
    void displayAllVectorAttr(bool isBefore);

    void insertionSortVector(int left, int right);
    void insertionSortDeque(int left, int right);
    void mergeInsertionSortVector(int left, int right);
    void mergeInsertionSortDeque(int left, int right);
    void mergeVector(int left, int mid, int right);
    void mergeDeque(int left, int mid, int right);
    void sort();
    void displayElapsedTime();
};

#endif
