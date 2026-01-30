/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:13:45 by lomont            #+#    #+#             */
/*   Updated: 2026/01/30 16:49:46 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

bool	checkOperator(char c);
bool	checkOperatorNumbers(char c, bool lastChar);
int		calculation(std::stack<int>& stack, char _operator);

#endif
