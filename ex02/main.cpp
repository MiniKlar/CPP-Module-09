/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:51:22 by lomont            #+#    #+#             */
/*   Updated: 2026/02/15 03:20:10 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main( int argc, char** argv) {
	if (argc >= 3) {
		PmergeMe a(argc, argv);
		ft_performCalculationAndPrintIt(a, argv, argc - 1, true);
		ft_performCalculationAndPrintIt(a, argv, argc - 1, false);
	}
	else {
		std::cerr << "Please use './PmergeMe args1 args2 ..." << std::endl;
		return (1);
	}
	return (0);
}
