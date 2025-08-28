# <h1 align="center">READY SET BOOLE</h1>

<p align="center">
   <b>A comprehensive implementation of Boolean algebra operations, from fundamental bit manipulation to advanced logical transformations and spatial algorithms. This project covers the theoretical foundations and practical implementations of Boolean logic that power modern computing.</b><br>
</p>

<p align="center">
    <img alt="C++" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
    <img alt="Math" src="https://img.shields.io/badge/Mathematics-FF6B6B?style=for-the-badge&logo=mathworks&logoColor=white" />
    <img alt="Boolean Algebra" src="https://img.shields.io/badge/Boolean%20Algebra-4ECDC4?style=for-the-badge" />
</p>
<p align="center">
    <img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/hugomgris/ready_set_boole?color=lightblue" />
    <img alt="Exercise Count" src="https://img.shields.io/badge/Exercises-11-brightgreen" />
    <img alt="Standard" src="https://img.shields.io/badge/C++-17-blue" />
</p>

## Table of Contents

1. [Project Overview](#project-overview)
2. [Mathematical Foundations](#mathematical-foundations)
3. [Exercise Breakdown](#exercise-breakdown)
4. [Implementation Architecture](#implementation-architecture)
5. [Building and Running](#building-and-running)
6. [Theoretical Deep Dive](#theoretical-deep-dive)

---

### **Core Concepts Covered**

- **Bit-Level Arithmetic**: Addition and multiplication without standard operators
- **Boolean Logic**: Expression evaluation and truth table generation
- **Formal Logic**: Negation Normal Form (NNF) and Conjunctive Normal Form (CNF)
- **Computational Complexity**: Boolean Satisfiability (SAT) solving
- **Set Theory**: Powerset generation and set operations
- **Spatial Algorithms**: Space-filling curves and coordinate mapping

### **Learning Objectives**

By completing this project, you will understand:
- How computers perform arithmetic at the hardware level
- The mathematical foundations of digital logic
- Expression parsing and evaluation algorithms
- NP-complete problem solving
- Spatial data structures and algorithms

---

## Mathematical Foundations

### **Boolean Algebra Laws**

The project implements and demonstrates these fundamental laws:

#### **Basic Operations**
```
AND (&): 1 & 1 = 1, otherwise 0
OR  (|): 0 | 0 = 0, otherwise 1  
NOT (!): !1 = 0, !0 = 1
XOR (^): a ^ b = (a & !b) | (!a & b)
```

#### **De Morgan's Laws**
```
!(A & B) = !A | !B
!(A | B) = !A & !B
```

#### **Distributive Laws**
```
A & (B | C) = (A & B) | (A & C)
A | (B & C) = (A | B) & (A | C)
```

#### **Identity and Complement Laws**
```
A | 0 = A    (OR identity)
A & 1 = A    (AND identity)
A | !A = 1   (Complement)
A & !A = 0   (Contradiction)
```

---

## Exercise Breakdown

### **Exercise 00: Binary Adder**

**Objective**: Implement addition using only bitwise operations.

**Algorithm**: Ripple-carry addition using XOR for sum bits and AND for carry bits.

```cpp
int adder(int a, int b) {
    while (b != 0) {
        int sum = a ^ b;        // Sum without carry
        int carry = (a & b) << 1; // Carry bits
        a = sum;
        b = carry;
    }
    return a;
}
```

**Key Insight**: This is exactly how CPU ALUs perform addition at the hardware level.

**Complexity**: O(log n) where n is the number of bits.

---

### **✖️ Exercise 01: Binary Multiplier**

**Objective**: Implement multiplication using only addition and bit shifting.

**Algorithm**: Binary multiplication through shift-and-add method.

```cpp
int multiplier(int a, int b) {
    int result = 0;
    bool result_negative = (a < 0) ^ (b < 0);
    
    // Work with absolute values
    if (a < 0) a = negate(a);
    if (b < 0) b = negate(b);
    
    while (b > 0) {
        if (b & 1) {
            result = adder(result, a);
        }
        a = a << 1;  // Multiply a by 2
        b = b >> 1;  // Divide b by 2
    }
    
    return result_negative ? negate(result) : result;
}
```

**Mathematical Foundation**: Based on binary representation and distributive property.

**Complexity**: O(log b) where b is the second operand.

---

### **Exercise 02: Gray Code**

**Objective**: Convert binary numbers to Gray code representation.

**Algorithm**: Single-bit transformation using XOR with right-shifted value.

```cpp
int gray_code(int n) {
    return n ^ (n >> 1);
}
```

**Properties**:
- Adjacent Gray code numbers differ by exactly one bit
- Eliminates race conditions in digital systems
- Used in rotary encoders and error correction

**Applications**: Mechanical encoders, digital communications, K-maps.

---

### **⚖️ Exercise 03: Boolean Expression Evaluation**

**Objective**: Evaluate Boolean expressions in Reverse Polish Notation (RPN).

**Supported Operations**:
```
! (NOT)  : Unary negation
& (AND)  : Logical conjunction  
| (OR)   : Logical disjunction
^ (XOR)  : Exclusive or
> (IMPL) : Material implication
= (EQUIV): Logical equivalence
```

**Algorithm**: Stack-based evaluation of postfix expressions.

```cpp
bool eval_formula(const std::string &expression) {
    std::stack<bool> data;
    
    for (char c : expression) {
        if (c == '0' || c == '1') {
            data.push(c == '1');
        } else if (c == '!') {
            bool operand = data.top(); data.pop();
            data.push(!operand);
        } else if (check_operand(c)) {
            bool b = data.top(); data.pop();
            bool a = data.top(); data.pop();
            data.push(process_operand(a, b, c));
        }
    }
    
    return data.top();
}
```

**Why RPN?**: Eliminates ambiguity, simplifies parsing, and mirrors stack-based computation.

---

### **Exercise 04: Truth Table Generation**

**Objective**: Generate complete truth tables for Boolean expressions with variables.

**Algorithm**: 
1. Extract variables from expression
2. Generate all 2^n possible assignments
3. Evaluate expression for each assignment
4. Display results in tabular format

```cpp
void print_truth_table(const std::string &expression) {
    std::set<char> variables;
    // Extract variables A-Z
    for (char c : expression) {
        if (c >= 'A' && c <= 'Z') {
            variables.insert(c);
        }
    }
    
    std::vector<char> vars(variables.begin(), variables.end());
    int n = vars.size();
    
    // Try all 2^n combinations
    for (int i = 0; i < (1 << n); ++i) {
        std::string sub = expression;
        for (int j = 0; j < n; ++j) {
            bool value = (i >> (n - 1 - j)) & 1;
            char truth_value = value ? '1' : '0';
            std::replace(sub.begin(), sub.end(), vars[j], truth_value);
        }
        bool result = eval_formula(sub);
        // Print row...
    }
}
```

**Applications**: Circuit verification, logic design, Boolean function analysis.

---

### **Exercise 05: Negation Normal Form (NNF)**

**Objective**: Transform Boolean expressions so negations only apply to variables.

**Transformations Applied**:
1. **Eliminate complex operators**:
   - `A > B` → `!A | B` (Implication)
   - `A = B` → `(A & B) | (!A & !B)` (Equivalence) 
   - `A ^ B` → `(A & !B) | (!A & B)` (XOR)

2. **Push negations down** using De Morgan's laws:
   - `!(A & B)` → `!A | !B`
   - `!(A | B)` → `!A & !B`
   - `!!A` → `A` (Double negation)

**Data Structure**: Abstract Syntax Tree (AST) with recursive transformations.

```cpp
std::unique_ptr<NNFNode> convert_to_nnf(std::unique_ptr<NNFNode> ast) {
    if (ast->type == NNFNode::NOT) {
        return push_negation_down(std::move(ast));
    }
    
    // Recursively convert children
    if (ast->left) ast->left = convert_to_nnf(std::move(ast->left));
    if (ast->right) ast->right = convert_to_nnf(std::move(ast->right));
    
    return ast;
}
```

**Benefits**: Simplifies logical reasoning, prepares for CNF conversion, enables efficient algorithms.

---

### **Exercise 06: Conjunctive Normal Form (CNF)**

**Objective**: Transform expressions into "AND of ORs" format.

**Target Structure**: `(A | B | C) & (D | E) & (F | G | H)`

**Algorithm**: Distribute OR over AND using distributive laws.

```cpp
std::unique_ptr<NNFNode> distribute_or_over_and(left, right) {
    // Case 1: (A & B) | C → (A | C) & (B | C)
    if (left->type == NNFNode::AND && right->type != NNFNode::AND) {
        auto or1 = distribute_or_over_and(left->left, clone(right));
        auto or2 = distribute_or_over_and(left->right, right);
        return create_and_node(or1, or2);
    }
    
    // Case 2: A | (B & C) → (A | B) & (A | C)
    // Case 3: (A & B) | (C & D) → (A|C) & (A|D) & (B|C) & (B|D)
    // ...
}
```

**Applications**: SAT solvers, automated theorem proving, resolution algorithms.

**Complexity**: Can cause exponential blowup in worst case.

---

### **Exercise 07: Boolean Satisfiability (SAT)**

**Objective**: Determine if a Boolean formula can be made true.

**Problem Classification**: NP-complete (Cook-Levin theorem, 1971).

**Algorithm**: Exhaustive search through all possible variable assignments.

```cpp
bool sat(const std::string &formula) {
    std::set<char> variables;
    extract_variables(formula, variables);
    
    int n = variables.size();
    
    // Try all 2^n assignments
    for (int i = 0; i < (1 << n); ++i) {
        std::string test_formula = formula;
        
        // Generate assignment i
        for (int j = 0; j < n; ++j) {
            bool value = (i >> (n - 1 - j)) & 1;
            substitute_variable(test_formula, variables[j], value);
        }
        
        // Check if this assignment satisfies the formula
        if (eval_formula(test_formula)) {
            return true;  // SATISFIABLE
        }
    }
    
    return false;  // UNSATISFIABLE
}
```

**Complexity**: O(2^n × |φ|) where n = variables, |φ| = formula size.

**Real-world SAT solvers**: Use advanced techniques like DPLL, CDCL, and learning.

---

### **Exercise 08: Powerset Generation**

**Objective**: Generate all possible subsets of a given set.

**Mathematical Foundation**: For set S with |S| = n, powerset P(S) has 2^n elements.

**Algorithm**: Bit manipulation mapping each integer to a subset.

```cpp
std::vector<std::vector<int>> powerset(const std::vector<int> &set) {
    std::vector<std::vector<int>> result;
    int n = set.size();
    
    // Generate all 2^n subsets
    for (int i = 0; i < (1 << n); ++i) {
        std::vector<int> subset;
        
        // Check each bit position
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                subset.push_back(set[j]);
            }
        }
        
        result.push_back(subset);
    }
    
    return result;
}
```

**Bit Mapping Example**:
```
Set: {1, 2, 3}
000 → {}
001 → {1}
010 → {2}  
011 → {1, 2}
100 → {3}
101 → {1, 3}
110 → {2, 3}
111 → {1, 2, 3}
```

---

### **Exercise 09: Set Evaluation**

**Objective**: Apply Boolean operations to sets instead of truth values.

**Operation Mapping**:
```
Boolean AND → Set Intersection (∩)
Boolean OR  → Set Union (∪)
Boolean NOT → Set Complement (relative to universe)
Boolean XOR → Symmetric Difference (△)
```

**Algorithm**: Stack-based evaluation with set operations.

```cpp
std::vector<int> eval_set(const std::string &formula, 
                         const std::vector<std::vector<int>> &sets) {
    std::stack<std::vector<int>> stack;
    
    for (char c : formula) {
        if (c >= 'A' && c <= 'Z') {
            stack.push(sets[c - 'A']);
        } else if (c == '&') {
            auto right = stack.top(); stack.pop();
            auto left = stack.top(); stack.pop();
            stack.push(intersection(left, right));
        } else if (c == '|') {
            auto right = stack.top(); stack.pop();
            auto left = stack.top(); stack.pop();
            stack.push(union_sets(left, right));
        }
        // Handle other operations...
    }
    
    return stack.top();
}
```

**Applications**: Database queries, search engines, data analysis.

---

### **Exercise 10: Space-Filling Curves (Z-Order)**

**Objective**: Map 2D coordinates to 1D values while preserving spatial locality.

**Algorithm**: Bit interleaving (Morton order/Z-order curve).

```cpp
double map(uint16_t x, uint16_t y) {
    uint32_t combined = 0;
    
    // Interleave bits of x and y
    for (int i = 0; i < 16; ++i) {
        uint32_t bit_x = (x >> i) & 1;
        uint32_t bit_y = (y >> i) & 1;
        
        // Place bit_x at position 2*i, bit_y at position 2*i+1
        combined |= (bit_x << (2 * i));
        combined |= (bit_y << (2 * i + 1));
    }
    
    // Normalize to [0, 1]
    return static_cast<double>(combined) / 0xFFFFFFFFUL;
}
```

**Bit Interleaving Example**:
```
x = 3 (011₂), y = 2 (010₂)
Interleaved: 010101₂
Result: 21/63 ≈ 0.333...
```

**Properties**:
- Preserves spatial locality: nearby 2D points → nearby 1D values
- Enables efficient spatial indexing
- Used in quadtrees and spatial databases

---

### **Exercise 11: Reverse Space-Filling Mapping**

**Objective**: Convert 1D values back to 2D coordinates (inverse of Exercise 10).

**Algorithm**: Bit de-interleaving to recover original coordinates.

```cpp
std::pair<uint16_t, uint16_t> reverse_map(double n) {
    // Clamp to [0, 1] and convert to integer
    uint32_t combined = static_cast<uint32_t>(n * 0xFFFFFFFFUL);
    
    uint16_t x = 0, y = 0;
    
    // De-interleave bits
    for (int i = 0; i < 16; ++i) {
        uint32_t bit_x = (combined >> (2 * i)) & 1;
        uint32_t bit_y = (combined >> (2 * i + 1)) & 1;
        
        x |= (bit_x << i);
        y |= (bit_y << i);
    }
    
    return std::make_pair(x, y);
}
```

**Round-trip Property**: `reverse_map(map(x, y)) = (x, y)` for all valid inputs.

**Applications**: Spatial database indexing, geographical information systems, computer graphics.

---

## Implementation Architecture

### **Core Design Principles**

1. **Modularity**: Each exercise is self-contained with clear interfaces
2. **Efficiency**: Optimized algorithms using bit manipulation where possible
3. **Robustness**: Comprehensive error handling and input validation
4. **Clarity**: Well-documented code with educational comments

### **Data Structures Used**

```cpp
// Expression evaluation
std::stack<bool> evaluation_stack;
std::set<char> variable_set;

// AST representation for logical transformations
struct NNFNode {
    enum Type { VARIABLE, AND, OR, NOT, XOR, IMPLIES, EQUIV };
    Type type;
    char variable;
    std::unique_ptr<NNFNode> left, right;
};

// Set operations
std::vector<std::vector<int>> powerset_result;
std::stack<std::vector<int>> set_stack;

// Spatial mapping
uint16_t coordinates[2];
uint32_t interleaved_bits;
```

### **File Organization**

```
ready_set_boole/
├── boolean_algebra.hpp          # Complete implementation
├── README.md                    # This file
├── ex00/                        # Binary adder
│   ├── main.cpp                 # Test program
│   └── Makefile                 # Build configuration
├── ex01/                        # Binary multiplier
├── ex02/                        # Gray code
├── ex03/                        # Boolean evaluation
├── ex04/                        # Truth tables
├── ex05/                        # Negation Normal Form
│   ├── main.cpp
│   ├── Makefile
│   └── NNF_explanation.md       # Detailed theory
├── ex06/                        # Conjunctive Normal Form
│   └── CNF_explanation.md       # Detailed theory
├── ex07/                        # SAT solver
│   └── SAT_explanation.md       # Detailed theory
├── ex08/                        # Powerset generation
├── ex09/                        # Set evaluation
├── ex10/                        # Space-filling curves
└── ex11/                        # Reverse mapping
```

---

## Building and Running

### **Prerequisites**

- **Compiler**: GCC 7+ or Clang 6+ with C++17 support
- **Build System**: GNU Make
- **Operating System**: Linux, macOS, or Windows with WSL

### **Building Individual Exercises**

```bash
# Navigate to any exercise directory
cd ex00

# Compile the exercise
make

# Run the test program
./ex00

# Clean build artifacts
make clean
```

### **Building All Exercises**

```bash
# Build all exercises at once
for dir in ex*/; do
    cd "$dir"
    make
    cd ..
done
```

### **Testing Examples**

```bash
# Exercise 00: Binary addition
./ex00
# Tests: adder(42, 17) = 59

# Exercise 03: Boolean evaluation  
./ex03
# Tests: eval_formula("10&") = false
#        eval_formula("10|") = true

# Exercise 07: SAT solving
./ex07
# Tests: sat("AB&") = true
#        sat("AA!&") = false
```

---

## Theoretical Deep Dive

### **Computational Complexity**

| Exercise | Algorithm | Time Complexity | Space Complexity |
|----------|-----------|----------------|------------------|
| 00 | Ripple Carry | O(log n) | O(1) |
| 01 | Shift-Add | O(log b) | O(1) |
| 02 | Gray Code | O(1) | O(1) |
| 03 | Stack Eval | O(m) | O(d) |
| 04 | Truth Table | O(2^n × m) | O(n) |
| 05 | NNF Transform | O(m) | O(d) |
| 06 | CNF Transform | O(2^m) worst | O(d) |
| 07 | SAT Brute Force | O(2^n × m) | O(n) |
| 08 | Powerset | O(n × 2^n) | O(2^n) |
| 09 | Set Eval | O(m × s) | O(s) |
| 10 | Z-Order Map | O(log w) | O(1) |
| 11 | Reverse Map | O(log w) | O(1) |

*Where: n = variables, m = formula size, d = AST depth, s = set size, w = coordinate width*

### **Boolean Function Classes**

The project covers functions from different complexity classes:

1. **P**: Polynomial-time solvable (Exercises 00-06, 08-11)
2. **NP-Complete**: SAT problem (Exercise 07)
3. **PSPACE**: Formula evaluation with quantifiers (extension)

### **Logical Equivalences Demonstrated**

```
Material Implication: A → B ≡ ¬A ∨ B
Logical Equivalence:  A ↔ B ≡ (A ∧ B) ∨ (¬A ∧ ¬B)
Exclusive Or:         A ⊕ B ≡ (A ∧ ¬B) ∨ (¬A ∧ B)
De Morgan's Laws:     ¬(A ∧ B) ≡ ¬A ∨ ¬B
Distributivity:       A ∨ (B ∧ C) ≡ (A ∨ B) ∧ (A ∨ C)
```
---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
