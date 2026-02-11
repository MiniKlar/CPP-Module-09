/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:27 by lomont            #+#    #+#             */
/*   Updated: 2026/02/11 17:31:56 by lomont           ###   ########.fr       */
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

int		parseNumbers( const char* str);
bool	hasOverflow(double n);
bool	isNumber(const char* str);
void	addNumber(std::deque<int>* c, int n);
void	printError(std::string Error);

#endif
