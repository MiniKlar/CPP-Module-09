/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:13:42 by lomont            #+#    #+#             */
/*   Updated: 2026/01/30 16:53:44 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

//function to check if char is */+-
bool	checkOperator(char c) {

if (c == '*' || c == '/' || c == '+' || c == '-')
		return ( true );
	return ( false );
}

//Function to calcul the numbers of operators & operand to check if operators - 1 = operand
bool	checkOperatorNumbers(char c, bool lastChar) {
	static	size_t numbers = 0, operators = 0;

	if (c == ' ')
		return (false);
	if (!isdigit(c))
		operators++;
	else
		numbers++;
	if (lastChar) {
		if (numbers - 1 == operators)
			return (true);
	}
	return (false);
}

//Function to calcul the operation depending on the operand
int	calculation(std::stack<int>& stack, char _operator) {
	int		n = 0;
	int		m = 0;

	n = stack.top();
	stack.pop();
	m = stack.top();
	stack.pop();

	switch (_operator)
	{
		case ('-') :
			return (m - n);
		case ('+') :
			return (m + n);
		case ('/') :
			return (m / n);
		case ('*') :
			return (m * n);
	}
	return (-1);
}
