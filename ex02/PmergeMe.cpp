/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:58:39 by linyao            #+#    #+#             */
/*   Updated: 2025/02/12 21:16:40 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int n, char **str)
{
    for (int i = 1; i < n; i++)
    {
        std::string s(str[i]);
        if (!isUnsignedInt(s))
        {
            std::cerr << "Error: " << str[i] << " is not a positive integer number!" << std::endl;
            exit(1);
        }
    }
    for (int i = 1; i < n; i++)
    {
        this->_vec.push_back(std::atoi(str[i]));
        this->_deq.push_back(std::atoi(str[i]));
    }
}
        
PmergeMe::PmergeMe(PmergeMe const &src)
{
    *this = src;
}
        
PmergeMe &PmergeMe::operator=(PmergeMe const &src)
{
    if (this != &src)
    {
        this->_vec = src._vec;
        this->_deq = src._deq;
    }
    return (*this);
}
        
PmergeMe::~PmergeMe() {}
        
std::vector<unsigned int>& PmergeMe::getVec()
{
    return (this->_vec);
}
        
std::deque<unsigned int>& PmergeMe::getDeq()
{
    return (this->_deq);
}

bool isUnsignedInt(std::string const &s)
{
    std::stringstream ss(s);
    long int i;

    ss >> i;
    if (i < 0 || i > std::numeric_limits<unsigned int>::max())
        return (false);
    return (ss.eof() && !ss.fail());
}
