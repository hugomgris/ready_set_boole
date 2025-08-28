# Exercise 09: Set-based Boolean Formula Evaluation

## Mathematical Foundation

### Set Algebra
Set algebra is the mathematical structure that maps boolean operations to set operations, creating an isomorphism between Boolean algebra and the algebra of sets.

**Key Mappings:**
```
Boolean Operation → Set Operation
AND (∧)          → Intersection (∩)
OR (∨)           → Union (∪)
NOT (¬)          → Complement (′)
XOR (⊕)          → Symmetric Difference (△)
IMPLIES (→)      → Set Implication
EQUALS (↔)       → Set Equivalence
```

### Set Operations Definitions

1. **Union (A ∪ B)**: All elements in either A or B
   ```
   A ∪ B = {x | x ∈ A ∨ x ∈ B}
   ```

2. **Intersection (A ∩ B)**: Elements in both A and B
   ```
   A ∩ B = {x | x ∈ A ∧ x ∈ B}
   ```

3. **Complement (A′)**: Elements not in A (relative to universe U)
   ```
   A′ = {x | x ∈ U ∧ x ∉ A}
   ```

4. **Symmetric Difference (A △ B)**: Elements in either A or B, but not both
   ```
   A △ B = (A ∪ B) - (A ∩ B) = (A - B) ∪ (B - A)
   ```

5. **Set Implication (A → B)**: Equivalent to A′ ∪ B
   ```
   A → B = A′ ∪ B = {x | x ∉ A ∨ x ∈ B}
   ```

6. **Set Equivalence (A ↔ B)**: Elements that are in both sets or in neither
   ```
   A ↔ B = (A ∩ B) ∪ (A′ ∩ B′)
   ```

## Algorithm: RPN Stack-based Evaluation

### Core Approach
Reuse the RPN (Reverse Polish Notation) evaluation strategy from ex03, but operate on sets instead of boolean values.

### Stack Operations

1. **Variable (A-Z)**: Push corresponding set onto stack
2. **Negation (!)**: Pop set, compute complement, push result
3. **Binary operators (&, |, ^, >, =)**: Pop two sets, apply operation, push result

### Universe Determination
For complement operations, the universe is determined as the union of all input sets:
```cpp
Universe = A ∪ B ∪ C ∪ ... (all sets in the input)
```

## Implementation Details

### Function Signature
```cpp
std::vector<int> eval_set(const std::string &formula, 
                         const std::vector<std::vector<int>> &sets)
```

### Operation Implementations

#### Union (|)
```cpp
std::set<int> union_set;
for (int elem : left) union_set.insert(elem);
for (int elem : right) union_set.insert(elem);
```

#### Intersection (&)
```cpp
std::vector<int> intersection;
for (int elem : left) {
    if (std::find(right.begin(), right.end(), elem) != right.end()) {
        intersection.push_back(elem);
    }
}
```

#### Complement (!)
```cpp
std::vector<int> complement;
for (int elem : universe) {
    if (std::find(set.begin(), set.end(), elem) == set.end()) {
        complement.push_back(elem);
    }
}
```

### Error Handling
- **Variable out of range**: Index beyond available sets
- **Stack underflow**: Not enough operands for operation
- **Invalid formula**: Wrong number of operands after evaluation

## Set Theory Laws Verification

### De Morgan's Laws
```
!(A ∪ B) = !A ∩ !B
!(A ∩ B) = !A ∪ !B
```

### Distributive Laws
```
A ∩ (B ∪ C) = (A ∩ B) ∪ (A ∩ C)
A ∪ (B ∩ C) = (A ∪ B) ∩ (A ∪ C)
```

### Identity Laws
```
A ∪ ∅ = A
A ∩ U = A
A ∪ A′ = U
A ∩ A′ = ∅
```

## Complexity Analysis

### Time Complexity
- **Per operation**: O(n) where n is the total number of elements
- **Formula evaluation**: O(m × n) where m is formula length
- **Universe computation**: O(k × n) where k is number of sets

### Space Complexity
- **Stack space**: O(d) where d is maximum nesting depth
- **Result storage**: O(n) for largest possible result set
- **Universe storage**: O(n) for all unique elements

## Applications

### Database Operations
Set operations map directly to SQL operations:
- Union → UNION
- Intersection → INTERSECT  
- Complement → NOT EXISTS
- Symmetric Difference → SYMMETRIC DIFFERENCE

### Logic Programming
- Variable assignments → Set membership
- Constraint satisfaction → Set operations
- Solution spaces → Set intersections

### Graph Theory
- Vertex sets → Node collections
- Edge sets → Connection collections
- Graph operations → Set operations

## Implementation Considerations

### Duplicate Handling
The implementation preserves duplicates within sets, treating them as distinct elements at their positions. For true mathematical sets, consider using `std::set<int>` instead of `std::vector<int>`.

### Ordering
Results are sorted for consistent output and easier testing. This adds O(n log n) to each operation but improves usability.

### Memory Efficiency
For large sets, consider:
- Bit vectors for dense integer ranges
- Hash sets for faster membership testing
- Lazy evaluation for complex formulas

## Testing Strategy

### Verification Points
1. **Basic operations**: Individual set operations work correctly
2. **Algebraic laws**: De Morgan's, distributivity, identity laws hold
3. **Edge cases**: Empty sets, single elements, large sets
4. **Complex formulas**: Nested operations produce correct results

### Property Testing
- **Commutativity**: A ∪ B = B ∪ A
- **Associativity**: (A ∪ B) ∪ C = A ∪ (B ∪ C)
- **Idempotence**: A ∪ A = A

## Connection to Boolean Algebra

This exercise demonstrates the **Stone representation theorem**: every Boolean algebra is isomorphic to a field of sets. The mapping is:
- Boolean variables → Sets
- Boolean operations → Set operations
- Truth values → Set membership

This connection enables:
- Converting logical problems to set problems
- Using set algorithms for boolean satisfiability
- Visualizing boolean operations geometrically

## Next Steps

The set evaluation foundation enables:
- **Constraint solving**: Express constraints as set operations
- **Optimization**: Find optimal set combinations
- **Data analysis**: Set-based queries and filtering
- **Graph algorithms**: Set-based graph representations
