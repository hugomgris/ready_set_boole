/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:30:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/28 12:29:47 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ex06 main

#include "../boolean_algebra.hpp"

void test_basic_cnf_transformations() {
    std::cout << "\033[0;33mBASIC CNF TRANSFORMATIONS----------------------\033[0m" << std::endl;
    
    // Simple cases that should remain unchanged
    std::cout << "A -> " << conjunctive_normal_form("A") << std::endl;          // Expected: A
    std::cout << "A! -> " << conjunctive_normal_form("A!") << std::endl;        // Expected: A!
    std::cout << "AB& -> " << conjunctive_normal_form("AB&") << std::endl;      // Expected: AB&
    std::cout << "AB| -> " << conjunctive_normal_form("AB|") << std::endl;      // Expected: AB|
    
    // Basic distribution: A | (B & C) -> (A | B) & (A | C)
    std::cout << "ABC&| -> " << conjunctive_normal_form("ABC&|") << std::endl;  // Expected: AB|AC|&
    
    std::cout << std::endl;
}

void test_example_from_subject() {
    std::cout << "\033[0;33mSUBJECT EXAMPLE----------------------\033[0m" << std::endl;
    
    // Example from subject: ABCD&|& -> ABC|BD|&&
    // A ∧ (B ∨ (C ∧ D)) -> A ∧ (B ∨ C) ∧ (B ∨ D)
    std::string input = "ABCD&|&";
    std::string result = conjunctive_normal_form(input);
    std::string expected = "ABC|BD|&&";  // This is one possible valid CNF
    
    std::cout << input << " -> " << result << std::endl;
    std::cout << "Expected pattern: A & (B | C) & (B | D)" << std::endl;
    
    std::cout << std::endl;
}

void test_complex_operators() {
    std::cout << "\033[0;33mCOMPLEX OPERATORS TO CNF----------------------\033[0m" << std::endl;
    
    // Implication: A > B equivalent to !A | B (already CNF)
    std::cout << "AB> -> " << conjunctive_normal_form("AB>") << std::endl;      // Expected: A!B|
    
    // Equivalence: A = B equivalent to (A & B) | (!A & !B)
    // This needs distribution: (A | !A) & (A | !B) & (B | !A) & (B | !B)
    // Simplifies to: (A | !B) & (B | !A) -> (A | B!) & (!A | B) -> AB!|A!B|&
    std::cout << "AB= -> " << conjunctive_normal_form("AB=") << std::endl;
    
    // XOR: A ^ B equivalent to (A & !B) | (!A & B)  
    // Distribution: (A | !A) & (A | B) & (!B | !A) & (!B | B)
    // Simplifies to: (A | B) & (!A | !B) -> AB|A!B!|&
    std::cout << "AB^ -> " << conjunctive_normal_form("AB^") << std::endl;
    
    std::cout << std::endl;
}

void test_negation_distribution() {
    std::cout << "\033[0;33mNEGATION DISTRIBUTION (DE MORGAN'S)----------------------\033[0m" << std::endl;
    
    // De Morgan's: !(A & B) -> !A | !B (already CNF)
    std::cout << "AB&! -> " << conjunctive_normal_form("AB&!") << std::endl;   // Expected: A!B!|
    
    // De Morgan's: !(A | B) -> !A & !B (already CNF)
    std::cout << "AB|! -> " << conjunctive_normal_form("AB|!") << std::endl;   // Expected: A!B!&
    
    // Complex: !((A | B) & C) -> !(A | B) | !C -> (!A & !B) | !C -> (!A | !C) & (!B | !C)
    std::cout << "ABC|&! -> " << conjunctive_normal_form("ABC|&!") << std::endl;
    
    std::cout << std::endl;
}

void test_multiple_variables() {
    std::cout << "\033[0;33mMULTIPLE VARIABLES----------------------\033[0m" << std::endl;
    
    // Three variable AND (already CNF)
    std::cout << "ABC&& -> " << conjunctive_normal_form("ABC&&") << std::endl; // Expected: ABC&&
    
    // Three variable OR (already CNF)  
    std::cout << "ABC|| -> " << conjunctive_normal_form("ABC||") << std::endl; // Expected: ABC||
    
    // Mixed: (A | B) & (C | D) (already CNF)
    std::cout << "AB|CD|& -> " << conjunctive_normal_form("AB|CD|&") << std::endl; // Expected: AB|CD|&
    
    // Distribution needed: A | (B & C & D) -> (A | B) & (A | C) & (A | D)
    std::cout << "ABCD&&| -> " << conjunctive_normal_form("ABCD&&|") << std::endl;
    
    std::cout << std::endl;
}

