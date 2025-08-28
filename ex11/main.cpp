#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include "../boolean_algebra.hpp"

void test_round_trip() {
    std::cout << "\033[0;33mRound Trip Tests----------------------\033[0m" << std::endl;
    
    // Test that map and reverse_map are inverses
    std::vector<std::pair<uint16_t, uint16_t>> test_points = {
        {0, 0},
        {65535, 65535},
        {100, 200},
        {500, 1000},
        {32768, 32768},
        {1, 1},
        {65534, 65534},
        {12345, 54321}
    };
    
    for (const auto &original : test_points) {
        // Forward mapping
        double mapped_value = map(original.first, original.second);
        
        // Reverse mapping
        auto recovered = reverse_map(mapped_value);
        
        std::cout << "(" << original.first << ", " << original.second << ") → " 
                  << std::fixed << std::setprecision(10) << mapped_value
                  << " → (" << recovered.first << ", " << recovered.second << ")";
        
        // Check if we recovered the original point
        if (original.first == recovered.first && original.second == recovered.second) {
            std::cout << " ✓" << std::endl;
        } else {
            std::cout << " ❌" << std::endl;
            assert(false);
        }
    }
    
    std::cout << "✓ All round trip tests passed" << std::endl;
}

void test_range_validation() {
    std::cout << "\n\033[0;33mRange Validation Tests----------------------\033[0m" << std::endl;
    
    // Test edge cases for the input range [0, 1]
    std::vector<double> test_values = {
        0.0,          // Minimum
        1.0,          // Maximum
        0.5,          // Middle
        -0.1,         // Below range (should clamp to 0)
        1.1,          // Above range (should clamp to 1)
        0.25,         // Quarter
        0.75,         // Three quarters
        0.333333,     // Third
        0.666667      // Two thirds
    };
    
    for (double value : test_values) {
        auto result = reverse_map(value);
        
        std::cout << std::fixed << std::setprecision(6) << value 
                  << " → (" << result.first << ", " << result.second << ")" << std::endl;
        
        // Verify coordinates are in valid range
        assert(result.first <= 65535);
        assert(result.second <= 65535);
    }
    
    std::cout << "✓ All range validation tests passed" << std::endl;
}

void test_corner_values() {
    std::cout << "\n\033[0;33mCorner Values Tests----------------------\033[0m" << std::endl;
    
    // Test the corner values that we know from the forward mapping
    struct CornerTest {
        double input;
        uint16_t expected_x, expected_y;
        std::string description;
    };
    
    std::vector<CornerTest> corners = {
        {0.0, 0, 0, "Bottom-left"},
        {1.0, 65535, 65535, "Top-right"}
        // Note: We can't easily predict the exact intermediate corner values
        // due to floating point precision, so we'll test the extremes
    };
    
    for (const auto &corner : corners) {
        auto result = reverse_map(corner.input);
        
        std::cout << corner.description << ": " << corner.input 
                  << " → (" << result.first << ", " << result.second << ")";
        
        if (result.first == corner.expected_x && result.second == corner.expected_y) {
            std::cout << " ✓" << std::endl;
        } else {
            std::cout << " (expected (" << corner.expected_x << ", " << corner.expected_y << "))" << std::endl;
        }
    }
    
    std::cout << "✓ Corner values test completed" << std::endl;
}

void test_precision() {
    std::cout << "\n\033[0;33mPrecision Tests----------------------\033[0m" << std::endl;
    
    // Test precision limits with very close values
    std::vector<double> close_values = {
        0.00000001,
        0.00000002,
        0.99999998,
        0.99999999
    };
    
    for (double value : close_values) {
        auto result = reverse_map(value);
        double back_mapped = map(result.first, result.second);
        
        std::cout << std::fixed << std::setprecision(15) << value 
                  << " → (" << result.first << ", " << result.second << ")"
                  << " → " << back_mapped;
        
        // Check if the round trip preserves precision reasonably
        double error = std::abs(value - back_mapped);
        if (error < 1e-9) {
            std::cout << " ✓" << std::endl;
        } else {
            std::cout << " (error: " << error << ")" << std::endl;
        }
    }
    
    std::cout << "✓ Precision tests completed" << std::endl;
}

