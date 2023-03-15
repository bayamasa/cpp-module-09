#include "BitcoinExchange.hpp"
#include <fstream>


int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout << "Error: need text file in args" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    std::string filename;
    filename = argv[1];
    std::ifstream ifs("data.csv");
    if (!ifs) {
        std::cerr << "Error: could not open the given csv file" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    std::string line;
    std::string separator = ",";
    while (std::getline(ifs, line))
    {
        // std::cout << line << std::endl;
        std::string::size_type pos = 0;
        pos = line.find(separator);
        if (pos == std::string::npos) {
            std::cerr << "Error: csv format" << std::endl;
            std::exit(EXIT_FAILURE);
        }
            
        std::string date = line.substr(0,pos);
        std::string rate = line.substr(pos + 1, line.size());
        
        // std::cout << date << std::endl;
        // std::cout << rate << std::endl;
        
    }
    
    return 0;
}

