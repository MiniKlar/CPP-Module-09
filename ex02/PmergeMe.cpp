/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:25 by lomont            #+#    #+#             */
/*   Updated: 2026/02/13 03:28:55 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::deque<int> t;
int i = 0;

PmergeMe::PmergeMe( int argc, char** argv ) : sav(-1) {
	std::cout << "Default PmergeMe constructor called" << std::endl;
	for (int i = 1; i < argc; i++)
		addNumber(&this->list, parseNumbers(argv[i]));
	return ;
}

PmergeMe::~PmergeMe( void ) {
	std::cout << "PmergeMe destructor called" << std::endl;
	return ;
}

int		parseNumbers( const char* str) {
	double	number;

	if (!isNumber(str))
		printError("It's not a number");
	number = atof(str);
	if (hasOverflow(number)) {
		printError("Overflow error");
	}
	return (static_cast<int>(number));
}

bool	hasOverflow(double n) {
	if (n > INT_MAX) {
		return (true);
	}
	return (false);
}

bool isNumber(const char* str) {
	for (size_t i = 0; i < strlen(str); i++) {
		if (str[0] == '-')
			printError("Number negative");
		if (!isnumber(str[i]))
			return (false);
	}
	return (true);
}

void	addNumber(std::deque<int>* c, int n) {
	c->push_back(n);
	return ;
}

void	printError(std::string Error) {
	std::cerr << Error << ", exiting program..." << std::endl; //for debug purpose only, for correction please put "Error"
	exit(1);
}

void	PmergeMe::printResult( void ) {
	int i = 1;
	for (std::deque<std::pair<int, int> >::iterator it = this->winners.begin(); it != this->winners.end(); it++) {
		std::cout << "a" << i << " = " << it->first << " b" << i << " = " << it->second << std::endl;
		i++;
	}
	std::cout << "Voici la valeur save = " << this->sav << std::endl;
}

std::deque<int> PmergeMe::fordJohnson(std::deque<int> container) {
	int								i;
	int								leftover;
	std::deque<int> 				winner;
	std::deque<std::pair<int, int>>	pairs;
	//cas d'arrêt
	if (container.size() <= 1)
		return std::deque<int>(container);

	i = 0;
	leftover = -1;
	//pour chaque élément de la liste d'entrée => créer une paire selon la comparaison
	std::deque<int>::iterator it = container.begin();
	while (it != container.end()) {
		int a = *it;
		it++;

		if (it == container.end()) {
			leftover = a;
			break;
		}

		int b = *it;
		it++;


		if (b > a) {
			pairs.push_back(std::make_pair(b, a));
		}
		else {
			pairs.push_back(std::make_pair(a, b));
		}

		winner.push_back(pairs[i].first);
		i++;
	}
	std::deque<int>result = fordJohnson(winner);
	binary_search(result, pairs, Jacobsthal(i++), Jacobsthal(i));
	std::deque<int>::iterator iteratorBi = std::lower_bound(result.begin(), result.end(), leftover);
	result.insert(iteratorBi, leftover);
	return (result);
}

std::deque<int>& PmergeMe::getList( void ) {
	return (this->list);
}

int		PmergeMe::Jacobsthal(int n) {
	if (n == 0)
		return (0);
	else if (n == 1)
		return (1);
	else
		return (Jacobsthal(n - 1) + 2 * (Jacobsthal(n - 2)));
}

void	PmergeMe::binary_search(std::deque<int>& S, std::deque<std::pair<int, int> >& pairs, int Jacobsthal, int prevJacobsthal) {
	for (int i = std::min(Jacobsthal - 1, static_cast<int>(pairs.size() - 1)); prevJacobsthal - 1 < i; i--) {
		binary_insert(S, pairs, pairs[i].first);
	}
		//donc on va chercher l'extrémité de 1 par exemple donc on sait que a1 > b1, on rajoute b1 au début (on cherche la valeur assigné à a1 (gagnant, perdant)). Si c'était 3, on chercherai a3 > b3 et la pair et on place b3 entre [b1, a1, a2] donc [b1, a1, a2]
			//on met ça dans la fonction qui va faire une comparaison dans [b1, a1, a2] pour placer b3. et ainsi de suite
}

void	binary_insert(std::deque<int>& S, std::deque<std::pair<int, int> >& pairs, int Ai) {
	std::deque<int>::iterator it = std::lower_bound(S.begin(), S.end(), Ai);
	int Bi;
	size_t i = 0;
	for (std::deque<std::pair<int, int> >::iterator iterator = pairs.begin(); iterator != pairs.end(); iterator++) {
		if (iterator->first == *it) {
			Bi = iterator->second;
			break;
		}
	}
	std::deque<int>::iterator iteratorBi = std::lower_bound(S.begin(), it, Bi);
	S.insert(iteratorBi, Bi);
}
