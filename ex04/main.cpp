/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:30:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/27 18:01:59 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../boolean_algebra.hpp"

//ex04 main

int main() {
    try {
        std::cout << "NNF Tests" << std::endl;
        
        std::cout << "AB&! -> " << negation_normal_form("AB&!") << std::endl;  // Expected: A!B!|
        std::cout << "AB|! -> " << negation_normal_form("AB|!") << std::endl;  // Expected: A!B!&
        std::cout << "AB> -> " << negation_normal_form("AB>") << std::endl;    // Expected: A!B|
        std::cout << "AB= -> " << negation_normal_form("AB=") << std::endl;    // Expected: AB&A!B!&|
        std::cout << "AB^ -> " << negation_normal_form("AB^") << std::endl;    // Expected: AB!&A!B&|
        
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}