/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 01:09:25 by lomont            #+#    #+#             */
/*   Updated: 2026/02/15 03:21:34 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
void	ft_printAfterSorted(T & container) {
	std::cout << "After:  ";
	for (typename T::iterator it = container.begin(); it != container.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void	ft_performCalculationAndPrintIt(T & a, char** argv, int len, bool isDeque) {
	double	start;

	start = a.ft_getTime();
	if (isDeque) {
		std::deque<int> result = a.ft_fordJohnson(a.ft_getList());
		a.ft_setTime();
		if (!ft_checkDuplicates(result))
			ft_printError("Duplicates found");
		ft_printBeforeSorted(argv);
		ft_printAfterSorted(result);
		std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << len << " elements with std::deque  : " << a.ft_getTime() - start << " us" << std::endl;
	}
	else {
		std::vector<int> result = a.ft_fordJohnsonVector(a.ft_getVList());
		a.ft_setTime();
		std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << len << " elements with std::vector : " << a.ft_getTime() - start << " us" << std::endl;
	}

	//Uncomment this two functions to see if the numbers are sorted.
	// bool sorted = std::is_sorted(result.begin(), result.end());
	// std::cout << sorted;
}
