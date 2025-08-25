/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:30:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/25 15:08:15 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../boolean_algebra.hpp"

//ex00 main

int main(void) {
	std::cout << "\033[0;33mADDER test-----------\033[0m" << std::endl;
	std::cout << "3+5=" << adder(3, 5) << std::endl;
	std::cout << "123+123=" << adder(123, 123) << std::endl;
	std::cout << "5-3=" << adder(5, -3) << std::endl;
	std::cout << "0-9=" << adder(0, -9) << std::endl;
	std::cout << "51244+312412=" << adder(51244, 312412) << std::endl;
	std::cout << "0-0=" << adder(0, -0) << std::endl;

}