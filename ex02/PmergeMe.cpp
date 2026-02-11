/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:25 by lomont            #+#    #+#             */
/*   Updated: 2026/02/11 17:32:13 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int		parseNumbers( const char* str) {
	double	number;

	if (!isNumber(str))
		printError("It's not a number");
	number = atof(str);
	if (hasOverflow(number)) {
		printError("Overflow error");
	}
	return (static_cast<int>(number));
}

bool	hasOverflow(double n) {
	if (n > INT_MAX) {
		return (true);
	}
	return (false);
}

bool isNumber(const char* str) {
	for (size_t i = 0; i < strlen(str); i++) {
		if (str[0] == '-')
			printError("Number negative");
		if (!isnumber(str[i]))
			return (false);
	}
	return (true);
}

void	addNumber(std::deque<int>* c, int n) {
	c->push_back(n);
	return ;
}

void	printError(std::string Error) {
	std::cerr << Error << ", exiting program..." << std::endl; //for debug purpose only, for correction please put "Error"
	exit(1);
}
