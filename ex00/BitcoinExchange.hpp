#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>
#include <iostream>

class BitcoinExchange
{
private:
    std::string _date;
    double      _exchange_rate;
public:
    BitcoinExchange();
    BitcoinExchange(std::string date, double exchange_rate);
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
};

#endif
