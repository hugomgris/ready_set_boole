/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_algebra.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:39:51 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/25 17:03:02 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOLEAN_ALGEBRA
# define BOOLEAN_ALGEBRA

# include <iostream>

// ex00
int adder(int a, int b) {
	while (b != 0) {
		int sum = a ^ b;
		int carry = (a & b) << 1;
		a = sum;
		b = carry;
	}

	return (a);
}

// ex01
// helper to change int sign (O(1) - constant time)
int negate(int n) {
    int all_ones = 0;
    for (int i = 0; i < 32; ++i) {
        all_ones = (all_ones << 1) | 1;
    }
    return adder(n ^ all_ones, 1);
}

int multiplier(int a, int b) {
    if (a == 0 || b == 0) return 0;

    int result = 0;
    bool result_negative = (a < 0) ^ (b < 0);

    if (a < 0) a = negate(a);
    if (b < 0) b = negate(b);

    while (b > 0) {
        if (b & 1) {
            result = adder(result, a);
        }
        a = a << 1;
        b = b >> 1;
    }

    if (result_negative) result = negate(result);
    return result;
}

// ex02
int gray_code(int n) {
	return n ^ (n >> 1);
}

#endif