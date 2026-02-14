/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:25 by lomont            #+#    #+#             */
/*   Updated: 2026/02/14 05:31:42 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe( int argc, char** argv ) : sav(-1) {
	std::cout << "Default PmergeMe constructor called" << std::endl;
	for (int i = 1; i < argc; i++)
		addNumber(&this->list, parseNumbers(argv[i]));
	if (gettimeofday(&_time, NULL) == -1)
		exit (1);
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

std::deque<int>& PmergeMe::getList( void ) {
	return (this->list);
}

double	PmergeMe::get_time( void ) {
	return (static_cast<double>(this->_time.tv_sec) * 1000000.0 + this->_time.tv_usec);
}

void PmergeMe::set_time( void ) {
	gettimeofday(&_time, NULL);
	return ;
}

bool	specialSort(const std::pair<int, int>& i, const std::pair<int, int>& j) {
	return (i.first < j.first);
}

std::deque<int> PmergeMe::fordJohnson(std::deque<int> container) {
	int								leftover;
	std::deque<int> 				winner;
	std::deque<std::pair<int, int> >	pairs;
	//cas d'arrêt
	if (container.size() <= 1)
		return std::deque<int>(container);

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

		winner.push_back(pairs.back().first);
	}
	std::deque<int>result = fordJohnson(winner);
	std::sort(pairs.begin(), pairs.end(), specialSort);
	result.push_front(pairs[0].second);
	for (int k = 3; Jacobsthal(k - 1) <= static_cast<int>(pairs.size()); k++)
		binary_search(result, pairs, Jacobsthal(k), Jacobsthal(k - 1));
	if (leftover != -1) {
		std::deque<int>::iterator iteratorBi = std::lower_bound(result.begin(), result.end(), leftover);
		result.insert(iteratorBi, leftover);
	}
	return (result);
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
		binary_insert(S, pairs[i].first, pairs[i].second);
	}
}

void	PmergeMe::binary_insert(std::deque<int>& S, int Ai, int Bi) {
	std::deque<int>::iterator it = std::lower_bound(S.begin(), S.end(), Ai);
	std::deque<int>::iterator iteratorBi = std::lower_bound(S.begin(), it, Bi);
	S.insert(iteratorBi, Bi);
}
