/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:38:55 by linyao            #+#    #+#             */
/*   Updated: 2025/02/12 14:38:57 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static void calculate(DerivedStack<int> &stack, char c)
{
	if (stack.size() < 2)
		throw NotEnoughNumException();
	int second = stack.top();
	stack.pop();
	if (c == '+')
		stack.top() += second;
	else if (c == '-')
		stack.top() -= second;
	else if (c == '*')
		stack.top() *= second;
	else if (c == '/')
	{
		if (second == 0)
			throw ZeroDivisorException();
		else
			stack.top() /= second;
	}
}

void rpn(char *s)
{
	DerivedStack<int> stack;
	while (s && *s == ' ')
		s++;
	while (s && *s)
	{
		if (std::isdigit(*s))
		{
			stack.push(*s - '0');
			s++;
		}
		else if (*s == '+' || *s == '-' || *s == '*' || *s == '/')
		{
			calculate(stack, *s);
			s++;
		}
		else
			throw BadCharacterException();
		if (*s != ' ' && *s != '\0')
			throw BadCharacterException();
		while (*s == ' ')
			s++;
	}
	if (stack.size() == 1)
		std::cout << stack.top() << std::endl;
	else
		throw BadResultException();
}
