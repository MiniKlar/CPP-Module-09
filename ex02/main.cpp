/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:51:22 by lomont            #+#    #+#             */
/*   Updated: 2026/02/14 05:26:44 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main( int argc, char** argv) {
	if (argc >= 2) {
		PmergeMe a(argc, argv);
		std::deque<int> result = a.fordJohnson(a.getList());
		double start = a.get_time();
		a.set_time();
		std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << argc - 1 << " elements with std::deque : " << a.get_time() - start << " us" << std::endl;
		std::cout << "Sorted: ";
		for (std::deque<int>::iterator it = result.begin(); it != result.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		bool sorted = std::is_sorted(result.begin(), result.end());
		std::cout << sorted;
	}
	else
		return (1);
	return (0);
}
