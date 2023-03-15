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
    // float f = bitcoinExchange.getRateByDate("2011-10-23");
    // std::cout << "rates: " << f << std::endl;
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

void validateArg(std::string filename) {
    std::string line;
    std::string separator = "|";
    
    std::ifstream ifs(filename);
    if (ifs.fail()) {
        throw std::runtime_error("Error: could not open argument text");
    }
    
    // header check
    std::getline(ifs, line);
    std::string::size_type pos = 0;
    pos = line.find(separator);
    if (pos == std::string::npos) {
        throw std::runtime_error("Error: header format invalid");
    }
    std::string date = line.substr(0,pos); 
    std::string value = line.substr(pos + 1, line.size());
    if (date != "date " || value != " value") {
        throw std::runtime_error("Error: header format invalid. ex) 'date | value'");
    }
    
    // body
    pos = 0;
    size_t line_count = 1;
    while (std::getline(ifs, line))
    {
        pos = line.find(separator);
        if (pos == std::string::npos) {
             throw std::runtime_error("Error: csv format");
        }
        std::string date = line.substr(0,pos);
        std::string value = line.substr(pos + 1, line.size());
        
        // 文字列チェック
        if (date.empty() || value.empty()) {
            std::cerr << "Error: line count: " << line_count << std::endl;
            throw std::runtime_error("Error: attribute is blank.");
        }
        
        if (date[date.size() - 1] != ' ' || value[0] != ' ') {
            std::cerr << "Error: line count: " << line_count << std::endl;
            throw std::runtime_error("Error: attribute needs space. ex) 'date | value'");
        }
        
        // 値チェック
        float valuef = stringToFloat(value);
        if (valuef < 0 || valuef > 1000) {
            std::cerr << "Error: line count: " << line_count << std::endl;
            throw std::runtime_error("Error: value must be between 0 to 1000");
        }

        if (isValidDate(date)) {
            std::cerr << "Error: line count: " << line_count << std::endl;
            throw std::runtime_error("Error: invalid date format ex) Year-Month-Day");
        }
    }
    ifs.close();
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
    size_t line_count = 1;
    while (std::getline(ifs, line))
    {
        pos = line.find(separator);
        if (pos == std::string::npos) {
             throw std::runtime_error("Error: csv format");
        }
        // '|'の前の空白を削除
        std::string date = line.substr(0,pos - 1);
        // '|'の後の空白を削除
        std::string value = line.substr(pos + 2, line.size());
        
        if (bic->isExistsDate(date))
        {
            float rate = bic->getRateByDate(date); 
        } else {
            // 直近のレートを探す。
            
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
        validateArg(filename);
        displayExchangeRate(bitcoinExchange ,filename);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        delete bitcoinExchange;
        std::exit(EXIT_FAILURE);
    }
    
    delete bitcoinExchange;
    return 0;
}

