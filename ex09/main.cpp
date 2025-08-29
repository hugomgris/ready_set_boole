#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "../boolean_algebra.hpp"

void print_set(const std::vector<int> &set) {
    std::cout << "{ ";
    for (size_t i = 0; i < set.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << set[i];
    }
    std::cout << " }";
}

void print_sets(const std::vector<std::vector<int>> &sets) {
    std::cout << "[ ";
    for (size_t i = 0; i < sets.size(); ++i) {
        if (i > 0) std::cout << ", ";
        print_set(sets[i]);
    }
    std::cout << " ]";
}

bool sets_equal(const std::vector<int> &a, const std::vector<int> &b) {
    if (a.size() != b.size()) return false;
    
    std::vector<int> sorted_a = a, sorted_b = b;
    std::sort(sorted_a.begin(), sorted_a.end());
    std::sort(sorted_b.begin(), sorted_b.end());
    
    return sorted_a == sorted_b;
}

void test_basic_operations() {
    std::cout << "\033[0;33mBasic Set Operations Tests----------------------\033[0m" << std::endl;
    
    // Test data: A = {1, 2}, B = {2, 3}
    std::vector<std::vector<int>> sets = {{1, 2}, {2, 3}};
    
    std::cout << "Sets: ";
    print_sets(sets);
    std::cout << std::endl;
    
    // Test union (disjunction)
    auto result = eval_set("AB|", sets);
    std::cout << "A | B = ";
    print_set(result);
    std::cout << std::endl;
    
    std::vector<int> expected_union = {1, 2, 3};
    assert(sets_equal(result, expected_union));
    std::cout << "\033[0;32m✓ Union test passed\033[0m" << std::endl;
    
    // Test intersection (conjunction)
    result = eval_set("AB&", sets);
    std::cout << "A & B = ";
    print_set(result);
    std::cout << std::endl;
    
    std::vector<int> expected_intersection = {2};
    assert(sets_equal(result, expected_intersection));
    std::cout << "\033[0;32m✓ Intersection test passed\033[0m" << std::endl;
    
    // Test symmetric difference (XOR)
    result = eval_set("AB^", sets);
    std::cout << "A ^ B = ";
    print_set(result);
    std::cout << std::endl;
    
    std::vector<int> expected_xor = {1, 3};
    assert(sets_equal(result, expected_xor));
    std::cout << "\033[0;32m✓ Symmetric difference test passed\033[0m" << std::endl;
}

void test_complement_operations() {
    std::cout << "\n\033[0;33mComplement Operations Tests----------------------\033[0m" << std::endl;
    
    // Test data: A = {1, 2}, universe = {1, 2, 3, 4}
    std::vector<std::vector<int>> sets = {{1, 2}, {3, 4}};
    
    std::cout << "Sets: ";
    print_sets(sets);
    std::cout << " (universe = {1, 2, 3, 4})" << std::endl;
    
    // Test complement
    auto result = eval_set("A!", sets);
    std::cout << "!A = ";
    print_set(result);
    std::cout << std::endl;
    
    std::vector<int> expected_complement = {3, 4};
    assert(sets_equal(result, expected_complement));
    std::cout << "\033[0;32m✓ Complement test passed\033[0m" << std::endl;
    
    // Test double complement (should return original)
    result = eval_set("A!!", sets);
    std::cout << "!!A = ";
    print_set(result);
    std::cout << std::endl;
    
    std::vector<int> expected_double_complement = {1, 2};
    assert(sets_equal(result, expected_double_complement));
    std::cout << "\033[0;32m✓ Double complement test passed\033[0m" << std::endl;
}

void test_implication_operations() {
    std::cout << "\n\033[0;33mImplication Operations Tests----------------------\033[0m" << std::endl;
    
    // Test data: A = {1}, B = {2, 3}, universe = {1, 2, 3}
    std::vector<std::vector<int>> sets = {{1}, {2, 3}, {1, 2, 3}};
    
    std::cout << "Sets: A = {1}, B = {2, 3}, universe = {1, 2, 3}" << std::endl;
    
    // Test implication A > B (equivalent to !A | B)
    auto result = eval_set("AB>", sets);
    std::cout << "A > B = ";
    print_set(result);
    std::cout << std::endl;
    
    // A > B = !A | B = {2, 3} | {2, 3} = {2, 3}
    std::vector<int> expected_implication = {2, 3};
    assert(sets_equal(result, expected_implication));
    std::cout << "\033[0;32m✓ Implication test passed\033[0m" << std::endl;
    
    // Test equivalence A = B (equivalent to (A & B) | (!A & !B))
    result = eval_set("AB=", sets);
    std::cout << "A = B = ";
    print_set(result);
    std::cout << std::endl;
    
    // A = B: (A & B) | (!A & !B) = {} | {} = {}
    std::vector<int> expected_equivalence = {};
    assert(sets_equal(result, expected_equivalence));
    std::cout << "\033[0;32m✓ Equivalence test passed\033[0m" << std::endl;
}