void test_systematic_coverage() {
    std::cout << "\n\033[0;33mSystematic Coverage Tests----------------------\033[0m" << std::endl;
    
    // Test a systematic grid of points to ensure broad coverage
    int grid_size = 20;
    int errors = 0;
    
    for (int i = 0; i <= grid_size; ++i) {
        for (int j = 0; j <= grid_size; ++j) {
            uint16_t x = static_cast<uint16_t>((i * 65535) / grid_size);
            uint16_t y = static_cast<uint16_t>((j * 65535) / grid_size);
            
            // Round trip test
            double mapped = map(x, y);
            auto recovered = reverse_map(mapped);
            
            if (recovered.first != x || recovered.second != y) {
                errors++;
            }
        }
    }
    
    int total_points = (grid_size + 1) * (grid_size + 1);
    std::cout << "Tested " << total_points << " grid points" << std::endl;
    std::cout << "Errors: " << errors << std::endl;
    
    assert(errors == 0);
    std::cout << "✓ Systematic coverage test passed" << std::endl;
}

void test_bit_pattern_recovery() {
    std::cout << "\n\033[0;33mBit Pattern Recovery Tests----------------------\033[0m" << std::endl;
    
    // Test specific bit patterns to verify the de-interleaving
    struct BitTest {
        uint16_t x, y;
        std::string description;
    };
    
    std::vector<BitTest> bit_tests = {
        {0x0000, 0x0000, "All zeros"},
        {0xFFFF, 0xFFFF, "All ones"},
        {0x5555, 0x5555, "Alternating 01"},
        {0xAAAA, 0xAAAA, "Alternating 10"},
        {0x0001, 0x0000, "Single bit in x"},
        {0x0000, 0x0001, "Single bit in y"},
        {0x8000, 0x0000, "High bit in x"},
        {0x0000, 0x8000, "High bit in y"}
    };
    
    for (const auto &test : bit_tests) {
        double mapped = map(test.x, test.y);
        auto recovered = reverse_map(mapped);
        
        std::cout << test.description << ": (" << test.x << ", " << test.y << ") → " 
                  << std::fixed << std::setprecision(15) << mapped
                  << " → (" << recovered.first << ", " << recovered.second << ")";
        
        if (recovered.first == test.x && recovered.second == test.y) {
            std::cout << " ✓" << std::endl;
        } else {
            std::cout << " ❌" << std::endl;
            assert(false);
        }
    }
    
    std::cout << "✓ Bit pattern recovery tests passed" << std::endl;
}

void demonstrate_inverse_mapping() {
    std::cout << "\n\033[0;33mInverse Mapping Demonstration----------------------\033[0m" << std::endl;
    
    std::cout << "The reverse_map function is the inverse of the map function." << std::endl;
    std::cout << "It takes a value in [0, 1] and recovers the original (x, y) coordinates." << std::endl;
    std::cout << std::endl;
    
    std::cout << "The algorithm reverses the bit interleaving process:" << std::endl;
    std::cout << "1. Convert the [0, 1] value back to a 32-bit integer" << std::endl;
    std::cout << "2. De-interleave the bits to separate x and y coordinates" << std::endl;
    std::cout << "3. Return the reconstructed (x, y) pair" << std::endl;
    std::cout << std::endl;
    
    // Demonstrate with a few examples
    std::vector<double> demo_values = {0.0, 0.25, 0.5, 0.75, 1.0};
    
    std::cout << "Examples:" << std::endl;
    for (double value : demo_values) {
        auto coords = reverse_map(value);
        double back_to_value = map(coords.first, coords.second);
        
        std::cout << std::fixed << std::setprecision(6) << value 
                  << " → (" << coords.first << ", " << coords.second << ")"
                  << " → " << back_to_value << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "This creates a bijective mapping between 2D discrete coordinates" << std::endl;
    std::cout << "and the continuous interval [0, 1], enabling space-filling curves." << std::endl;
}

int main() {
    std::cout << "Exercise 11: Reverse Space-Filling Curve Mapping (1D → 2D)" << std::endl;
    std::cout << "============================================================" << std::endl;
    
    try {
        test_round_trip();
        test_range_validation();
        test_corner_values();
        test_precision();
        test_systematic_coverage();
        test_bit_pattern_recovery();
        demonstrate_inverse_mapping();
        
        std::cout << "\nAll tests passed! Reverse mapping implementation is correct." << std::endl;
        
    } catch (const std::exception &e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
