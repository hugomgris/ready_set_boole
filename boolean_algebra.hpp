/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_algebra.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:39:51 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/25 18:21:22 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOLEAN_ALGEBRA
# define BOOLEAN_ALGEBRA

# include <iostream>
# include <stack>
# include <set>
# include <vector>
# include <algorithm>
# include <exception>
# include <stdexcept>

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

//ex03
bool process_operand(bool a, bool b, char operand) {
    if (operand == '!') {
        return !b;
    } else if (operand == '&') {
		return (a && b);
	} else if (operand == '|') {
		return (a || b);
	} else if (operand == '^') {
		return (a ^ b);
	} else if (operand == '>') {
		return (!a || b);
	} else if (operand == '=') {
		return (a == b);
	} else return (false); // will never reach this point
}

bool check_operand(const char c) {
	char operands[] = {'!', '&', '|', '^', '>', '='};

	for (const char o : operands) {
		if (c == o) { return (true); }
	}

	return (false);
}

bool eval_formula(const std::string &expression) {
    std::stack<bool> data;
    
    for (char c : expression) {
        if (c == '0' || c == '1') {
            data.push(c == '1');
        } else if (c == '!') {
            if (data.empty()) {
                throw std::invalid_argument("Error: Invalid RPN expression: not enough operands");
            }
            bool operand = data.top(); 
            data.pop();
            data.push(!operand);
        } else if (check_operand(c)) {
            if (data.size() < 2) {
                throw std::invalid_argument("Error: Invalid RPN expression: not enough operands");
            }
            bool b = data.top(); data.pop();
            bool a = data.top(); data.pop();
            bool result = process_operand(a, b, c);
            data.push(result);
        } else {
            throw std::invalid_argument("Error: Invalid RPN expression: bad operand");
        }
    }

    if (data.size() != 1) {
        throw std::invalid_argument("Error: Invalid RPN expression: bad construction");
    }
    
    return data.top();
}

// ex04
void print_truth_table(const std::string &expression) {
	std::set<char> variables;

	for (const char c : expression) {
		if (c >= 'A' && c <= 'Z') {
			variables.insert(c);
		} else if (c == '1' || c == '0') {
			throw std::invalid_argument("Error: invalid expression for truth table: only A-Z characters and valid operators admitted");
		}
	}

	std::vector<char> vars(variables.begin(), variables.end());
	int n = vars.size();

	for (char var : vars) {
		std::cout << var << " | ";
	}
		std::cout << "Result" << std::endl;

		for (int i = 0; i < (1 << n); ++i) {
		std::string sub = expression;
		std::vector<bool> values(n);
		
		for (int j = 0; j < n; ++j) {
			values[j] = (i >> (n - 1 - j)) & 1;
			char value = values[j] ? '1' : '0';
			std::replace(sub.begin(), sub.end(), vars[j], value);
		}
		
		bool result = eval_formula(sub);
		
		for (bool val : values) {
			std::cout << (val ? 1 : 0) << " | ";
		}
		std::cout << (result ? 1 : 0) << std::endl;
	}
}

#endif