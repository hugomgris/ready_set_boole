/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:30:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/25 17:53:58 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../boolean_algebra.hpp"

//ex03 main

int main(void) {
	try {
		std::cout << "\033[0;33mRPN test-----------\033[0m" << std::endl;
		std::cout << "10& - > " << ((eval_formula("10&") == 1) ? "true" : "false") << std::endl;
		std::cout << "10| - > " << ((eval_formula("10|") == 1) ? "true" : "false") << std::endl;
		std::cout << "10> - > " << ((eval_formula("10>") == 1) ? "true" : "false") << std::endl;
		std::cout << "10= - > " << ((eval_formula("10=") == 1) ? "true" : "false") << std::endl;
		std::cout << "1! -> " << ((eval_formula("1!") == 1) ? "true" : "false") << std::endl;
		std::cout << "0! -> " << ((eval_formula("0!") == 1) ? "true" : "false") << std::endl;
		std::cout << "1011||= - > " << ((eval_formula("1011||=") == 1) ? "true" : "false") << std::endl;
		std::cout << "1011||=1 - > " << ((eval_formula("1011||=1") == 1) ? "true" : "false") << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}
}