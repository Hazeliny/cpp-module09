/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:48:54 by linyao            #+#    #+#             */
/*   Updated: 2025/02/12 00:31:48 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, float>    _map;
    public:
        BitcoinExchange();
        BitcoinExchange(std::string inf);
        BitcoinExchange(BitcoinExchange const &src);
        BitcoinExchange &operator=(BitcoinExchange const &src);
        ~BitcoinExchange();

        void createDb(std::string inf);
        void getResult(std::string line) const;
        
        class RepeatedlyCreateDbException : public std::exception
        {
            virtual const char *what() const throw()
            {
                return ("Repeatedly creating database is prohibited.");
            }
        };
        class InvalidDbFileException : public std::exception
        {
            virtual const char *what() const throw()
            {
                return ("Database file cannot be open, make sure it exists and readable with the right path.");
            }
        };
        class InvalidDbHeadException : public std::exception
        {
            virtual const char *what() const throw()
            {
                return ("Error: invalid head in database file.");
            }
        };
        class BadInputException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Error: bad input => ");
                }
        };

        class NegativeIntException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Error: not a positive number.");
                }
        };
        class NoMatchDateException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Error: no date match!");
                }
        };
};
