/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:59:51 by linyao            #+#    #+#             */
/*   Updated: 2025/02/11 23:48:11 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Invalid number of arguments." << std::endl;
		return(1);
	}
	BitcoinExchange btc("data.csv");
	std::ifstream 	infile(av[1]);
	std::string		line;
	if (infile.fail())
	{
		std::cerr << "Invalid file." << std::endl;
		return (1);
	}
	getline(infile, line);
	if (line.compare("date | value"))
	{
		std::cerr << "Invalid file format. The first line must be 'date | value'." << std::endl;
		return (1);
	}
	while (getline(infile, line))
		btc.getResult(line);
	
	return (0);
}
