# Exercise 11: Reverse Space-Filling Curve Mapping (1D → 2D)

## Mathematical Foundation

### Inverse Mapping
The **reverse mapping** is the inverse function of the space-filling curve mapping from Exercise 10. It takes a value from the continuous interval [0,1] and recovers the original 2D coordinates.

**Mathematical Definition:**
```
reverse_map: [0,1] → [0,65535] × [0,65535]
reverse_map(map(x,y)) = (x,y) for all valid (x,y)
```

### Bijective Property
For discrete coordinates, this mapping is **bijective** (one-to-one and onto):
- **Injective**: Different 1D values map to different 2D points
- **Surjective**: Every valid 2D point can be reached
- **Perfect inverse**: Complete round-trip fidelity

## Algorithm: Bit De-interleaving

### Core Concept
The reverse mapping **de-interleaves** the bits that were interleaved in the forward mapping.

Given an interleaved bit pattern:
```
z = y₁₅x₁₅y₁₄x₁₄y₁₃x₁₃...y₁x₁y₀x₀
```

We extract the original coordinates:
```
x = x₁₅x₁₄x₁₃...x₁x₀  (bits at even positions)
y = y₁₅y₁₄y₁₃...y₁y₀  (bits at odd positions)
```

### Implementation Steps

1. **Denormalize**: Convert [0,1] value back to 32-bit integer
2. **Initialize coordinates**: Start with x = 0, y = 0
3. **Extract bits**: For each position i from 0 to 15:
   - Get bit at position 2i (for x coordinate)
   - Get bit at position 2i+1 (for y coordinate)
4. **Reconstruct**: Place extracted bits in correct positions
5. **Return**: The recovered (x, y) coordinate pair

### Example Walkthrough

For input value corresponding to interleaved bits `001101₂`:
```
Original pattern: y₂x₂y₁x₁y₀x₀ = 001101
Position 0: x₀ = 1, y₀ = 0
Position 1: x₁ = 1, y₁ = 1  
Position 2: x₂ = 0, y₂ = 0

Result: x = 011₂ = 3, y = 010₂ = 2
```

**Step-by-step bit extraction:**
```
Input: 001101₂
Bit positions: 5,4,3,2,1,0
Extract even positions (x): bits 4,2,0 → 0,1,1 → x = 011₂ = 3
Extract odd positions (y):  bits 5,3,1 → 0,1,0 → y = 010₂ = 2
```

## Code Analysis

### Function Signature
```cpp
std::pair<uint16_t, uint16_t> reverse_map(double n)
```

### Key Operations

1. **Range clamping**: Ensure input is in [0, 1]
2. **Integer conversion**: `n * 0xFFFFFFFFUL` recovers 32-bit value
3. **Bit extraction**: `(combined >> (2*i)) & 1` gets individual bits
4. **Coordinate reconstruction**: `x |= (bit_x << i)` builds coordinates
5. **Pair creation**: Return reconstructed (x, y) coordinates

### Error Handling
- **Clamping**: Input values outside [0,1] are clamped to valid range
- **Precision**: Limited by double-precision floating point
- **Boundary cases**: 0.0 → (0,0), 1.0 → (65535,65535)

## Round-Trip Fidelity

### Perfect Recovery
For the discrete coordinate domain, the mapping achieves **perfect round-trip fidelity**:
```cpp
assert(reverse_map(map(x, y)) == make_pair(x, y));
```

### Floating-Point Considerations
- **Precision limits**: IEEE 754 double precision
- **Rounding errors**: May occur at extreme precision limits  
- **Practical accuracy**: Perfect for 16-bit coordinate ranges

## Applications

### Spatial Data Retrieval
Reverse mapping enables **efficient spatial queries**:
- Convert 1D range queries back to 2D regions
- Reconstruct original coordinates from indexed values
- Support spatial database operations

### Image Processing
- **Pixel addressing**: Convert linear indices to (x,y) coordinates
- **Memory layout**: Transform between different memory organizations
- **Texture mapping**: Convert 1D texture coordinates to 2D positions

### Computational Geometry
- **Point location**: Find 2D coordinates from spatial hash values
- **Nearest neighbor**: Convert proximity in 1D back to 2D distance
- **Range queries**: Map 1D intervals to 2D rectangular regions

## Performance Analysis

### Time Complexity
- **Bit operations**: O(log n) for n-bit coordinates
- **Constant factors**: Very fast for fixed 16-bit coordinates
- **No memory allocation**: Direct computation in registers

### Space Complexity
- **Memory usage**: O(1) constant space
- **No auxiliary storage**: Direct bit manipulation
- **Cache efficient**: Sequential bit processing

## Precision Analysis

