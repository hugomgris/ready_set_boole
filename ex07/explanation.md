# Exercise 07: Boolean Satisfiability (SAT)

## **Theoretical Foundation**

### What is Boolean Satisfiability (SAT)?

**Boolean Satisfiability (SAT)** is the problem of determining whether there exists an assignment of truth values to variables that makes a boolean formula evaluate to true.

**Formal Definition**:
- **Input**: A boolean formula φ over variables x₁, x₂, ..., xₙ
- **Output**: TRUE if there exists an assignment that makes φ = TRUE, FALSE otherwise
- **Terminology**: 
  - **Satisfiable (SAT)**: At least one satisfying assignment exists
  - **Unsatisfiable (UNSAT)**: No satisfying assignment exists

### Why is SAT Important?

**SAT is the first NP-complete problem** and serves as the foundation for computational complexity theory:

- **Theoretical Importance**: Cook-Levin theorem (1971) proved SAT is NP-complete
- **Practical Applications**: Circuit design, software verification, AI planning, cryptography
- **SAT Solvers**: Modern algorithms can solve instances with millions of variables
- **Reduction Base**: Many problems reduce to SAT for practical solving

---

## **Mathematical Foundations**

### **Basic Concepts**

#### **Satisfying Assignment**
An assignment σ: {x₁, x₂, ..., xₙ} → {0, 1} such that φ(σ) = 1

**Example**:
- Formula: `A ∧ (B ∨ C)`
- Satisfying assignment: A=1, B=1, C=0
- Verification: 1 ∧ (1 ∨ 0) = 1 ∧ 1 = 1 ✓

#### **Tautology vs Contradiction vs Contingency**
- **Tautology**: Always true (e.g., `A ∨ ¬A`)
- **Contradiction**: Always false (e.g., `A ∧ ¬A`)  
- **Contingency**: Sometimes true, sometimes false (e.g., `A ∧ B`)

### **SAT vs Related Problems**

| **Problem** | **Question** | **Complexity** |
|-------------|--------------|----------------|
| **SAT** | Is φ satisfiable? | NP-complete |
| **TAUTOLOGY** | Is φ always true? | coNP-complete |
| **MODEL COUNTING** | How many satisfying assignments? | #P-complete |
| **EQUIV** | Are φ₁ and φ₂ equivalent? | coNP-complete |

---

## **Algorithm Approaches**

### **1. Brute Force (Truth Table)**
**Our Implementation**: Try all 2ⁿ possible assignments

```
Algorithm: Exhaustive_SAT(φ)
1. Extract variables V = {v₁, v₂, ..., vₙ}
2. For each assignment σ ∈ {0,1}ⁿ:
   3. If φ(σ) = 1: return SAT
4. Return UNSAT
```

**Complexity**: O(2ⁿ × |φ|) where n = number of variables

### **2. Modern SAT Solvers (Advanced)**
- **DPLL Algorithm**: Davis-Putnam-Logemann-Loveland
- **CDCL**: Conflict-Driven Clause Learning
- **Unit Propagation**: Simplify using unit clauses
- **Boolean Constraint Propagation**: Maintain consistency

---

## **Step-by-Step Execution Examples**

### **Example 1: Simple Satisfiable Formula**

**Input**: `"AB&"` (A ∧ B)

#### **Step 1: Extract Variables**
```
Variables: {A, B}
Number of combinations: 2² = 4
```

#### **Step 2: Try All Assignments**
```
Assignment 1: A=0, B=0 → "01&" → 0 ∧ 0 = 0 ❌
Assignment 2: A=0, B=1 → "01&" → 0 ∧ 1 = 0 ❌  
Assignment 3: A=1, B=0 → "10&" → 1 ∧ 0 = 0 ❌
Assignment 4: A=1, B=1 → "11&" → 1 ∧ 1 = 1 ✅
```

#### **Result**: **SAT** (satisfying assignment: A=1, B=1)

### **Example 2: Unsatisfiable Formula**

**Input**: `"AA!&"` (A ∧ ¬A)

#### **Step 1: Extract Variables**
```
Variables: {A}
Number of combinations: 2¹ = 2
```

#### **Step 2: Try All Assignments**
```
Assignment 1: A=0 → "00!&" → "01&" → 0 ∧ 1 = 0 ❌
Assignment 2: A=1 → "11!&" → "10&" → 1 ∧ 0 = 0 ❌
```

#### **Result**: **UNSAT** (contradiction - no satisfying assignment)

### **Example 3: Complex Formula**

**Input**: `"AB>"` (A ⇒ B)

#### **Step 1: Extract Variables**
```
Variables: {A, B}  
Number of combinations: 2² = 4
```

#### **Step 2: Try All Assignments**
```
Assignment 1: A=0, B=0 → "00>" → ¬0 ∨ 0 = 1 ∨ 0 = 1 ✅
Assignment 2: A=0, B=1 → "01>" → ¬0 ∨ 1 = 1 ∨ 1 = 1 ✅
Assignment 3: A=1, B=0 → "10>" → ¬1 ∨ 0 = 0 ∨ 0 = 0 ❌
Assignment 4: A=1, B=1 → "11>" → ¬1 ∨ 1 = 0 ∨ 1 = 1 ✅
```

