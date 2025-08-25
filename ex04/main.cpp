/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:30:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/25 18:19:13 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../boolean_algebra.hpp"

//ex04 main

int main(void) {
	try {
		std::cout << "\033[0;33mTRUTH TABLE tests-----------\033[0m" << std::endl;
		std::cout << "expresion -> AB&C|" << std::endl << std::endl;
		print_truth_table("AB&C|");
		std::cout << std::endl;

		std::cout << "expresion -> ABCD||=E" << std::endl << std::endl;
		print_truth_table("ABCD||=");
		std::cout << std::endl;

		std::cout << "expresion -> 1010||=" << std::endl << std::endl;
		print_truth_table("1010||=");
		std::cout << std::endl;
	} catch (const std::invalid_argument &e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	try {
		std::cout << "expresion -> ABCD||=E" << std::endl << std::endl;
		print_truth_table("ABCD||=E");
	} catch (const std::invalid_argument &e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}
}