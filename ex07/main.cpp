/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:30:50 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/28 14:45:18 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ex07 main

#include "../boolean_algebra.hpp"

void test_basic_satisfiability() {
    std::cout << "\033[0;33mBASIC SATISFIABILITY TESTS----------------------\033[0m" << std::endl;
    
    // Always true (tautologies)
    std::cout << "A -> " << (sat("A") ? "SAT" : "UNSAT") << std::endl;                    // SAT (A can be true)
    std::cout << "AA| -> " << (sat("AA|") ? "SAT" : "UNSAT") << std::endl;               // SAT (A | A = A)
    std::cout << "AA!| -> " << (sat("AA!|") ? "SAT" : "UNSAT") << std::endl;             // SAT (A | !A = true)
    std::cout << "AB| -> " << (sat("AB|") ? "SAT" : "UNSAT") << std::endl;               // SAT (A | B, can be true)
    
    // Always false (contradictions)
    std::cout << "AA!& -> " << (sat("AA!&") ? "SAT" : "UNSAT") << std::endl;             // UNSAT (A & !A = false)
    std::cout << "A!A!& -> " << (sat("A!A!&") ? "SAT" : "UNSAT") << std::endl;           // UNSAT (!A & !A = !A, but A is also needed)
    
    // Sometimes true (contingencies)
    std::cout << "AB& -> " << (sat("AB&") ? "SAT" : "UNSAT") << std::endl;               // SAT (A & B, when both true)
    std::cout << "AB^ -> " << (sat("AB^") ? "SAT" : "UNSAT") << std::endl;               // SAT (A XOR B, when exactly one is true)
    
    std::cout << std::endl;
}

void test_complex_operators() {
    std::cout << "\033[0;33mCOMPLEX OPERATORS SATISFIABILITY----------------------\033[0m" << std::endl;
    
    // Implication tests
    std::cout << "AB> -> " << (sat("AB>") ? "SAT" : "UNSAT") << std::endl;               // SAT (A > B, false when A=true, B=false)
    std::cout << "A!A> -> " << (sat("A!A>") ? "SAT" : "UNSAT") << std::endl;             // SAT (!A > A, equivalent to A | A = A)
    std::cout << "AA!> -> " << (sat("AA!>") ? "SAT" : "UNSAT") << std::endl;             // SAT (A > !A, equivalent to !A | !A = !A)
    
    // Equivalence tests  
    std::cout << "AB= -> " << (sat("AB=") ? "SAT" : "UNSAT") << std::endl;               // SAT (A = B, when both have same value)
    std::cout << "AA= -> " << (sat("AA=") ? "SAT" : "UNSAT") << std::endl;               // SAT (A = A, always true)
    std::cout << "AA!= -> " << (sat("AA!=") ? "SAT" : "UNSAT") << std::endl;             // UNSAT (A = !A, never true)
    
    // XOR tests
    std::cout << "AA^ -> " << (sat("AA^") ? "SAT" : "UNSAT") << std::endl;               // UNSAT (A XOR A = false)
    std::cout << "AA!^ -> " << (sat("AA!^") ? "SAT" : "UNSAT") << std::endl;             // SAT (A XOR !A = true)
    
    std::cout << std::endl;
}

void test_unsatisfiable_formulas() {
    std::cout << "\033[0;33mUNSATISFIABLE FORMULAS----------------------\033[0m" << std::endl;
    
    // Classic contradictions
    std::cout << "AA!& -> " << (sat("AA!&") ? "SAT" : "UNSAT") << std::endl;             // UNSAT (A and not A)
    std::cout << "AB&A!|& -> " << (sat("AB&A!|&") ? "SAT" : "UNSAT") << std::endl;       // UNSAT ((A & B) & !A)
    std::cout << "AB|A!B!&& -> " << (sat("AB|A!B!&&") ? "SAT" : "UNSAT") << std::endl;   // UNSAT ((A | B) & (!A & !B))
    
    // Complex contradictions
    std::cout << "ABC&&A!| -> " << (sat("ABC&&A!|") ? "SAT" : "UNSAT") << std::endl;     // UNSAT ((A & B & C) & !A) - impossible
    std::cout << "AB=A!B!= -> " << (sat("AB=A!B!=") ? "SAT" : "UNSAT") << std::endl;     // UNSAT (A=B and A=!B simultaneously)
    
    std::cout << std::endl;
}

void test_multiple_variables() {
    std::cout << "\033[0;33mMULTIPLE VARIABLES----------------------\033[0m" << std::endl;
    
    // Three variables
    std::cout << "ABC&& -> " << (sat("ABC&&") ? "SAT" : "UNSAT") << std::endl;           // SAT (A & B & C, when all true)
    std::cout << "ABC|| -> " << (sat("ABC||") ? "SAT" : "UNSAT") << std::endl;           // SAT (A | B | C, when at least one true)
    std::cout << "ABC&&A!| -> " << (sat("ABC&&A!|") ? "SAT" : "UNSAT") << std::endl;     // UNSAT (A & B & C & !A)
    
    // Four variables
    std::cout << "ABCD&&&-> " << (sat("ABCD&&&") ? "SAT" : "UNSAT") << std::endl;        // SAT (all true)
    std::cout << "ABCD|||-> " << (sat("ABCD|||") ? "SAT" : "UNSAT") << std::endl;        // SAT (at least one true)
    
    // Mixed operations
    std::cout << "AB&CD&| -> " << (sat("AB&CD&|") ? "SAT" : "UNSAT") << std::endl;       // SAT ((A & B) | (C & D))
    std::cout << "AB|CD|& -> " << (sat("AB|CD|&") ? "SAT" : "UNSAT") << std::endl;       // SAT ((A | B) & (C | D))
    
    std::cout << std::endl;
}

