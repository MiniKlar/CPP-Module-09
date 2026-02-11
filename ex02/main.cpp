/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:51:22 by lomont            #+#    #+#             */
/*   Updated: 2026/02/11 17:32:51 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main( int argc, char** argv) {
	if (argc >= 2) {
		std::deque<int> container;
		for (int i = 1; i < argc; i++) {
			addNumber(&container, parseNumbers(argv[i]));
		}
		for (std::deque<int>::iterator it = container.begin(); it != container.end(); it++) {
			std::cout << *it << std::endl;
		}
	}
	else
		return (1);
	return (0);
}
