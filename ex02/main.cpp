/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:59:51 by linyao            #+#    #+#             */
/*   Updated: 2025/02/12 21:45:57 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 3)
	{
		std::cerr << "Error: not enough number of arguments." << std::endl;
		return(1);
	}
	PmergeMe pm(ac, av);
	
	double time_vec, time_deq;
	clock_t s_vec, e_vec, s_deq, e_deq;

	std::cout << "Before: ";
	print(pm.getVec());

	s_vec = clock();
	mergeInsertSort(pm.getVec(), 0, pm.getVec().size() - 1, 5);
	e_vec = clock();
	time_vec = double(e_vec - s_vec) / CLOCKS_PER_SEC * 1000;

	s_deq = clock();
	mergeInsertSort(pm.getDeq(), 0, pm.getDeq().size() - 1, 5);
	e_deq = clock();
	time_deq = double(e_deq - s_deq) / CLOCKS_PER_SEC * 1000;

	std::cout << std::fixed << std::setprecision(3) << "After: ";
	print(pm.getDeq());
	std::cout << "Time to process a range of " << ac - 1 << " elements with std::vector: " << time_vec << " ms" << std::endl;
	std::cout << "Time to process a range of " << ac - 1 << " elements with std::deque:  " << time_deq << " ms" << std::endl;
		
	return (0);
}
