/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:27 by lomont            #+#    #+#             */
/*   Updated: 2026/02/14 05:31:41 by lomont           ###   ########.fr       */
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
#include <sys/time.h>
#include <iomanip>

class PmergeMe
{
	private:
		int sav;
		struct timeval _time;
		std::deque<int> list;
		std::deque<std::pair<int, int> > winners;
	public:
		PmergeMe( int argc, char** argv );
		~PmergeMe( void );
		std::deque<int> fordJohnson(std::deque<int> container);
		std::deque<int>& getList( void );
		void	printResult(void);
		int		Jacobsthal(int n);
		void	binary_search(std::deque<int>& S, std::deque<std::pair<int, int> >& pairs, int jacobstal, int leftover);
		void	binary_insert(std::deque<int>& S, int Ai, int Bi);
		double	get_time( void );
		void set_time( void );
};

int		parseNumbers( const char* str);
bool	hasOverflow(double n);
bool	isNumber(const char* str);
void	addNumber(std::deque<int>* c, int n);
void	printError(std::string Error);

#endif
