/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:27 by lomont            #+#    #+#             */
/*   Updated: 2026/02/15 03:18:18 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <climits>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <iomanip>

class PmergeMe
{
	private:
		std::deque<int> 	list;
		std::vector<int> 	Vlist;
		struct timeval 		_time;
	public:
		//canonical form
		PmergeMe( int argc, char** argv );
		~PmergeMe( void );

		//Getters
		std::deque<int>&			ft_getList( void );
		std::vector<int>&			ft_getVList( void );
		double						ft_getTime( void );

		//Setters
		void						ft_setTime( void );

		//Members function
		int							ft_Jacobsthal(int n);

		//for deque
		void						ft_binary_search(std::deque<int>& S, std::deque<std::pair<int, int> >& pairs, int jacobstal, int leftover);
		void						ft_binary_insert(std::deque<int>& S, int Ai, int Bi);
		std::deque<int> 			ft_fordJohnson(std::deque<int> container);

		//for vector
		void						ft_binaryInsertVector(std::vector<int>& S, int Ai, int Bi);
		void						ft_binarySearchVector(std::vector<int>& S, std::vector<std::pair<int, int> >& pairs, int Jacobsthal, int prevJacobsthal);
		std::vector<int>			ft_fordJohnsonVector(std::vector<int> container);

};

//Utils functions

int									ft_parseNumbers( const char* str);
bool								ft_hasOverflowed(double n);
bool								ft_isNumber(const char* str);
bool								ft_checkDuplicates(std::deque<int> & result);
bool								ft_specialSort(const std::pair<int, int>& i, const std::pair<int, int>& j);
void								ft_addNumber(std::deque<int>* c, std::vector<int>* Vc, int n);
void								ft_printError(std::string Error);
void								ft_printBeforeSorted(char** argv);

template <typename T>
void								ft_performCalculationAndPrintIt(T& a, char** argv, int listLen, bool isDeque);

template <typename T>
void								ft_printAfterSorted(T& container);

#include "PmergeMe.tpp"

#endif
