/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:57:25 by lomont            #+#    #+#             */
/*   Updated: 2026/02/15 03:16:50 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//Canonical form

PmergeMe::PmergeMe( int argc, char** argv ) {
	//std::cout << "Default PmergeMe constructor called" << std::endl;
	for (int i = 1; i < argc; i++) {
		ft_addNumber(&this->list, &this->Vlist, ft_parseNumbers(argv[i]));
	}
	if (gettimeofday(&_time, NULL) == -1)
		exit (1);
	return ;
}

PmergeMe::~PmergeMe( void ) {
	//std::cout << "PmergeMe destructor called" << std::endl;
	return ;
}

//missing 2 functions

std::deque<int>&	PmergeMe::ft_getList( void ) {
	return (this->list);
}

std::vector<int>&	PmergeMe::ft_getVList( void ) {
	return (this->Vlist);
}

//Ford Johnson algorithm and Jacobsthal numbers functions for deque

std::deque<int> PmergeMe::ft_fordJohnson(std::deque<int> container) {
	std::deque<std::pair<int, int> >	pairs;
	std::deque<int>						winner;
	int									leftover;
	int									a, b;

	if (container.size() <= 1)
		return std::deque<int>(container);
	leftover = -1;
	std::deque<int>::iterator it = container.begin();
	while (it != container.end()) {
		a = *it;
		it++;
		if (it == container.end()) {
			leftover = a;
			break;
		}
		b = *it;
		it++;
		if (b > a) {
			pairs.push_back(std::make_pair(b, a));
		}
		else {
			pairs.push_back(std::make_pair(a, b));
		}

		winner.push_back(pairs.back().first);
	}
	std::deque<int>result = ft_fordJohnson(winner);
	std::sort(pairs.begin(), pairs.end(), ft_specialSort);
	result.push_front(pairs[0].second);
	for (int k = 3; ft_Jacobsthal(k - 1) <= static_cast<int>(pairs.size()); k++)
		ft_binary_search(result, pairs, ft_Jacobsthal(k), ft_Jacobsthal(k - 1));
	if (leftover != -1) {
		std::deque<int>::iterator iteratorBi = std::lower_bound(result.begin(), result.end(), leftover);
		result.insert(iteratorBi, leftover);
	}
	return (result);
}

int		PmergeMe::ft_Jacobsthal(int n) {
	if (n == 0)
		return (0);
	else if (n == 1)
		return (1);
	else
		return (ft_Jacobsthal(n - 1) + 2 * (ft_Jacobsthal(n - 2)));
}

void	PmergeMe::ft_binary_search(std::deque<int>& S, std::deque<std::pair<int, int> >& pairs, int Jacobsthal, int prevJacobsthal) {
	for (int i = std::min(Jacobsthal - 1, static_cast<int>(pairs.size() - 1)); prevJacobsthal - 1 < i; i--) {
		ft_binary_insert(S, pairs[i].first, pairs[i].second);
	}
}

void	PmergeMe::ft_binary_insert(std::deque<int>& S, int Ai, int Bi) {
	std::deque<int>::iterator it = std::lower_bound(S.begin(), S.end(), Ai);
	std::deque<int>::iterator iteratorBi = std::lower_bound(S.begin(), it, Bi);
	S.insert(iteratorBi, Bi);
}

//Ford Johnson algorithm and Jacobsthal numbers functions for deque

std::vector<int> PmergeMe::ft_fordJohnsonVector(std::vector<int> container) {
	std::vector<std::pair<int, int> >	pairs;
	std::vector<int>					winner;
	int									leftover;
	int									a, b;

	if (container.size() <= 1)
		return std::vector<int>(container);
	leftover = -1;
	std::vector<int>::iterator it = container.begin();
	while (it != container.end()) {
		a = *it;
		it++;
		if (it == container.end()) {
			leftover = a;
			break;
		}
		b = *it;
		it++;
		if (b > a) {
			pairs.push_back(std::make_pair(b, a));
		}
		else {
			pairs.push_back(std::make_pair(a, b));
		}

		winner.push_back(pairs.back().first);
	}
	std::vector<int>result = ft_fordJohnsonVector(winner);
	std::sort(pairs.begin(), pairs.end(), ft_specialSort);
	result.insert(result.begin(), pairs[0].second);
	for (int k = 3; ft_Jacobsthal(k - 1) <= static_cast<int>(pairs.size()); k++)
		ft_binarySearchVector(result, pairs, ft_Jacobsthal(k), ft_Jacobsthal(k - 1));
	if (leftover != -1) {
		std::vector<int>::iterator iteratorBi = std::lower_bound(result.begin(), result.end(), leftover);
		result.insert(iteratorBi, leftover);
	}
	return (result);
}


void	PmergeMe::ft_binarySearchVector(std::vector<int>& S, std::vector<std::pair<int, int> >& pairs, int Jacobsthal, int prevJacobsthal) {
	for (int i = std::min(Jacobsthal - 1, static_cast<int>(pairs.size() - 1)); prevJacobsthal - 1 < i; i--) {
		ft_binaryInsertVector(S, pairs[i].first, pairs[i].second);
	}
}

void	PmergeMe::ft_binaryInsertVector(std::vector<int>& S, int Ai, int Bi) {
	std::vector<int>::iterator it = std::lower_bound(S.begin(), S.end(), Ai);
	std::vector<int>::iterator iteratorBi = std::lower_bound(S.begin(), it, Bi);
	S.insert(iteratorBi, Bi);
}

//Time functions

double	PmergeMe::ft_getTime( void ) {
	return (static_cast<double>(this->_time.tv_sec) * 1000000.0 + this->_time.tv_usec);
}

void PmergeMe::ft_setTime( void ) {
	gettimeofday(&this->_time, NULL);
	return ;
}
