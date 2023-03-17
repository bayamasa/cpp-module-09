#include "BitcoinExchange.hpp"
#include <fstream>


BitcoinExchange *storeCsvInMemory() {
    BitcoinExchange *bitcoinExchange = new BitcoinExchange();

    std::ifstream ifs("data.csv");
    if (ifs.fail()) {
       throw std::runtime_error("Error: could not open the given csv file");
    }
    
    // csvの読み込み
    std::string line;
    std::string separator = ",";
    
    // 最初の行は読み飛ばす
    std::getline(ifs, line);
    
    while (std::getline(ifs, line))
    {
        std::string::size_type pos = 0;
        pos = line.find(separator);
        if (pos == std::string::npos) {
            ifs.close();
            throw std::runtime_error("Error: csv format invalid");
        }
            
        std::string date = line.substr(0,pos);
        std::string rate = line.substr(pos + 1, line.size());
        
        bitcoinExchange->add(date, rate);
    }
    ifs.close();
    return bitcoinExchange;
}

bool isValidDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    int year, month, day;
    std::istringstream date_stream(date);

    date_stream >> year;
    date_stream.ignore(1);
    date_stream >> month;
    date_stream.ignore(1);
    date_stream >> day;

    if (date_stream.fail() || !date_stream.eof()) {
        return false;
    }

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        days_in_month[2] = 29;  // うるう年の場合
    }

    if (day > days_in_month[month]) {
        return false;
    }

    return true;
}

void displayExchangeRate(BitcoinExchange *bic, std::string filename) {
    std::string line;
    std::string separator = "|";
    
    std::ifstream ifs(filename);
    if (ifs.fail()) {
        throw std::runtime_error("Error: could not open argument text");
    }
    
    // header
    std::getline(ifs, line);
    std::string::size_type pos = 0;
    
    // body
    size_t line_count = 0;
    while (std::getline(ifs, line))
    {
        line_count++;
        pos = line.find(separator);
        if (pos == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0,pos);
        std::string value = line.substr(pos + 1, line.size());
        
        // 文字列チェック
        if (date.empty() || value.empty()) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        
        if (date[date.size() - 1] != ' ' || value[0] != ' ') {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        
        // '|'の前の空白を削除
        date = line.substr(0,pos - 1);
        // '|'の後の空白を削除
        value = line.substr(pos + 2, line.size());
        
        // 値チェック
        float valuef = stringToFloat(value);
        if (valuef < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        } else if (valuef > 1000) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        float rate;
        if (bic->isExistsDate(date))
        {
            rate = bic->getRateByDate(date);
            float valuef = stringToFloat(value);
            
            std::cout << date << " => " << value << " = " << rate * valuef << std::endl;
            
            
        } else {
            // 直近のレートを探す。
            std::map<std::string, float>::const_iterator it = bic->findLessEqual(date);
            rate = it->second;
            if (it != bic->getPriceEnd()) {
                std::cout << date << " => " << value << " = " << rate * valuef << std::endl;
            } else {
                std::cout << "Error: bad input => " << line << std::endl;
            }
        }
    }
}


int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout << "Error: need text file in args" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string filename = argv[1];
    BitcoinExchange *bitcoinExchange;
    try
    {
        bitcoinExchange = storeCsvInMemory();
        displayExchangeRate(bitcoinExchange ,filename);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        delete bitcoinExchange;
        std::exit(EXIT_FAILURE);
    }
    
    delete bitcoinExchange;
    return 0;
}

