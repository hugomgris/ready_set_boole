# Exercise 06: Conjunctive Normal Form (CNF)

## **Theoretical Foundation**

### What is Conjunctive Normal Form?

**Conjunctive Normal Form (CNF)** is a standardized representation of boolean formulas where:
1. **Structure**: A conjunction (AND) of clauses, where each clause is a disjunction (OR) of literals
2. **Literals**: Variables or their negations (A, B, !A, !B)
3. **Form**: `(A ∨ B ∨ ¬C) ∧ (¬A ∨ D) ∧ (B ∨ ¬D ∨ E)`
4. **Key property**: All ANDs are at the top level, all ORs are inside "parentheses"

### Why is CNF Important?

- **SAT Solving**: Most boolean satisfiability (SAT) solvers require CNF input
- **Logic Programming**: Prolog and similar systems use CNF-like representations
- **Circuit Design**: Direct mapping to hardware implementations using AND/OR gates
- **Proof Systems**: Resolution theorem proving works on CNF formulas
- **Database Query Optimization**: Query conditions often expressed in CNF

---

## **Mathematical Foundations**

### CNF vs Other Normal Forms

| **Form** | **Structure** | **Example** | **Use Case** |
|----------|---------------|-------------|--------------|
| **CNF** | AND of ORs | `(A ∨ B) ∧ (¬A ∨ C)` | SAT solving, theorem proving |
| **DNF** | OR of ANDs | `(A ∧ B) ∨ (¬A ∧ C)` | Database queries, logic minimization |
| **NNF** | Negations on variables only | `A ∧ (¬B ∨ C)` | Intermediate form for transformations |

### Key Transformation: Distribution Law

The core of CNF conversion is **distributing OR over AND**:

```
A ∨ (B ∧ C) ≡ (A ∨ B) ∧ (A ∨ C)
```

**Why this works**:
- For the left side to be true: either `A` is true, or both `B` and `C` are true
- For the right side to be true: both `(A ∨ B)` and `(A ∨ C)` must be true
- These conditions are logically equivalent

### Example Transformation Process

**Input**: `A ∧ (B ∨ (C ∧ D))` (RPN: `ABCD&|&`)

**Step 1**: Already in NNF, proceed to distribution
**Step 2**: Apply distribution to `B ∨ (C ∧ D)`:
```
B ∨ (C ∧ D) → (B ∨ C) ∧ (B ∨ D)
```
**Step 3**: Combine with outer AND:
```
A ∧ (B ∨ C) ∧ (B ∨ D)
```
**Result**: `ABC|BD|&&` (in RPN)

---

## **Implementation Architecture**

Our CNF converter uses a **three-phase approach**:

```
Input RPN → NNF AST → CNF AST → Output RPN
    ↓         ↓         ↓         ↓
"ABCD&|&" [NNF] [Distribute] "ABC|BD|&&"
```

### Phase 1: **Convert to NNF**
- Eliminate complex operators (`>`, `=`, `^`)
- Push negations down to variables using De Morgan's laws
- Handle double negation elimination

### Phase 2: **Distribute OR over AND**
- Apply distribution law recursively
- Handle all combinations: literal∨AND, AND∨literal, AND∨AND
- Build new tree structure with ANDs at the top

### Phase 3: **Convert back to RPN**
- Traverse the CNF tree in post-order
- Generate RPN string with proper operator precedence

---

## **Step-by-Step Execution Examples**

### **Example 1: Simple Distribution**

**Input**: `"ABC&|"` (A ∨ (B ∧ C))

#### **Step 1: Convert to NNF**
```
Already in NNF - no complex operators or nested negations
AST:
    OR
   /  \
  A   AND
      /  \
     B    C
```

#### **Step 2: Apply Distribution**
```
A ∨ (B ∧ C) → (A ∨ B) ∧ (A ∨ C)

New AST:
       AND
      /   \
    OR     OR
   / \    / \
  A   B  A   C
```

#### **Step 3: Convert to RPN**
```
Post-order traversal:
1. (A ∨ B) → "AB|"
2. (A ∨ C) → "AC|"  
3. Final AND → "AB|AC|&"

Result: "AB|AC|&"
```

### **Example 2: Complex Operator Transformation**

**Input**: `"AB="` (A ⇔ B)

