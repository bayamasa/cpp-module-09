#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, float> _price;
public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    void add(const std::string &date, const std::string &rate);
    float getRateByDate(const std::string &date);
};

#endif
