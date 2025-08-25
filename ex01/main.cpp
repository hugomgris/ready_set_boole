/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:30:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/25 16:03:43 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../boolean_algebra.hpp"

//ex01 main

int main(void) {
	std::cout << "\033[0;33mMULTIPLIER test-----------\033[0m" << std::endl;
	std::cout << "3*2=" << multiplier(3, 2) << std::endl;
	std::cout << "9*1=" << multiplier(9, 1) << std::endl;
	std::cout << "5*5=" << multiplier(5, 5) << std::endl;
	std::cout << "100*-2=" << multiplier(100, -2) << std::endl;
	std::cout << "-100*2=" << multiplier(-100, 2) << std::endl;
	std::cout << "-100*-2=" << multiplier(-100, -2) << std::endl;
	std::cout << "6*0=" << multiplier(6, 0) << std::endl;
	std::cout << "0*6=" << multiplier(6, 0) << std::endl;
	std::cout << "100000*200000=" << multiplier(100000, 200000) << std::endl;
}