#### **Result**: **SAT** (multiple satisfying assignments)

---

## **Implementation Architecture**

Our SAT solver uses a **brute force approach** with the following phases:

```
Input RPN → Variable Extraction → Assignment Generation → Evaluation
     ↓              ↓                      ↓                ↓
  "AB&"         {A, B}           {00, 01, 10, 11}      [0,0,0,1]
```

### **Phase 1: Variable Extraction**
```cpp
std::set<char> variables;
for (char c : formula) {
    if (c >= 'A' && c <= 'Z') {
        variables.insert(c);
    }
}
```

### **Phase 2: Assignment Generation**
```cpp
for (int i = 0; i < (1 << n); ++i) {
    // Generate i-th assignment
    for (int j = 0; j < n; ++j) {
        bool value = (i >> (n - 1 - j)) & 1;
        // Assign value to variable j
    }
}
```

### **Phase 3: Formula Evaluation**
```cpp
std::string test_formula = formula;
// Substitute variables with truth values
std::replace(test_formula.begin(), test_formula.end(), 'A', '1');
bool result = eval_formula(test_formula);
```

---

## **Complexity Analysis**

### **Time Complexity**
- **Variable extraction**: O(|φ|) where |φ| is formula length
- **Assignment enumeration**: O(2ⁿ) where n is number of variables
- **Formula evaluation per assignment**: O(|φ|)
- **Total**: O(2ⁿ × |φ|)

### **Space Complexity**
- **Variable storage**: O(n)
- **Formula copy per evaluation**: O(|φ|)
- **Evaluation stack**: O(depth of φ)
- **Total**: O(n + |φ|)

### **Exponential Growth Example**
| Variables | Assignments | Time (rough) |
|-----------|-------------|--------------|
| 10        | 1,024       | ~1ms         |
| 20        | 1,048,576   | ~1s          |
| 30        | 1,073,741,824 | ~17min     |

---

## **Code Implementation Details**

### **Core SAT Function**

```cpp
bool sat(const std::string &formula) {
    // 1. Extract variables
    std::set<char> variables;
    for (char c : formula) {
        if (c >= 'A' && c <= 'Z') {
            variables.insert(c);
        }
    }
    
    // 2. Try all 2^n assignments
    std::vector<char> vars(variables.begin(), variables.end());
    int n = vars.size();
    
    for (int i = 0; i < (1 << n); ++i) {
        // 3. Generate assignment i
        std::string test_formula = formula;
        for (int j = 0; j < n; ++j) {
            bool value = (i >> (n - 1 - j)) & 1;
            char truth_value = value ? '1' : '0';
            std::replace(test_formula.begin(), test_formula.end(), 
                        vars[j], truth_value);
        }
        
        // 4. Evaluate formula
        if (eval_formula(test_formula)) {
            return true;  // Found satisfying assignment
        }
    }
    
    return false;  // No satisfying assignment found
}
```

### **Key Implementation Details**

#### **1. Variable Extraction**
- Use `std::set<char>` for automatic sorting and deduplication
- Only extract uppercase letters A-Z as variables
- Convert to `std::vector<char>` for indexed access

#### **2. Assignment Enumeration**
- Use bit manipulation: `i >> (n-1-j) & 1` 
- Maps integer i to binary assignment for variables
- MSB corresponds to first variable (lexicographic order)

#### **3. Formula Substitution**
- Copy original formula for each assignment
- Use `std::replace` to substitute variables with '0'/'1'
- Reuse existing `eval_formula` function

#### **4. Early Termination**
- Return `true` immediately when satisfying assignment found
- Only return `false` after exhausting all possibilities

---

## **Practical Applications**

### **1. Circuit Verification**
```cpp
// Check if circuit implementation matches specification
bool circuit_correct = !sat("spec_formula ^ impl_formula");
```

### **2. Software Bounded Model Checking**
```cpp
// Check if program can reach error state
bool program_safe = !sat("path_condition & error_condition");
```

### **3. Cryptographic Analysis**
```cpp
// Try to find key that produces known plaintext/ciphertext pair
bool key_found = sat("encryption_formula & known_io_constraints");
```

### **4. AI Planning**
```cpp
// Find action sequence that reaches goal
bool plan_exists = sat("initial_state & actions & goal_state");
```

---

## **Optimization Opportunities**

### **1. Early Pruning**
- **Unit Propagation**: If formula contains single literal, set it true
- **Pure Literal Elimination**: Variables appearing with one polarity

### **2. Smart Variable Ordering**
- **Most Constrained First**: Variables appearing in most clauses
- **Activity-Based**: Variables involved in recent conflicts

### **3. Clause Learning**
- **CDCL**: Learn from conflicts to avoid revisiting similar states
- **Backjumping**: Skip irrelevant decision levels

### **4. Preprocessing**
- **Subsumption**: Remove redundant clauses
- **Resolution**: Eliminate variables through resolution

### **Future Improvements**
The current brute force implementation could be enhanced with:
- DPLL algorithm with unit propagation
- Non-chronological backtracking
- Conflict-driven clause learning
- Random restarts

However, for the scope of this exercise, the exhaustive approach correctly solves the SAT problem for small to medium-sized formulas.
