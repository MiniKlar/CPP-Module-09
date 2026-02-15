/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 01:11:16 by lomont            #+#    #+#             */
/*   Updated: 2026/02/15 03:12:29 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//Functions to parse

int		ft_parseNumbers( const char* str) {
	double	number;

	if (!ft_isNumber(str))
		ft_printError("It's not a number");
	number = atof(str);
	if (ft_hasOverflowed(number)) {
		ft_printError("Overflow error");
	}
	return (static_cast<int>(number));
}

bool	ft_hasOverflowed(double n) {
	if (n > INT_MAX) {
		return (true);
	}
	return (false);
}

bool ft_isNumber(const char* str) {
	for (size_t i = 0; i < strlen(str); i++) {
		if (str[0] == '-')
			ft_printError("Number negative");
		if (!isnumber(str[i]))
			return (false);
	}
	return (true);
}

//add Number to container

void	ft_addNumber(std::deque<int>* c, std::vector<int>* Vc, int n) {
	c->push_back(n);
	Vc->push_back(n);
	return ;
}

//Sort homemade for losers numbers.

bool	ft_specialSort(const std::pair<int, int>& i, const std::pair<int, int>& j) {
	return (i.first < j.first);
}

//Check duplicates
bool	ft_checkDuplicates(std::deque<int> & result) {
	int	tmp = -1;
	for (std::deque<int>::iterator it = result.begin(); it != result.end(); it++) {
		if (tmp == *it)
			return (false);
		tmp = *it;
	}
	return (true);
}

//Print functions

void	ft_printError(std::string Error) {
	std::cerr << Error << ", exiting program..." << std::endl; //for debug purpose only, for correction please put "Error"
	exit(1);
}


void	ft_printBeforeSorted(char** argv) {
	std::cout << "Before: ";
	for (size_t i = 1; argv[i]; i++) {
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;
}
