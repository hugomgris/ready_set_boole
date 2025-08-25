/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:30:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/25 17:07:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../boolean_algebra.hpp"

//ex02 main

int main(void) {
	std::cout << "\033[0;33mGRAY CODE test-----------\033[0m" << std::endl;
	for (int i = 0; i < 9; ++i) {
		std::cout << "gray code of " << i << " -> " << gray_code(i) << std::endl;
	}
}