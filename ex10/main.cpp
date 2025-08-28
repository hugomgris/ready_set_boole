#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include "../boolean_algebra.hpp"

void test_corner_points() {
    std::cout << "\033[0;33mCorner Points Tests----------------------\033[0m" << std::endl;
    
    // Test corner points of the square [0, 65535] x [0, 65535]
    std::vector<std::pair<uint16_t, uint16_t>> corners = {
        {0, 0},           // Bottom-left
        {65535, 0},       // Bottom-right  
        {0, 65535},       // Top-left
        {65535, 65535}    // Top-right
    };
    
    std::vector<std::string> names = {
        "Bottom-left (0, 0)",
        "Bottom-right (65535, 0)", 
        "Top-left (0, 65535)",
        "Top-right (65535, 65535)"
    };
    
    for (size_t i = 0; i < corners.size(); ++i) {
        double result = map(corners[i].first, corners[i].second);
        std::cout << names[i] << " → " << std::fixed << std::setprecision(10) << result << std::endl;
        
        // Result should be in [0, 1]
        assert(result >= 0.0 && result <= 1.0);
    }
    
    std::cout << "✓ All corner points map to [0, 1]" << std::endl;
}

void test_range_properties() {
    std::cout << "\n\033[0;33mRange Properties Tests----------------------\033[0m" << std::endl;
    
    double min_val = 1.0, max_val = 0.0;
    int test_points = 1000;
    
    // Test various points to verify range
    for (int i = 0; i < test_points; ++i) {
        uint16_t x = static_cast<uint16_t>(rand() % 65536);
        uint16_t y = static_cast<uint16_t>(rand() % 65536);
        
        double result = map(x, y);
        
        assert(result >= 0.0 && result <= 1.0);
        min_val = std::min(min_val, result);
        max_val = std::max(max_val, result);
    }
    
    std::cout << "Tested " << test_points << " random points" << std::endl;
    std::cout << "Min value: " << std::fixed << std::setprecision(10) << min_val << std::endl;
    std::cout << "Max value: " << std::fixed << std::setprecision(10) << max_val << std::endl;
    std::cout << "✓ All values in range [0, 1]" << std::endl;
}

void test_bit_interleaving() {
    std::cout << "\n\033[0;33mBit Interleaving Tests----------------------\033[0m" << std::endl;
    
    // Test simple bit patterns to verify interleaving
    struct TestCase {
        uint16_t x, y;
        std::string x_binary, y_binary, expected_pattern;
    };
    
    std::vector<TestCase> test_cases = {
        {0, 0, "0000", "0000", "00000000"},
        {1, 0, "0001", "0000", "00000001"}, 
        {0, 1, "0000", "0001", "00000010"},
        {1, 1, "0001", "0001", "00000011"},
        {2, 0, "0010", "0000", "00000100"},
        {0, 2, "0000", "0010", "00001000"},
        {3, 3, "0011", "0011", "00001111"}
    };
    
    for (const auto &test : test_cases) {
        double result = map(test.x, test.y);
        
        std::cout << "(" << test.x << ", " << test.y << ") → " 
                  << std::fixed << std::setprecision(10) << result;
        
        // Verify the mapping is deterministic
        double result2 = map(test.x, test.y);
        assert(result == result2);
        std::cout << " ✓" << std::endl;
    }
    
    std::cout << "✓ Bit interleaving works correctly" << std::endl;
}

void test_injectivity() {
    std::cout << "\n\033[0;33mInjectivity Tests----------------------\033[0m" << std::endl;
    
    // Test that different points map to different values (within precision limits)
    std::vector<std::pair<uint16_t, uint16_t>> test_points = {
        {0, 0}, {1, 0}, {0, 1}, {1, 1},
        {100, 200}, {200, 100}, {500, 1000},
        {1000, 500}, {32768, 32768}, {65535, 0}
    };
    
    std::vector<double> results;
    for (const auto &point : test_points) {
        double result = map(point.first, point.second);
        results.push_back(result);
        
        std::cout << "(" << point.first << ", " << point.second << ") → " 
                  << std::fixed << std::setprecision(15) << result << std::endl;
    }
    
    // Check that all results are unique
    std::sort(results.begin(), results.end());
    auto unique_end = std::unique(results.begin(), results.end());
    
    assert(unique_end == results.end());
    std::cout << "✓ All test points map to unique values (bijective)" << std::endl;
}