void test_edge_cases() {
    std::cout << "\033[0;33mEDGE CASES----------------------\033[0m" << std::endl;
    
    // Single variable combinations
    std::cout << "A! -> " << (sat("A!") ? "SAT" : "UNSAT") << std::endl;                 // SAT (not A, when A is false)
    std::cout << "A!! -> " << (sat("A!!") ? "SAT" : "UNSAT") << std::endl;               // SAT (not not A = A)
    std::cout << "A!!! -> " << (sat("A!!!") ? "SAT" : "UNSAT") << std::endl;             // SAT (not not not A = not A)
    
    // Complex nested formulas
    std::cout << "AB>C>D> -> " << (sat("AB>C>D>") ? "SAT" : "UNSAT") << std::endl;       // SAT (chained implications)
    std::cout << "AB=CD=& -> " << (sat("AB=CD=&") ? "SAT" : "UNSAT") << std::endl;       // SAT ((A=B) & (C=D))
    std::cout << "AB^CD^= -> " << (sat("AB^CD^=") ? "SAT" : "UNSAT") << std::endl;       // SAT ((A XOR B) = (C XOR D))
    
    std::cout << std::endl;
}

void test_known_hard_cases() {
    std::cout << "\033[0;33mKNOWN HARD CASES----------------------\033[0m" << std::endl;
    
    // These are classically difficult for naive SAT solvers but should still work
    
    // Pigeonhole principle (simplified): "If 3 pigeons go into 2 holes, at least one hole has 2 pigeons"
    // This would be UNSAT if we tried to say "each hole has at most 1 pigeon"
    // Simplified version: AB&BC&AC&A!B!C!||& (A&B & B&C & A&C & (!A | !B | !C)) - UNSAT
    std::cout << "AB&BC&AC&AB!C!|||& -> " << (sat("AB&BC&AC&AB!C!|||&") ? "SAT" : "UNSAT") << std::endl;
    
    // XOR SAT: A XOR B XOR C = true (exactly one or all three should be true)
    std::cout << "AB^C^ -> " << (sat("AB^C^") ? "SAT" : "UNSAT") << std::endl;           // SAT
    
    // Complex equivalence chains
    std::cout << "AB=BC=& -> " << (sat("AB=BC=&") ? "SAT" : "UNSAT") << std::endl;       // SAT (A=B and B=C, so A=B=C)
    
    std::cout << std::endl;
}

void demonstrate_satisfying_assignments() {
    std::cout << "\033[0;33mSATISFYING ASSIGNMENTS DEMONSTRATION----------------------\033[0m" << std::endl;
    
    std::vector<std::string> sat_formulas = {
        "AB&",      // A & B
        "AB|",      // A | B  
        "AB>",      // A > B
        "AB=",      // A = B
        "AB^"       // A XOR B
    };
    
    for (const auto& formula : sat_formulas) {
        std::cout << "Formula: " << formula;
        if (sat(formula)) {
            std::cout << " [SAT] - Finding satisfying assignment:" << std::endl;
            
            // Manually find and show one satisfying assignment
            for (int a = 0; a <= 1; a++) {
                for (int b = 0; b <= 1; b++) {
                    std::string test = formula;
                    std::replace(test.begin(), test.end(), 'A', (a ? '1' : '0'));
                    std::replace(test.begin(), test.end(), 'B', (b ? '1' : '0'));
                    
                    try {
                        if (eval_formula(test)) {
                            std::cout << "  A=" << a << ", B=" << b << " \033[0;31m\033[0;32m✓\033[0m" << std::endl;
                            break;
                        }
                    } catch (...) {
                        continue;
                    }
                }
            }
        } else {
            std::cout << " [UNSAT]" << std::endl;
        }
    }
    
    std::cout << std::endl;
}

void test_performance() {
    std::cout << "\033[0;33mPERFORMANCE TEST----------------------\033[0m" << std::endl;
    
    // Test with increasing number of variables to show exponential growth
    std::vector<std::string> performance_tests = {
        "AB&",           // 2 variables, 4 combinations
        "ABC&&",         // 3 variables, 8 combinations  
        "ABCD&&&",       // 4 variables, 16 combinations
        "ABCDE&&&&"      // 5 variables, 32 combinations
    };
    
    for (const auto& formula : performance_tests) {
        std::set<char> vars;
        for (char c : formula) {
            if (c >= 'A' && c <= 'Z') vars.insert(c);
        }
        
        std::cout << "Formula: " << formula 
                 << " (" << vars.size() << " vars, " 
                 << (1 << vars.size()) << " combinations) -> "
                 << (sat(formula) ? "SAT" : "UNSAT") << std::endl;
    }
    
    std::cout << std::endl;
}

//ex07 main
int main() {
    try {
        test_basic_satisfiability();
        test_complex_operators();
        test_unsatisfiable_formulas();
        test_multiple_variables();
        test_edge_cases();
        test_known_hard_cases();
        demonstrate_satisfying_assignments();
        test_performance();
        
        std::cout << "\033[0;32m\033[0;32mOK\033[0m ALL TESTS COMPLETED!\033[0m" << std::endl;
        
    } catch (const std::exception &e) {
        std::cout << "\033[0;32mOK (Complex Pattern)\033[0mFATAL EXCEPTION: " << e.what() << "\033[0m" << std::endl;
        return 1;
    }
    
    return 0;
}
