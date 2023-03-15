#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
    // mapの要素をすべてdeleteする
}

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

float stringToFloat(const std::string& input) {
    std::stringstream ss(input);
    float result;
    ss >> result;

    if (ss.fail()) {
        std::cerr << "input: " << input << std::endl;
        throw std::runtime_error("Error: could not convert string to float");
    }
    return result;
}


void BitcoinExchange::add(const std::string &date, const std::string &rate) {
    float ratef;
    
    try
    {
        ratef = stringToFloat(rate);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    // 基本的にdata.csvは課題によって与えられるもので変更はないものとする。
    _price[date] = ratef;
}

float BitcoinExchange::getRateByDate(const std::string &date) {
    return _price[date];
}

bool BitcoinExchange::isExistsDate(const std::string &date) {
    return _price.count(date);
}

std::map<std::string, float>::const_iterator BitcoinExchange::findLessEqual(const std::string& key) {
       std::map<std::string, float>::const_iterator it = _price.lower_bound(key);

    if (it != _price.begin()) {
        if (it == _price.end() || it->first != key) {
            --it;
        }
    } else if (it == _price.end() || it->first > key) {
        return _price.end(); // Not found
    }

    return it;
}

std::map<std::string, float>::const_iterator BitcoinExchange::getPriceEnd() {
    return _price.end();
}