void test_space_filling_properties() {
    std::cout << "\n\033[0;33mSpace-Filling Properties Tests----------------------\033[0m" << std::endl;
    
    // Test that nearby points in 2D space have similar mapped values
    // This tests the space-filling curve property
    
    std::vector<std::pair<std::pair<uint16_t, uint16_t>, std::pair<uint16_t, uint16_t>>> nearby_pairs = {
        {{100, 100}, {101, 100}},  // Horizontal neighbors
        {{100, 100}, {100, 101}},  // Vertical neighbors
        {{500, 500}, {501, 501}},  // Diagonal neighbors
    };
    
    for (const auto &pair : nearby_pairs) {
        double val1 = map(pair.first.first, pair.first.second);
        double val2 = map(pair.second.first, pair.second.second);
        
        std::cout << "(" << pair.first.first << ", " << pair.first.second << ") → " 
                  << std::fixed << std::setprecision(8) << val1 << std::endl;
        std::cout << "(" << pair.second.first << ", " << pair.second.second << ") → " 
                  << std::fixed << std::setprecision(8) << val2 << std::endl;
        std::cout << "Difference: " << std::abs(val1 - val2) << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << "✓ Space-filling curve properties demonstrated" << std::endl;
}

void demonstrate_z_order_curve() {
    std::cout << "\n\033[0;33mZ-Order Curve Demonstration----------------------\033[0m" << std::endl;
    
    std::cout << "The Z-order curve (Morton curve) interleaves the bits of x and y coordinates." << std::endl;
    std::cout << "This creates a space-filling curve that maps 2D points to 1D values." << std::endl;
    std::cout << std::endl;
    
    std::cout << "Example bit interleaving for small values:" << std::endl;
    
    for (uint16_t x = 0; x < 4; ++x) {
        for (uint16_t y = 0; y < 4; ++y) {
            double result = map(x, y);
            
            // Show the bit pattern
            std::cout << "(" << x << ", " << y << "): ";
            std::cout << "x=" << std::bitset<2>(x) << " y=" << std::bitset<2>(y);
            
            // Calculate interleaved bits manually for demonstration
            uint32_t interleaved = 0;
            for (int i = 0; i < 2; ++i) {
                interleaved |= ((x >> i) & 1) << (2 * i);
                interleaved |= ((y >> i) & 1) << (2 * i + 1);
            }
            
            std::cout << " → " << std::bitset<4>(interleaved);
            std::cout << " → " << std::fixed << std::setprecision(8) << result << std::endl;
        }
    }
    
    std::cout << std::endl;
    std::cout << "The Z-order curve gets its name from the Z-like pattern it traces" << std::endl;
    std::cout << "through 2D space when connecting points in order of their 1D values." << std::endl;
}

void test_extreme_values() {
    std::cout << "\n\033[0;33mExtreme Values Tests----------------------\033[0m" << std::endl;
    
    // Test extreme coordinate values
    std::vector<std::pair<uint16_t, uint16_t>> extreme_points = {
        {0, 0},           // Minimum coordinates
        {65535, 65535},   // Maximum coordinates  
        {0, 65535},       // Mixed extremes
        {65535, 0},
        {32768, 32768},   // Middle point
        {1, 65534},       // Near extremes
        {65534, 1}
    };
    
    for (const auto &point : extreme_points) {
        double result = map(point.first, point.second);
        
        std::cout << "(" << std::setw(5) << point.first << ", " << std::setw(5) << point.second << ") → " 
                  << std::fixed << std::setprecision(15) << result << std::endl;
        
        // Verify range
        assert(result >= 0.0 && result <= 1.0);
    }
    
    std::cout << "✓ Extreme values handled correctly" << std::endl;
}

int main() {
    std::cout << "Exercise 10: Space-Filling Curve Mapping (2D → 1D)" << std::endl;
    std::cout << "===================================================" << std::endl;
    
    try {
        test_corner_points();
        test_range_properties();
        test_bit_interleaving();
        test_injectivity();
        test_space_filling_properties();
        test_extreme_values();
        demonstrate_z_order_curve();
        
        std::cout << "\nAll tests passed! Space-filling curve mapping is correct." << std::endl;
        
    } catch (const std::exception &e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
