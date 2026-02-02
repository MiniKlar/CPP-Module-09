/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:13:42 by lomont            #+#    #+#             */
/*   Updated: 2026/02/02 23:17:37 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

//canonical form

RPN::RPN( int argc, char** argv ) {
	//std::cout << "RPN default constructor called" << std::endl;
	this->str = argv[argc - 1];
	if (!this->str[0])
		this->ft_error();
	parsing();
	execution();
	return ;
}

RPN::RPN( const RPN& src) : s(src.s) {
	//std::cout << RPN copy constructor called" << std::endl;
	return ;
}

RPN& RPN::operator=( const RPN& other ) {
	//std::cout << "RPN assignement operator called" << std::endl;
	if (&other != this) {
		this->s = other.s;
	}
	return ( *this );
}

RPN::~RPN( void ) {
	//std::cout << "RPN Destructor called" << std::endl;
	return ;
}

void RPN::parsing( void ) {
	for (size_t i = 0; str[i]; i++) {
		if (i % 2 == 1) {
			if (str[i] != ' ')
				this->ft_error();
	}
	else if (!isdigit(str[i]) && !checkOperator(str[i]) )
		this->ft_error();
	if (str[i + 1] == '\0') {
		if (!checkOperatorNumbers(str[i], true))
			this->ft_error();
	}
	checkOperatorNumbers(str[i], false);
}
if (!checkexpression(this->str)) {
	this->ft_error();
}
}

//function to check if char is */+-
bool	RPN::checkOperator(char c) {

if (c == '*' || c == '/' || c == '+' || c == '-')
		return ( true );
	return ( false );
}

//Function to calcul the numbers of operators & operand to check if operators - 1 = operand
bool	RPN::checkOperatorNumbers(char c, bool lastChar) {
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
int	RPN::calculation(std::stack<int>& stack, char _operator) {
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

bool RPN::checkexpression(const char* str) {
	size_t i = 0;
	size_t stackSize = 0;

	while (str[i]) {
		if (str[i] == ' ')
			i++;
		if (isdigit(str[i]))
			stackSize++;
		else {
			if (stackSize < 2)
				return (false);
			stackSize = stackSize - 1;
		}
		i++;
	}
	return (true);
}

void	RPN::ft_error( void ) {
	std::cerr << "Error" << std::endl;
	exit (1);
}

void	RPN::execution( void ) {
	size_t	j = 0;
	int 	result = 0;

	while (str[j]) {
		if (str[j] == ' ')
			j++;
		if (isdigit(str[j]))
			this->s.push(str[j] - '0');
		else {
			result = calculation(this->s, str[j]);
			this->s.push(result);
		}
		j++;
	}
	std::cout << this->s.top() << std::endl;
	this->s.pop();
}