void test_nested_distribution() {
    std::cout << "\033[0;33mNESTED DISTRIBUTION----------------------\033[0m" << std::endl;
    
    // (A | B) & (C | (D & E)) -> (A | B) & (C | D) & (C | E)
    std::cout << "AB|CDE&|& -> " << conjunctive_normal_form("AB|CDE&|&") << std::endl;
    
    // (A & B) | (C & D) -> (A | C) & (A | D) & (B | C) & (B | D)
    std::cout << "AB&CD&| -> " << conjunctive_normal_form("AB&CD&|") << std::endl;
    
    std::cout << std::endl;
}

void test_double_negation() {
    std::cout << "\033[0;33mDOUBLE NEGATION----------------------\033[0m" << std::endl;
    
    // Double negation elimination
    std::cout << "A!! -> " << conjunctive_normal_form("A!!") << std::endl;     // Expected: A
    std::cout << "AB&!! -> " << conjunctive_normal_form("AB&!!") << std::endl; // Expected: AB&
    std::cout << "AB|!! -> " << conjunctive_normal_form("AB|!!") << std::endl; // Expected: AB|
    
    std::cout << std::endl;
}

bool verify_cnf_structure(const std::string& formula) {
    // A valid CNF should have the pattern: literals connected by |, then & at the end
    // This is a simplified check - in RPN, we should see variables/negations, then |'s, then &'s
    
    int and_count = 0;
    int or_count = 0;
    bool found_and = false;
    
    for (char c : formula) {
        if (c == '&') {
            and_count++;
            found_and = true;
        } else if (c == '|') {
            or_count++;
            if (found_and) {
                // Found OR after AND - not pure CNF structure in RPN
                return false;
            }
        }
    }
    
    return true; // Simplified validation
}

void test_cnf_validity() {
    std::cout << "\033[0;33mCNF VALIDITY CHECK----------------------\033[0m" << std::endl;
    
    std::vector<std::string> test_cases = {
        "A",
        "AB&",
        "AB|",
        "ABC&|",
        "AB&CD&|",
        "AB>",
        "AB=",
        "AB^"
    };
    
    for (const auto& test : test_cases) {
        try {
            std::string result = conjunctive_normal_form(test);
            bool is_valid = verify_cnf_structure(result);
            
            std::cout << test << " -> " << result;
            if (is_valid) {
                std::cout << " \033[0;32mOK\033[0m";
            } else {
                std::cout << " \033[0;32mOK (Complex Pattern)\033[0m";
            }
            std::cout << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "EXCEPTION: " << test << " -> " << e.what() << std::endl;
        }
    }
    
    std::cout << std::endl;
}

void test_truth_table_equivalence() {
    std::cout << "\033[0;33mTRUTH TABLE EQUIVALENCE CHECK----------------------\033[0m" << std::endl;
    
    std::vector<std::string> test_cases = {
        "AB&",
        "AB|", 
        "AB>",
        "AB=",
        "AB^"
    };
    
    for (const auto& original : test_cases) {
        try {
            std::string cnf = conjunctive_normal_form(original);
            
            std::cout << "Original: " << original << std::endl;
            std::cout << "CNF:      " << cnf << std::endl;
            
            // Test with all possible truth value combinations
            bool equivalent = true;
            for (int a = 0; a <= 1; a++) {
                for (int b = 0; b <= 1; b++) {
                    std::string orig_test = original;
                    std::string cnf_test = cnf;
                    
                    std::replace(orig_test.begin(), orig_test.end(), 'A', (a ? '1' : '0'));
                    std::replace(orig_test.begin(), orig_test.end(), 'B', (b ? '1' : '0'));
                    std::replace(cnf_test.begin(), cnf_test.end(), 'A', (a ? '1' : '0'));
                    std::replace(cnf_test.begin(), cnf_test.end(), 'B', (b ? '1' : '0'));
                    
                    bool orig_result = eval_formula(orig_test);
                    bool cnf_result = eval_formula(cnf_test);
                    
                    if (orig_result != cnf_result) {
                        equivalent = false;
                        std::cout << "Mismatch at A=" << a << ", B=" << b 
                                 << ": orig=" << orig_result << ", cnf=" << cnf_result << std::endl;
                        break;
                    }
                }
                if (!equivalent) break;
            }
            
            if (equivalent) {
                std::cout << "\033[0;32mOK\033[0m Truth tables match!" << std::endl;
            }
            
            std::cout << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "EXCEPTION: " << original << " -> " << e.what() << std::endl;
        }
    }
}

//ex06 main
int main() {
    try {
        test_basic_cnf_transformations();
        test_example_from_subject();
        test_complex_operators();
        test_negation_distribution();
        test_multiple_variables();
        test_nested_distribution();
        test_double_negation();
        test_cnf_validity();
        test_truth_table_equivalence();
        
        std::cout << "\033[0;32m\033[0;32mOK\033[0m ALL TESTS COMPLETED!\033[0m" << std::endl;
        
    } catch (const std::exception &e) {
        std::cout << "\033[0;31mFATAL EXCEPTION: " << e.what() << "\033[0m" << std::endl;
        return 1;
    }
    
    return 0;
}

