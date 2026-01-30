/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:13:40 by lomont            #+#    #+#             */
/*   Updated: 2026/01/30 16:51:40 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main( int argc, char** argv ) {

	if (argc != 2) {
		std::cerr << "Please verify your input command: ./RPN '*expression*'" << std::endl;
		return (1);
	}

	//variable containing the expression to parse
	char* str = argv[argc - 1];

	//check if str is only */+- and nbr
	if (!str[0]) {
		std::cout << "Error" << std::endl;
		return (5);
	}
	for (size_t i = 0; str[i]; i++) {
		if (i % 2 == 1) {
			if (str[i] != ' ') {
				std::cerr << "Error" << std::endl;
				return (4);
			}
		}
		else if (!isdigit(str[i]) && !checkOperator(str[i]) ) {
			std::cerr << "Error" << std::endl;
			return (2);
		}
		if (str[i + 1] == '\0') {
			if (!checkOperatorNumbers(str[i], true)) {
				std::cerr << "Error" << std::endl;
				return (3);
			}
		}
		checkOperatorNumbers(str[i], false);
		// check qu'un operateur ne soit pas entre 2 chiffres "2 * 3"
	}

	std::cout << "Parsing OK" << std::endl;

	std::stack<int> stack;

	size_t	j = 0;
	int result = 0;
	while (str[j]) {
		//check si c'est un espace, si oui, j++
		if (str[j] == ' ') {
			j++;
		}
		//si c'est un nbr mettre dans la stack
		if (isdigit(str[j])) {
			stack.push(str[j] - '0');
		}
		//else si c'est un operateur, prendre le dessus de la stack, faire le calcul et push le résultat dans la stack
		else {
			//faire une fonction qui prendra les deux nombres et qui les sépare dans des variables, ensuite il checkera le signe et returnera l'opération pour mettre dans la variable result
			result = calculation(stack, str[j]);
			stack.push(result);
		}
		j++;
	}
	std::cout << stack.top() << std::endl;
	return (0);
}

//. "1 2 * 2 / 2 * 2 4 - +"
