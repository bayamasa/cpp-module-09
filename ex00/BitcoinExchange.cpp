#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        _price = other._price;
    }
    return *this;
}

double stringToDouble(const std::string& input) {
    std::stringstream ss(input);
    double result;
    ss >> result;

    if (ss.fail()) {
        throw std::runtime_error("Error: could not convert string to double");
    }
    if (!ss.eof()) {
        throw std::runtime_error("Error: extra characters exist");
    }
    
    return result;
}


void BitcoinExchange::add(const std::string &date, const std::string &rate) {
    double ratef;
    
    try
    {
        ratef = stringToDouble(rate);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    // 基本的にdata.csvは課題によって与えられるもので変更はないものとする。
    _price[date] = ratef;
}

double BitcoinExchange::getRateByDate(const std::string &date) {
    return _price[date];
}

bool BitcoinExchange::isExistsDate(const std::string &date) {
    return _price.count(date);
}

std::map<std::string, double>::const_iterator BitcoinExchange::findLessEqual(const std::string& key) {
       std::map<std::string, double>::const_iterator it = _price.lower_bound(key);

    if (it != _price.begin()) {
        if (it == _price.end() || it->first != key) {
            --it;
        }
    } else if (it == _price.end() || it->first > key) {
        return _price.end();
    }

    return it;
}

std::map<std::string, double>::const_iterator BitcoinExchange::getPriceEnd() {
    return _price.end();
}
