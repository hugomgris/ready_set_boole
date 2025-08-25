/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_algebra.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:39:51 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/25 14:58:34 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOLEAN_ALGEBRA
# define BOOLEAN_ALGEBRA

# include <iostream>

// ex00
template<typename T>
T adder(T a, T b) {
	while (b != 0) {
		T sum = a ^ b;
		T carry = (a & b) << 1;
		a = sum;
		b = carry;
	}

	return (a);
}

#endif