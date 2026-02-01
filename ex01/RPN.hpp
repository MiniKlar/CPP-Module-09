/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:13:45 by lomont            #+#    #+#             */
/*   Updated: 2026/02/01 23:06:34 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <cstdlib>

class RPN
{
	private:
		std::stack<int>	s;
		const char*		str;
	public:
		//Canonical form
		RPN( int argc, char** argv );
		RPN( const RPN& src );
		RPN& operator=( const RPN& other );
		~RPN( void );

		//Member functions
		void	ft_error( void );
		void	parsing( void );
		void	execution( void );
		bool	checkOperator(char c);
		bool	checkOperatorNumbers(char c, bool lastChar);
		bool	checkexpression(const char* str);
		int		calculation(std::stack<int>& stack, char _operator);
};

#endif
