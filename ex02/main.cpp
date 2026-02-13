/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:51:22 by lomont            #+#    #+#             */
/*   Updated: 2026/02/12 03:06:35 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main( int argc, char** argv) {
	if (argc >= 2) {
		PmergeMe a(argc, argv);
		std::deque<int> result = a.fordJohnson(a.getList());
		
		std::cout << "Sorted: ";
		for (std::deque<int>::iterator it = result.begin(); it != result.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
	else
		return (1);
	return (0);
}

		// std::deque<int> container;
		// std::deque<int> winner;

		// for (std::deque<int>::iterator it = container.begin(); it != container.end(); it++) {
		// 	std::cout << *it << " ";
		// }
		// std::cout << std::endl;
		// //boucle (bientôt récursive) pour trouver les gagnants
		// for (std::deque<int>::iterator it = container.begin(); it != container.end();) {
		// 	//faire des pas de 2 pour comparer 2 nombres, prendre le gagnant et le placer dans une autre deque
		// 	int a = *it;
		// 	//check avant si size pair ou impair pour gérer cas seul
		// 	if (++it == container.end())
		// 		break;
		// 	int b = *(it);
		// 	if (b > a) {
		// 		winner.push_back(b);
		// 		it = container.erase(it);
		// 	}
		// 	else {
		// 		winner.push_back(a);
		// 		it = container.erase(--it);
		// 		it++;
		// 	}
		// }

		// printResult(container, winner);
