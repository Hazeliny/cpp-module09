/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:12:16 by linyao            #+#    #+#             */
/*   Updated: 2025/02/12 21:17:40 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
//#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <ctime>

bool isUnsignedInt(std::string const &s);

class PmergeMe
{
    private:
        std::vector<unsigned int>   _vec;
        std::deque<unsigned int>    _deq;
        PmergeMe();
    public:
        PmergeMe(int n, char **str);
        PmergeMe(PmergeMe const &src);
        PmergeMe &operator=(PmergeMe const &src);
        ~PmergeMe();
        std::vector<unsigned int>& getVec();
        std::deque<unsigned int>& getDeq();
};

template <typename T>
void insertSort(T& ct, int left, int right)
{
    int             j;
    unsigned int    key;

    for (int i = left + 1; i <= right; i++)
    {
        key = ct[i];
        for (j = i - 1; j >= left && ct[j] > key; j--)
            ct[j + 1] = ct[j];
        ct[j + 1] = key;
    }
}

template <typename T>
void mergeSort(T&ct, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    T left_half(n1);
    T right_half(n2);

    for (int i = 0; i < n1; i++)
        left_half[i] = ct[left + i];
    for (int j = 0; j < n2; j++)
        right_half[j] = ct[middle + 1 + j];
    
    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (left_half[i] <= right_half[j])
        {
            ct[k] = left_half[i];
            i++;
        }
        else
        {
           ct[k] = right_half[j];
           j++;
        }
        k++;
    }
    while (i < n1)
    {
        ct[k] = left_half[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        ct[k] = right_half[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeInsertSort(T& ct, int left, int right, int threshold)
{
    if (left < right)
    {
        if (right - left <= threshold)
            insertSort(ct, left, right);
        else
        {
            int middle = left + (right - left) / 2;
            mergeInsertSort(ct, left, middle, threshold);
            mergeInsertSort(ct, middle + 1, right, threshold);
            mergeSort(ct, left, middle, right);
        }
    }
}

template <typename T>
void print(T &container)
{
    typename T::iterator it;
    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}
