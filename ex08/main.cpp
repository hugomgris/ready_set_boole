/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:42:31 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/28 14:45:30 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ex08 main

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <bitset>
#include "../boolean_algebra.hpp"

void print_powerset(const std::vector<std::vector<int>> &powerset) {
    std::cout << "{ ";
    for (size_t i = 0; i < powerset.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << "{ ";
        for (size_t j = 0; j < powerset[i].size(); ++j) {
            if (j > 0) std::cout << ", ";
            std::cout << powerset[i][j];
        }
        std::cout << " }";
    }
    std::cout << " }" << std::endl;
}

void test_powerset_basic() {
    std::cout << "\033[0;33mBasic Powerset Tests----------\033[0m\033[0m" << std::endl;
    
    // Test empty set
    std::vector<int> empty = {};
    auto result = powerset(empty);
    std::cout << "Powerset of {} = ";
    print_powerset(result);
    assert(result.size() == 1 && result[0].empty());
    std::cout << "✓ Empty set test passed" << std::endl;
    
    // Test single element
    std::vector<int> single = {1};
    result = powerset(single);
    std::cout << "Powerset of {1} = ";
    print_powerset(result);
    assert(result.size() == 2);
    std::cout << "✓ Single element test passed" << std::endl;
    
    // Test two elements
    std::vector<int> two = {1, 2};
    result = powerset(two);
    std::cout << "Powerset of {1, 2} = ";
    print_powerset(result);
    assert(result.size() == 4);
    std::cout << "✓ Two elements test passed" << std::endl;
}

void test_powerset_properties() {
    std::cout << "\n\033[0;33mPowerset Properties Tests----------\033[0m" << std::endl;
    
    // Test that powerset size is 2^n
    for (int n = 0; n <= 5; ++n) {
        std::vector<int> set;
        for (int i = 0; i < n; ++i) {
            set.push_back(i);
        }
        
        auto result = powerset(set);
        size_t expected_size = 1 << n;  // 2^n
        
        std::cout << "Set of size " << n << " has powerset of size " << result.size() 
                  << " (expected " << expected_size << ")" << std::endl;
        assert(result.size() == expected_size);
    }
    std::cout << "✓ Cardinality property verified" << std::endl;
}

void test_powerset_contains_all_subsets() {
    std::cout << "\n\033[0;33mSubset Containment Tests----------\033[0m" << std::endl;
    
    std::vector<int> set = {1, 2, 3};
    auto result = powerset(set);
    
    // Check that powerset contains empty set
    bool has_empty = false;
    for (const auto &subset : result) {
        if (subset.empty()) {
            has_empty = true;
            break;
        }
    }
    assert(has_empty);
    std::cout << "✓ Contains empty set" << std::endl;
    
    // Check that powerset contains the original set
    bool has_original = false;
    for (const auto &subset : result) {
        if (subset.size() == set.size()) {
            bool matches = true;
            for (size_t i = 0; i < set.size(); ++i) {
                if (std::find(subset.begin(), subset.end(), set[i]) == subset.end()) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                has_original = true;
                break;
            }
        }
    }
    assert(has_original);
    std::cout << "✓ Contains original set" << std::endl;
    
    // Check that all elements in subsets are from original set
    for (const auto &subset : result) {
        for (int element : subset) {
            assert(std::find(set.begin(), set.end(), element) != set.end());
        }
    }
    std::cout << "✓ All subset elements are from original set" << std::endl;
}

void test_powerset_duplicates() {
    std::cout << "\n\033[0;33mDuplicate Handling Tests----------\033[0m" << std::endl;
    
    // Test with duplicate elements in input
    std::vector<int> with_dups = {1, 1, 2};
    auto result = powerset(with_dups);
    
    std::cout << "Powerset of {1, 1, 2} = ";
    print_powerset(result);
    
    // Should still generate 2^3 = 8 subsets
    assert(result.size() == 8);
    std::cout << "✓ Handles duplicates by treating them as distinct positions" << std::endl;
}

void test_powerset_edge_cases() {
    std::cout << "\n\033[0;33mEdge Cases Tests----------\033[0m" << std::endl;
    
    // Test with negative numbers
    std::vector<int> negative = {-1, 0, 1};
    auto result = powerset(negative);
    std::cout << "Powerset of {-1, 0, 1} = ";
    print_powerset(result);
    assert(result.size() == 8);
    std::cout << "✓ Handles negative numbers" << std::endl;
    
    // Test with large numbers
    std::vector<int> large = {100, 200};
    result = powerset(large);
    std::cout << "Powerset of {100, 200} = ";
    print_powerset(result);
    assert(result.size() == 4);
    std::cout << "✓ Handles large numbers" << std::endl;
}

void demonstrate_powerset_concept() {
    std::cout << "\n\033[0;33mPowerset Concept Demonstration----------\033[0m" << std::endl;
    
    std::cout << "The powerset P(S) of a set S is the set of all subsets of S." << std::endl;
    std::cout << "For a set with n elements, the powerset has 2^n elements." << std::endl;
    std::cout << "This is because each element can either be included or excluded from a subset." << std::endl;
    
    std::vector<int> demo = {1, 2, 3};
    auto result = powerset(demo);
    
    std::cout << "\nFor set {1, 2, 3}:" << std::endl;
    std::cout << "Each subset corresponds to a binary pattern:" << std::endl;
    
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "Pattern " << std::bitset<3>(i) << " → { ";
        for (size_t j = 0; j < result[i].size(); ++j) {
            if (j > 0) std::cout << ", ";
            std::cout << result[i][j];
        }
        std::cout << " }" << std::endl;
    }
}

int main() {
    try {
        test_powerset_basic();
        test_powerset_properties();
        test_powerset_contains_all_subsets();
        test_powerset_duplicates();
        test_powerset_edge_cases();
        demonstrate_powerset_concept();
        
        std::cout << "\n\033[0;32mAll tests passed! Powerset implementation is correct.\033[0m" << std::endl;
        
    } catch (const std::exception &e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
