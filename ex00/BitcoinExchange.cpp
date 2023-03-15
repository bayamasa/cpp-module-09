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
    
    if (_price.count(date) == 0)
    {
        // TODO:dateが存在しなかったときの処理を書く
        throw std::runtime_error("Error: no applicable rates found");
    }
    return _price[date];
}
