/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:13:40 by lomont            #+#    #+#             */
/*   Updated: 2026/02/01 22:48:47 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main( int argc, char** argv ) {

	if (argc != 2) {
		std::cerr << "Please verify your input command: ./RPN '*expression*'" << std::endl;
		return (1);
	}
	else {
		RPN a(argc, argv);
		return (0);
	}
}

//. "1 2 * 2 / 2 * 2 4 - +"