### Theoretical Precision
- **Input precision**: IEEE 754 double (53-bit mantissa)
- **Coordinate precision**: 16 bits per coordinate (32 bits total)
- **Sufficient precision**: Double can exactly represent all 32-bit integers

### Practical Accuracy
- **Round-trip guarantee**: Perfect for intended coordinate range
- **Edge cases**: Properly handled with clamping
- **Numerical stability**: No accumulation of floating-point errors

## Implementation Considerations

### Input Validation
```cpp
if (n < 0.0) n = 0.0;  // Clamp below range
if (n > 1.0) n = 1.0;  // Clamp above range
```

### Bit Manipulation Safety
- **Type safety**: Explicit casts for bit operations
- **Overflow protection**: 16-bit coordinates never overflow
- **Endianness**: Implementation-independent bit operations

### Optimization Opportunities

#### Hardware Acceleration
- **BMI2 instructions**: PEXT instruction for parallel bit extraction
- **SIMD operations**: Vectorize multiple reverse mappings
- **GPU compute**: Massively parallel coordinate reconstruction

#### Lookup Tables
For performance-critical applications:
- **Cache bit patterns**: Pre-compute common de-interleaving operations
- **Memory vs. computation**: Trade-off for specific use cases
- **Branch reduction**: Eliminate conditional operations

## Testing Strategy

### Verification Methods

1. **Round-trip testing**: Verify `reverse_map(map(x,y)) = (x,y)`
2. **Range validation**: Ensure outputs are in valid coordinate range
3. **Bit pattern verification**: Test specific bit patterns
4. **Boundary testing**: Verify corner cases and extremes
5. **Systematic coverage**: Test grid of coordinate space

### Property-Based Testing
- **Bijection property**: One-to-one mapping verification
- **Range preservation**: Output coordinates within bounds
- **Precision consistency**: Floating-point accuracy verification

## Error Analysis

### Sources of Error
1. **Floating-point precision**: Limited by IEEE 754 standard
2. **Rounding errors**: Minimal for 32-bit integer range
3. **Implementation bugs**: Bit manipulation errors

### Error Mitigation
- **Clamping**: Handle out-of-range inputs gracefully
- **Precision testing**: Verify accuracy at boundaries
- **Systematic validation**: Comprehensive test coverage

## Mathematical Properties

### Inverse Function Theorem
The reverse mapping satisfies the mathematical properties of an inverse function:
- **Left inverse**: `reverse_map(map(x)) = x`
- **Right inverse**: `map(reverse_map(y)) = y`
- **Bijective**: One-to-one correspondence

### Measure Preservation
The inverse mapping preserves spatial measures:
- **Area preservation**: Equal 1D intervals → equal 2D areas
- **Distribution preservation**: Uniform 1D → uniform 2D
- **Geometric consistency**: Spatial relationships maintained

## Connection to Information Theory

### Entropy Preservation
The bijective mapping preserves information content:
- **No information loss**: Perfect reconstruction possible
- **Maximum entropy**: Uniform distribution preservation
- **Compression properties**: Lossless coordinate transformation

### Coding Theory
The bit interleaving/de-interleaving relates to coding theory:
- **Error correction**: Bit patterns can detect some errors
- **Channel capacity**: Maximum information transfer
- **Redundancy**: No redundant information in the mapping

## Advanced Applications

### Database Systems
- **Spatial indexing**: R-trees, quadtrees with Z-order
- **Query optimization**: Convert between query types
- **Data distribution**: Balanced partitioning schemes

### Computer Graphics
- **Texture synthesis**: Procedural texture generation
- **Mesh processing**: Vertex ordering and processing
- **Level-of-detail**: Multi-resolution coordinate mapping

### Scientific Computing
- **Domain decomposition**: Parallel processing coordination
- **Adaptive refinement**: Multi-scale coordinate systems
- **Visualization**: Data mapping between dimensions

## Future Extensions

### Higher Dimensions
The technique extends to higher dimensions:
- **3D coordinates**: Interleave x, y, z bits
- **4D space-time**: Include temporal dimension
- **N-dimensional**: Generalize to arbitrary dimensions

### Alternative Curves
Other space-filling curves can be inverted:
- **Hilbert curve**: Better locality preservation
- **Peano curve**: Ternary-based mapping
- **Custom curves**: Application-specific designs

## Conclusion

The reverse mapping completes the bijective transformation between 2D discrete coordinates and the 1D continuous interval [0,1]. This enables powerful spatial algorithms that can work efficiently in both domains, choosing the most appropriate representation for each operation.

The combination of forward and reverse mappings provides a foundation for sophisticated spatial data structures and algorithms that bridge the gap between discrete computational coordinates and continuous mathematical spaces.
