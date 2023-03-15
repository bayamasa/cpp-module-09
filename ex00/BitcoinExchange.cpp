#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    _date = "";
    _exchange_rate = 0.0;
}

BitcoinExchange::BitcoinExchange(std::string date, double exchange_rate)
{
    _date = date;
    _exchange_rate = exchange_rate;
}

BitcoinExchange::~BitcoinExchange()
{
    
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        _date = other._date;
        _exchange_rate = other._exchange_rate;
    }
    return *this;
}
