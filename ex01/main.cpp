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

#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Invalid number of arguments." << std::endl;
		return(1);
	}
	try
	{
		rpn(av[1]);
	}
	catch(BadCharacterException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch(NotEnoughNumException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch(ZeroDivisorException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch(BadResultException& e)
	{
		std::cerr << e.what() << std::endl;
	}
/*
	catch(const std::exception& e)
	{
		std::cerr << "Error: rpn" << std::endl;
	}
*/	
	return (0);
}
