/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:38:43 by linyao            #+#    #+#             */
/*   Updated: 2025/02/12 14:38:47 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>

void rpn(char *s);

template <typename T>
class DerivedStack : public std::stack<T>
{
	public:
		DerivedStack(){};
		DerivedStack(DerivedStack const &src) : std::stack<T>(src) {};
		DerivedStack &operator=(DerivedStack const &src) {
			if (this != &src)
				std::stack<T>::operator=(src);
			return (*this);
		};
		virtual ~DerivedStack() {};

		typedef typename std::stack<T>::container_type::iterator it;
		typedef typename std::stack<T>::container_type::const_iterator const_it;
		it begin() {
			return std::stack<T>::c.begin();
		};
		it end() {
			return std::stack<T>::c.end();
		};
		const_it begin() const {
			return std::stack<T>::c.begin();
		};
		const_it end() const {
			return std::stack<T>::c.end();
		};
};

class NotEnoughNumException : public std::exception
{
	public:
		virtual const char *what() const throw()
		{
			return ("Error: not enough numbers to calculate!");
		}
};

class ZeroDivisorException : public std::exception
{
	public:
		virtual const char *what() const throw()
		{
			return ("Error: zero divisor!");
		}
};

class BadCharacterException : public std::exception
{
	public:
		virtual const char *what() const throw()
		{
			return ("Error: bad character!");
		}
};

class BadResultException : public std::exception
{
	public:
		virtual const char *what() const throw()
		{
			return ("Error: bad result!");
		}
};