void test_complex_formulas() {
    std::cout << "\n\033[0;33mComplex Formula Tests----------------------\033[0m" << std::endl;
    
    // Test data: A = {1}, B = {2}, C = {1, 2}
    std::vector<std::vector<int>> sets = {{1}, {2}, {1, 2}};
    
    std::cout << "Sets: A = {1}, B = {2}, C = {1, 2}" << std::endl;
    
    // Test De Morgan's law: !(A | B) = !A & !B
    auto left_side = eval_set("AB|!", sets);
    auto right_side = eval_set("A!B!&", sets);
    
    std::cout << "!(A | B) = ";
    print_set(left_side);
    std::cout << std::endl;
    
    std::cout << "!A & !B = ";
    print_set(right_side);
    std::cout << std::endl;
    
    assert(sets_equal(left_side, right_side));
    std::cout << "\033[0;32m✓ De Morgan's law verified\033[0m" << std::endl;
    
    // Test distributivity: A & (B | C) = (A & B) | (A & C)
    auto left_dist = eval_set("ABC|&", sets);
    auto right_dist = eval_set("AB&AC&|", sets);
    
    std::cout << "A & (B | C) = ";
    print_set(left_dist);
    std::cout << std::endl;
    
    std::cout << "(A & B) | (A & C) = ";
    print_set(right_dist);
    std::cout << std::endl;
    
    assert(sets_equal(left_dist, right_dist));
    std::cout << "\033[0;32m✓ Distributivity verified\033[0m" << std::endl;
}

void test_edge_cases() {
    std::cout << "\n\033[0;33mEdge Cases Tests----------------------\033[0m" << std::endl;
    
    // Test with empty sets
    std::vector<std::vector<int>> empty_sets = {{}, {1, 2}};
    
    auto result = eval_set("AB|", empty_sets);
    std::cout << "Empty ∪ {1, 2} = ";
    print_set(result);
    std::cout << std::endl;
    
    std::vector<int> expected = {1, 2};
    assert(sets_equal(result, expected));
    std::cout << "\033[0;32m✓ Empty set union test passed\033[0m" << std::endl;
    
    result = eval_set("AB&", empty_sets);
    std::cout << "Empty ∩ {1, 2} = ";
    print_set(result);
    std::cout << std::endl;
    
    std::vector<int> expected_empty = {};
    assert(sets_equal(result, expected_empty));
    std::cout << "\033[0;32m✓ Empty set intersection test passed\033[0m" << std::endl;
    
    // Test single element operations
    std::vector<std::vector<int>> single_sets = {{1}};
    
    result = eval_set("A", single_sets);
    std::cout << "Single set A = ";
    print_set(result);
    std::cout << std::endl;
    
    std::vector<int> expected_single = {1};
    assert(sets_equal(result, expected_single));
    std::cout << "\033[0;32m✓ Single set test passed\033[0m" << std::endl;
}

void demonstrate_set_algebra() {
    std::cout << "\n\033[0;33mSet Algebra Demonstration----------------------\033[0m" << std::endl;
    
    std::cout << "Set algebra maps boolean operations to set operations:" << std::endl;
    std::cout << "• AND (∧) → Intersection (∩)" << std::endl;
    std::cout << "• OR (∨) → Union (∪)" << std::endl;
    std::cout << "• NOT (¬) → Complement (′)" << std::endl;
    std::cout << "• XOR (⊕) → Symmetric Difference (△)" << std::endl;
    std::cout << "• IMPLIES (→) → Set Implication" << std::endl;
    std::cout << "• EQUALS (↔) → Set Equivalence" << std::endl;
    
    std::vector<std::vector<int>> demo_sets = {{1, 2}, {2, 3}, {1, 3}};
    
    std::cout << "\nExample with A = {1, 2}, B = {2, 3}, C = {1, 3}:" << std::endl;
    
    std::vector<std::string> formulas = {"AB&", "AB|", "AB^", "A!", "AB>", "AB="};
    std::vector<std::string> descriptions = {
        "A ∩ B (intersection)",
        "A ∪ B (union)", 
        "A △ B (symmetric difference)",
        "A′ (complement)",
        "A → B (implication)",
        "A ↔ B (equivalence)"
    };
    
    for (size_t i = 0; i < formulas.size(); ++i) {
        auto result = eval_set(formulas[i], demo_sets);
        std::cout << descriptions[i] << " = ";
        print_set(result);
        std::cout << std::endl;
    }
}

int main() {
    try {
        test_basic_operations();
        test_complement_operations();
        test_implication_operations();
        test_complex_formulas();
        test_edge_cases();
        demonstrate_set_algebra();
        
        std::cout << "\n\033[0;32mAll tests passed! Set evaluation implementation is correct.\033[0m" << std::endl;
        
    } catch (const std::exception &e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
