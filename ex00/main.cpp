/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 02:55:36 by lomont            #+#    #+#             */
/*   Updated: 2026/01/25 17:00:50 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char** argv) {
	if (argc == 2) {
		BitcoinDatabase _class;
		BitcoinExchange	_exchange(argv[argc - 1], _class);
		return (0);
	}
	std::cerr << "Error: could not open file." << std::endl;
	return (1);
}