#### **Step 1: Convert to NNF**
```
Eliminate EQUIV: A ⇔ B → (A ∧ B) ∨ (¬A ∧ ¬B)

AST after NNF:
       OR
      /  \
    AND   AND
   / \   /  \
  A   B A!  B!
```

#### **Step 2: Apply Distribution**
```
(A ∧ B) ∨ (¬A ∧ ¬B) → (A ∨ ¬A) ∧ (A ∨ ¬B) ∧ (B ∨ ¬A) ∧ (B ∨ ¬B)

Simplify using tautologies:
- (A ∨ ¬A) = TRUE (can be eliminated)
- (B ∨ ¬B) = TRUE (can be eliminated)

Result: (A ∨ ¬B) ∧ (¬A ∨ B)

Final AST:
        AND
       /   \
     OR     OR
    / \    / \
   A  B!  A!  B
```

#### **Step 3: Convert to RPN**
```
Result: "AB!|A!B|&"
```

### **Example 3: Subject Example**

**Input**: `"ABCD&|&"` (A ∧ (B ∨ (C ∧ D)))

#### **Step 1: Parse and NNF**
```
AST:
       AND
      /   \
     A     OR
          /  \
         B   AND
             / \
            C   D
```

#### **Step 2: Apply Distribution (Inner First)**
```
B ∨ (C ∧ D) → (B ∨ C) ∧ (B ∨ D)

Intermediate AST:
       AND
      /   \
     A    AND
          /  \
        OR    OR
       / \   / \
      B   C B   D
```

#### **Step 3: Final Structure**
```
A ∧ (B ∨ C) ∧ (B ∨ D) - already in CNF!

Final AST:
         AND
        /   \
       A    AND
           /  \
         OR    OR
        / \   / \
       B   C B   D
```

#### **Step 4: Convert to RPN**
```
Result: "ABC|BD|&&"
```

---

## **Algorithm Complexity**

### **Time Complexity**
- **Worst Case**: O(2^n) where n is the number of variables
- **Typical Case**: Much better for most real-world formulas
- **Exponential growth** occurs when distributing OR over many nested ANDs

### **Space Complexity**
- **Formula size** can grow exponentially
- **AST depth** proportional to operator nesting
- **Memory usage** dominated by intermediate tree structures

### **Example of Exponential Growth**
```
Input:  (A₁ ∨ B₁) ∧ (A₂ ∨ B₂) ∧ ... ∧ (Aₙ ∨ Bₙ)
When inverted and distributed:
Output: 2ⁿ clauses in worst case
```

---

## **Code Implementation Details**

### **Core Algorithm: Distribution Function**

```cpp
std::unique_ptr<NNFNode> distribute_or_over_and(left, right) {
    if (left != AND && right != AND) {
        // Both literals: A ∨ B → A ∨ B (no change)
        return simple_or(left, right);
    }
    
    if (left == AND && right != AND) {
        // (A ∧ B) ∨ C → (A ∨ C) ∧ (B ∨ C)
        return and_node(
            distribute(left.left, right.clone()),
            distribute(left.right, right)
        );
    }
    
    if (left != AND && right == AND) {
        // A ∨ (B ∧ C) → (A ∨ B) ∧ (A ∨ C)
        return and_node(
            distribute(left.clone(), right.left),
            distribute(left, right.right)
        );
    }
    
    if (left == AND && right == AND) {
        // (A ∧ B) ∨ (C ∧ D) → (A∨C) ∧ (A∨D) ∧ (B∨C) ∧ (B∨D)
        return four_way_distribution(left, right);
    }
}
```

### **Key Functions**

#### **1. conjunctive_normal_form()**
```cpp
// Main entry point for CNF conversion
// 1. Parse RPN to AST
// 2. Convert to NNF (eliminate complex operators)
// 3. Apply distribution to achieve CNF
// 4. Convert back to RPN
```

#### **2. distribute_or_over_and()**
```cpp
// Core distribution algorithm
// Handles all cases: literal∨AND, AND∨literal, AND∨AND
// Recursively applies distribution until CNF achieved
```

#### **3. convert_to_cnf()**
```cpp
// Orchestrates the CNF conversion process
// Recursively processes AST nodes
// Calls distribution function for OR nodes
```

#### **4. clone_node()**
```cpp
// Creates deep copies of AST subtrees
// Essential for distribution where nodes are reused
// Prevents memory corruption during tree manipulation
```
