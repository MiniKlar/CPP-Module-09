/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:27 by lomont            #+#    #+#             */
/*   Updated: 2026/02/13 03:03:54 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <deque>
#include <algorithm>

class PmergeMe
{
	private:
		std::deque<int> list;
		std::deque<std::pair<int, int> > winners;
		int sav;
	public:
		PmergeMe( int argc, char** argv );
		~PmergeMe( void );
		std::deque<int> fordJohnson(std::deque<int> container);
		std::deque<int>& getList( void );
		void	printResult(void);
		int		Jacobsthal(int n);
		void	binary_search(std::deque<int>& S, std::deque<std::pair<int, int> >& pairs, int jacobstal, int leftover);
		void	binary_insert(std::deque<int>& S, std::deque<std::pair<int, int> >& pairs, int Ai)
};

int		parseNumbers( const char* str);
bool	hasOverflow(double n);
bool	isNumber(const char* str);
void	addNumber(std::deque<int>* c, int n);
void	printError(std::string Error);

#endif
