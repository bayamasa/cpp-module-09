#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
    
}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vector_array = other._vector_array;
        _deque_array = other._deque_array;
        _vector_sort_time = other._vector_sort_time;
        _deque_sort_time = other._deque_sort_time;
    }
    return *this;
}

void PmergeMe::addNumber(int num) {
    _vector_array.push_back(num);
    _deque_array.push_back(num);
}

void PmergeMe::displayAllVectorAttr(bool isBefore) {
    if (isBefore)
        std::cout << "Before: ";
    else 
        std::cout << "After: ";
    
    std::vector<size_t>::const_iterator itr = _vector_array.begin();
    
    size_t i = 0;
    while (itr != _vector_array.end()) {
        std::cout << *itr++ << " ";
        if (i == 4)
        {
            std::cout << "[...]";
            break;
        }
        i++;
    }
        
    
    std::cout << std::endl;
}

void PmergeMe::insertionSortVector(int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        size_t key = _vector_array[i];
        int j = i - 1;
        while (j >= left && _vector_array[j] > key) {
            _vector_array[j + 1] = _vector_array[j];
            j--;
        }
        _vector_array[j + 1] = key;
    }
}

void PmergeMe::insertionSortDeque(int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        size_t key = _deque_array[i];
        int j = i - 1;
        while (j >= left && _deque_array[j] > key) {
            _deque_array[j + 1] = _deque_array[j];
            j--;
        }
        _deque_array[j + 1] = key;
    }
}

void PmergeMe::mergeVector(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = _vector_array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = _vector_array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    
    // どちらかの要素が尽きるまで、２つのソート済み配列を左から本体に入れる
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            _vector_array[k] = L[i];
            i++;
        } else {
            _vector_array[k] = R[j];
            j++;
        }
        k++;
    }

    // n1 or n2のマージが終わったらので、余った方の要素をマージする。
    while (i < n1) {
        _vector_array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        _vector_array[k] = R[j];
        j++;
        k++;
    }
}

void PmergeMe::mergeDeque(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = _deque_array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = _deque_array[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            _deque_array[k] = L[i];
            i++;
        } else {
            _deque_array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        _deque_array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        _deque_array[k] = R[j];
        j++;
        k++;
    }
}

void PmergeMe::mergeInsertionSortVector(int left, int right) {
    if (right - left <= _threshold) {
        insertionSortVector(left, right);
    } else {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeInsertionSortVector(left, mid);
            mergeInsertionSortVector(mid + 1, right);
            mergeVector(left, mid, right);
        }
    }
}

void PmergeMe::mergeInsertionSortDeque(int left, int right) {
    if (right - left <= _threshold) {
        insertionSortDeque(left, right);
    } else {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeInsertionSortDeque(left, mid);
            mergeInsertionSortDeque(mid + 1, right);
            mergeDeque(left, mid, right);
        }
    }
}

void PmergeMe::sort() {
    _threshold = 2;
    std::clock_t vec_start_time = std::clock();
    mergeInsertionSortVector(0, _vector_array.size() - 1);
    std::clock_t vec_end_time = std::clock();
    _vector_sort_time = static_cast<double>(vec_end_time - vec_start_time) / CLOCKS_PER_SEC * 1000000;

    std::clock_t deq_start_time = std::clock();
    mergeInsertionSortDeque(0, _deque_array.size() - 1);
    std::clock_t deq_end_time = std::clock();
    _deque_sort_time = static_cast<double>(deq_end_time - deq_start_time) / CLOCKS_PER_SEC * 1000000;

}

void PmergeMe::displayElapsedTime() {
    std::cout   << "Time to process a range of "
                << _vector_array.size() 
                << " elements with std::vector : "
                << _vector_sort_time
                << " us" << std::endl;
    std::cout   << "Time to process a range of "
                << _deque_array.size() 
                << " elements with std::deque : "
                << _deque_sort_time
                << " us" << std::endl;
}
