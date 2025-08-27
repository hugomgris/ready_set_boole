/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:30:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/27 18:03:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../boolean_algebra.hpp"

void test_basic_transformations() {
    std::cout << "\033[0;33mBASIC TRANSFORMATIONS----------------------\033[0m" << std::endl;
    
    // De Morgan's Laws
    std::cout << "AB&! -> " << negation_normal_form("AB&!") << std::endl;  // Expected: A!B!|
    std::cout << "AB|! -> " << negation_normal_form("AB|!") << std::endl;  // Expected: A!B!&
    
    // Material Condition (Implication)
    std::cout << "AB> -> " << negation_normal_form("AB>") << std::endl;    // Expected: A!B|
    
    // Equivalence  
    std::cout << "AB= -> " << negation_normal_form("AB=") << std::endl;    // Expected: AB&A!B!&|
    
    // XOR
    std::cout << "AB^ -> " << negation_normal_form("AB^") << std::endl;    // Expected: AB!&A!B&|
    
    std::cout << std::endl;
}

void test_double_negation() {
    std::cout << "\033[0;33mDOUBLE NEGATION ELIMINATION----------------------\033[0m" << std::endl;
    
    // Double negation on variables
    std::cout << "A!! -> " << negation_normal_form("A!!") << std::endl;    // Expected: A
    std::cout << "B!! -> " << negation_normal_form("B!!") << std::endl;    // Expected: B
    
    // Triple negation
    std::cout << "A!!! -> " << negation_normal_form("A!!!") << std::endl;  // Expected: A!
    
    // Double negation on expressions
    std::cout << "AB&!! -> " << negation_normal_form("AB&!!") << std::endl; // Expected: AB&
    std::cout << "AB|!! -> " << negation_normal_form("AB|!!") << std::endl; // Expected: AB|
    
    std::cout << std::endl;
}

void test_complex_nested() {
    std::cout << "\033[0;33mCOMPLEX NESTED EXPRESSIONS----------------------\033[0m" << std::endl;
    
    // Nested negations with De Morgan's
    std::cout << "ABC&|! -> " << negation_normal_form("ABC&|!") << std::endl; // Expected: A!BC&!&
    std::cout << "ABC|&! -> " << negation_normal_form("ABC|&!") << std::endl; // Expected: A!BC|!|
    
    // Multiple operators
    std::cout << "AB&CD|> -> " << negation_normal_form("AB&CD|>") << std::endl; // Expected: AB&!CD||
    std::cout << "AB>CD>& -> " << negation_normal_form("AB>CD>&") << std::endl; // Expected: A!B|C!D|&
    
    // Equivalence with other operators
    std::cout << "AB=C& -> " << negation_normal_form("AB=C&") << std::endl;   // Expected: AB&A!B!&|C&
    
    std::cout << std::endl;
}

void test_single_variables() {
    std::cout << "\033[0;33mSINGLE VARIABLES----------------------\033[0m" << std::endl;
    
    // Variables (should remain unchanged)
    std::cout << "A -> " << negation_normal_form("A") << std::endl;          // Expected: A
    std::cout << "B -> " << negation_normal_form("B") << std::endl;          // Expected: B
    
    // Single negations (already in NNF)
    std::cout << "A! -> " << negation_normal_form("A!") << std::endl;        // Expected: A!
    std::cout << "B! -> " << negation_normal_form("B!") << std::endl;        // Expected: B!
    
    std::cout << std::endl;
}

void test_multiple_variables() {
    std::cout << "\033[0;33mMULTIPLE VARIABLES----------------------\033[0m" << std::endl;
    
    // Three variables
    std::cout << "ABC&& -> " << negation_normal_form("ABC&&") << std::endl;  // Expected: ABC&&
    std::cout << "ABC|| -> " << negation_normal_form("ABC||") << std::endl;  // Expected: ABC||
    std::cout << "ABC&&! -> " << negation_normal_form("ABC&&!") << std::endl; // Expected: A!B!C!||
    
    // Four variables
    std::cout << "ABCD&&&! -> " << negation_normal_form("ABCD&&&!") << std::endl; // Expected: A!B!C!D!|||
    
    std::cout << std::endl;
}

void test_edge_cases() {
    std::cout << "\033[0;33mEDGE CASES----------------------\033[0m" << std::endl;
    
    // Chained implications
    std::cout << "AB>C> -> " << negation_normal_form("AB>C>") << std::endl;  // Expected: A!B|!C|
    
    // Mixed equivalences and implications
    std::cout << "AB=C> -> " << negation_normal_form("AB=C>") << std::endl;  // Expected: AB&A!B!&|!C|
    
    // Complex XOR combinations
    std::cout << "AB^C^ -> " << negation_normal_form("AB^C^") << std::endl;  // Expected: complex...
    
    std::cout << std::endl;
}

void verify_nnf_property(const std::string& original, const std::string& nnf) { 
    for (size_t i = 0; i < nnf.length(); i++) {
        if (nnf[i] == '!') {
            // Check if the negation is followed by a variable
            if (i == 0 || (nnf[i-1] < 'A' || nnf[i-1] > 'Z')) {
                std::cout << "❌ INVALID NNF: " << original << " -> " << nnf 
                         << " (negation not on variable)" << std::endl;
                return;
            }
        }
        
        // Check for forbidden operators in output
        if (nnf[i] == '^' || nnf[i] == '>' || nnf[i] == '=') {
            std::cout << "❌ INVALID NNF: " << original << " -> " << nnf 
                     << " (contains forbidden operator: " << nnf[i] << ")" << std::endl;
            return;
        }
    }
    
    std::cout << "✅ VALID NNF: " << original << " -> " << nnf << std::endl;
}

void test_nnf_validity() {
    std::cout << "\033[0;33mNNF VALIDITY CHECK----------------------\033[0m" << std::endl;
    
    std::vector<std::string> test_cases = {
        "AB&!",
        "AB|!",
        "AB>",
        "AB=",
        "AB^",
        "ABC&&!",
        "AB>C>",
        "A!!"
    };
    
    for (const auto& test : test_cases) {
        try {
            std::string result = negation_normal_form(test);
            verify_nnf_property(test, result);
        } catch (const std::exception& e) {
            std::cout << "❌ EXCEPTION: " << test << " -> " << e.what() << std::endl;
        }
    }
    
    std::cout << std::endl;
}

//ex04 main
int main() {
    try {
        std::cout << "\033[0;32m🚀 COMPREHENSIVE NNF TESTING SUITE 🚀\033[0m" << std::endl;
        std::cout << "==========================================" << std::endl << std::endl;
        
        test_single_variables();
        test_basic_transformations();
        test_double_negation();
        test_complex_nested();
        test_multiple_variables();
        test_edge_cases();
        test_nnf_validity();
        
        std::cout << "\033[0;32m✅ ALL TESTS COMPLETED!\033[0m" << std::endl;
        
    } catch (const std::exception &e) {
        std::cout << "\033[0;31m❌ FATAL EXCEPTION: " << e.what() << "\033[0m" << std::endl;
        return 1;
    }
    
    return 0;
}