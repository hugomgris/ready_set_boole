# Exercise 08: Powerset

## Mathematical Foundation

### What is a Powerset?
The **powerset** P(S) of a set S is the set of all possible subsets of S, including the empty set ∅ and S itself.

**Formal Definition:**
```
P(S) = {X | X ⊆ S}
```

### Key Properties

1. **Cardinality**: If |S| = n, then |P(S)| = 2^n
2. **Always contains**: ∅ and S
3. **Subset relation**: Every element of P(S) is a subset of S

### Examples

```
S = {}           → P(S) = { {} }
S = {1}          → P(S) = { {}, {1} }
S = {1, 2}       → P(S) = { {}, {1}, {2}, {1,2} }
S = {1, 2, 3}    → P(S) = { {}, {1}, {2}, {3}, {1,2}, {1,3}, {2,3}, {1,2,3} }
```

## Algorithm: Bit Manipulation Approach

### Core Insight
Each subset can be represented by a binary number where:
- Bit i = 1: include element i in the subset
- Bit i = 0: exclude element i from the subset

For n elements, we need all numbers from 0 to 2^n - 1.

### Implementation Steps

1. **Generate all binary patterns**: from 0 to 2^n - 1
2. **For each pattern**: check each bit position
3. **If bit is set**: include corresponding element in subset
4. **Add subset**: to the result

### Example Walkthrough
For set {1, 2, 3}:

```
Pattern 000 (0) → {}        (no bits set)
Pattern 001 (1) → {1}       (bit 0 set)
Pattern 010 (2) → {2}       (bit 1 set)
Pattern 011 (3) → {1, 2}    (bits 0,1 set)
Pattern 100 (4) → {3}       (bit 2 set)
Pattern 101 (5) → {1, 3}    (bits 0,2 set)
Pattern 110 (6) → {2, 3}    (bits 1,2 set)
Pattern 111 (7) → {1, 2, 3} (all bits set)
```

## Code Analysis

### Function Signature
```cpp
std::vector<std::vector<int>> powerset(const std::vector<int> &set)
```

### Key Operations

1. **Bit counting**: `(1 << n)` generates 2^n
2. **Bit testing**: `i & (1 << j)` checks if bit j is set in i
3. **Element inclusion**: Add set[j] if bit j is set

### Time Complexity
- **Time**: O(n × 2^n) - for each of 2^n subsets, check n bits
- **Space**: O(2^n) - storing all subsets

## Set Theory Connections

### Relation to Boolean Algebra
The powerset operation connects directly to boolean functions:
- Each subset ↔ Boolean function on the original set
- Element inclusion ↔ Variable assignment (true/false)
- Powerset ↔ Truth table of all possible assignments

### Applications

1. **Combinatorics**: All possible selections
2. **Graph theory**: All possible subgraphs
3. **Logic**: All possible truth assignments
4. **Optimization**: All possible solutions to explore

## Implementation Considerations

### Memory Usage
For large sets, powerset grows exponentially:
- 10 elements: 1,024 subsets
- 20 elements: 1,048,576 subsets
- 30 elements: 1,073,741,824 subsets

### Optimization Opportunities
1. **Iterator pattern**: Generate subsets on demand
2. **Gray code**: Generate subsets in minimal-change order
3. **Lexicographic order**: Sort subsets systematically

## Testing Strategy

### Verification Points
1. **Cardinality**: Check |P(S)| = 2^|S|
2. **Completeness**: Contains ∅ and S
3. **Validity**: All elements in subsets are from original set
4. **Uniqueness**: No duplicate subsets (unless input has duplicates)

### Edge Cases
- Empty set
- Single element
- Duplicate elements in input
- Negative numbers
- Large numbers

## Mathematical Properties

### Lattice Structure
The powerset with ⊆ (subset relation) forms a **Boolean lattice**:
- **Meet (∧)**: Intersection (∩)
- **Join (∨)**: Union (∪)
- **Complement**: Set complement
- **Bottom**: ∅
- **Top**: S

### Boolean Algebra Connection
This lattice is isomorphic to the Boolean algebra B^n where n = |S|.

## Next Steps

This powerset implementation will be used in:
- **ex09**: Evaluating set-based boolean formulas
- **Advanced algorithms**: Where all combinations must be considered
- **Optimization problems**: Exhaustive search spaces
