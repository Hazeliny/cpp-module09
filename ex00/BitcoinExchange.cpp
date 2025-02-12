/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:49:08 by linyao            #+#    #+#             */
/*   Updated: 2025/02/12 00:40:08 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _map()
{}
        
BitcoinExchange::BitcoinExchange(std::string inf) : _map()
{
    this->createDb(inf);
}
        
BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) : _map(src._map)
{
    *this = src;
}
        
BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &src)
{
    this->_map = src._map;
    return (*this);
}
        
BitcoinExchange::~BitcoinExchange()
{}

static float strToFloat(std::string s)
{
    double num = std::strtod(s.c_str(), NULL);
    return (static_cast<float>(num));
}

void BitcoinExchange::createDb(std::string inf)
{
    if (this->_map.size())
        throw RepeatedlyCreateDbException();
        
    std::ifstream   db(inf.c_str());
    std::string     buf;
    if (db.fail())
    {
        db.close();
        throw InvalidDbFileException();
    }
    getline(db, buf);
    if (buf.compare("date,exchange_rate"))
    {
        db.close();
        throw InvalidDbHeadException();
    }

    std::string date;
    float       rate;
    while (getline(db, buf))
    {
        date = buf.substr(0, 10);
        rate = strToFloat(buf.substr(11));
//        std::cout << date << " , " << rate << std::endl;
        this->_map.insert(std::pair<std::string, float>(date, rate));
    }
}

int strToInt(char const *s)
{
    char *end = NULL;
    long l;
    
    errno = 0;
    if (s[0] == '0')
        s++;
    l = strtol(s, &end, 0);
    if ((errno == ERANGE && l == std::numeric_limits<long int>::max()) || l > std::numeric_limits<int>::max())
    {
        std::cerr << "Error: too large a number." << std::endl;
        throw std::exception();
    }
    if ((errno == ERANGE && l == std::numeric_limits<long int>::min()) || l < std::numeric_limits<int>::min())
    {
        std::cerr << "Error: not a positive number." << std::endl;
        throw std::exception();
    }
    if (*s == '\0' || *end != '\0')
        throw BitcoinExchange::BadInputException();
    return (static_cast<int>(l));
}

void isValid_Year(int y)
{
    if (y < 2009)
        throw BitcoinExchange::BadInputException();
}

void isValid_Month(int m)
{
    if (m < 1 || m > 12)
        throw BitcoinExchange::BadInputException();
}

void isValid_Day(int y, int m, int d)
{
    if (m == 2)
    {
        if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
        {
            if (d < 1 || d > 29)
                throw BitcoinExchange::BadInputException();
        }
        else if (d < 1 || d > 28)
            throw BitcoinExchange::BadInputException();
    }
    else if (m == 4 || m == 6 || m == 9 || m == 11)
    {
        if (d < 1 || d > 30)
            throw BitcoinExchange::BadInputException();
    }
    else if (d < 1 || d > 31)
        throw BitcoinExchange::BadInputException();
}
        
void BitcoinExchange::getResult(std::string line) const
{
    std::string date = line.substr(0, 10);
    try
    {
        int y = strToInt(date.substr(0, 4).c_str());
        isValid_Year(y);
        int m = strToInt(date.substr(5, 2).c_str());
        isValid_Month(m);
        int d = strToInt(date.substr(8, 2).c_str());
        isValid_Day(y, m, d);
    }
    catch(BitcoinExchange::BadInputException &e)
    {
        std::cerr << e.what() << date << std::endl;
        return ;
    }
    catch(std::exception &e)
    {
        return ;
    }
    try
    {
        float btcNum = strToFloat(line.substr(12));
        if (btcNum < 0)
            throw BitcoinExchange::NegativeIntException();
        else if (btcNum > 1000)
            throw std::exception();
    }
    catch(BitcoinExchange::NegativeIntException &e)
    {
//        std::cerr << "Error: not a positive number." << std::endl;
        std::cerr << e.what() << std::endl;
        return ;
    }
    catch(std::exception &e)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return ;
    }
    date[4] = '-';
    date[7] = '-';
    float btcNum = strToFloat(line.substr(12));
    std::map<std::string, float>::const_iterator it = this->_map.lower_bound(date);
    try
    {
        if (this->_map.empty())
            throw BitcoinExchange::EmptyMapException(); 
        if (it == this->_map.end() || (it != this->_map.begin() && it->first != date))
            it--;
        else if (it == this->_map.begin() && it->first != date)
            throw BitcoinExchange::NoMatchDateException();
    }
    catch(BitcoinExchange::EmptyMapException &e)
    {
        std::cerr << e.what() << std::endl;
        return ;
    }
    catch(BitcoinExchange::NoMatchDateException &e)
    {
        std::cerr << e.what() << std::endl;
        return ;
    }
    if (it->first != date)
        std::cout << it->first << " is the last date" << std::endl;
    std::cout << date << " => " << std::fixed << std::setprecision(2) << btcNum << " = " << btcNum * it->second << std::endl;
}
