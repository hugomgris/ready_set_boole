# Exercise 05: Negation Normal Form (NNF)

## 📚 **Theoretical Foundation**

### What is Negation Normal Form?

**Negation Normal Form (NNF)** is a standardized representation of boolean formulas where:
1. **Negation operators (`!`) only appear directly before variables** - never before complex expressions
2. **Only three operators are allowed**: `!` (NOT), `&` (AND), `|` (OR)
3. **All other operators** (`^`, `>`, `=`) must be eliminated and converted to basic forms

### Why is NNF Important?

- **Simplified reasoning**: Easier to analyze and manipulate boolean expressions
- **Algorithm efficiency**: Many boolean algorithms work faster on NNF formulas
- **Canonical form**: Provides a standard representation for logical equivalence
- **Circuit design**: Maps directly to digital logic gate implementations

---

## 🔄 **Mathematical Transformations**

### 1. **De Morgan's Laws**
The core transformations for pushing negations down:

```
¬(A ∧ B) ≡ ¬A ∨ ¬B    (NOT distributes over AND → becomes OR)
¬(A ∨ B) ≡ ¬A ∧ ¬B    (NOT distributes over OR → becomes AND)
```

**Example**:
- Input: `¬(A ∧ B)` 
- Apply De Morgan's: `¬A ∨ ¬B`
- Result: Negations now only on variables ✅

### 2. **Double Negation Elimination**
```
¬¬A ≡ A    (Double negative cancels out)
```

### 3. **Complex Operator Elimination**

**Material Condition (Implication)**:
```
A ⇒ B ≡ ¬A ∨ B
```

**Logical Equivalence**:
```
A ⇔ B ≡ (A ∧ B) ∨ (¬A ∧ ¬B)
```

**Exclusive OR (XOR)**:
```
A ⊕ B ≡ (A ∧ ¬B) ∨ (¬A ∧ B)
```

---

## 🏗️ **Implementation Architecture**

Our NNF converter uses a **three-phase approach**:

```
Input RPN → AST → NNF AST → Output RPN
    ↓         ↓        ↓         ↓
  "AB&!"  [Parse]  [Transform] "A!B!|"
```

### Phase 1: **RPN to AST Parsing**
Convert Reverse Polish Notation to Abstract Syntax Tree for easier manipulation.

### Phase 2: **AST Transformation**
Apply boolean algebra rules to convert to NNF.

### Phase 3: **AST to RPN Conversion**
Convert the transformed tree back to RPN format.

---

## 🚀 **Step-by-Step Execution**

### **Example 1: Simple De Morgan's Law**

**Input**: `"AB&!"` (¬(A ∧ B))

#### **Step 1: Parse RPN to AST**
```
Input: "AB&!"

Parsing process:
1. 'A' → push variable A
2. 'B' → push variable B  
3. '&' → pop B,A → create AND(A,B) → push
4. '!' → pop AND(A,B) → create NOT(AND(A,B)) → push

Result AST:
    NOT
     |
    AND
   /   \
  A     B
```

#### **Step 2: Eliminate Complex Operators**
No complex operators (`>`, `=`, `^`) present, so AST remains unchanged.

#### **Step 3: Convert to NNF**
```
Process NOT node:
- Inner node is AND
- Apply De Morgan's: ¬(A ∧ B) → ¬A ∨ ¬B

Transformation:
1. Create NOT(A)
2. Create NOT(B)  
3. Create OR(NOT(A), NOT(B))

Result AST:
     OR
    /  \
  NOT  NOT
   |    |
   A    B
```

#### **Step 4: Convert AST to RPN**
```
Traverse AST in post-order:
1. Visit NOT(A) → "A!"
2. Visit NOT(B) → "B!"
3. Visit OR → "A!B!|"

Final result: "A!B!|"
```

### **Example 2: Material Condition**

**Input**: `"AB>"` (A ⇒ B)

#### **Step 1: Parse RPN to AST**
```
Result AST:
  IMPLIES
   /    \
  A      B
```

#### **Step 2: Eliminate Complex Operators**
```
Transform IMPLIES:
A ⇒ B becomes ¬A ∨ B

New AST:
    OR
   /  \
 NOT   B
  |
  A
```

#### **Step 3: Convert to NNF**
Already in NNF form (negation only on variable A).

#### **Step 4: Convert to RPN**
```
Result: "A!B|"
```

### **Example 3: Complex Equivalence**

**Input**: `"AB="` (A ⇔ B)

#### **Step 1: Parse RPN to AST**
```
Result AST:
  EQUIV
   /   \
  A     B
```

#### **Step 2: Eliminate Complex Operators**
```
Transform EQUIV:
A ⇔ B becomes (A ∧ B) ∨ (¬A ∧ ¬B)

New AST:
       OR
      /  \
    AND   AND
   /  \   /  \
  A    B NOT NOT
           |   |
           A   B
```

#### **Step 3: Convert to NNF**
Already in NNF form.

#### **Step 4: Convert to RPN**
```
Result: "AB&A!B!&|"
```

---

## 💻 **Code Implementation Details**

### **Core Data Structure: NNFNode**
```cpp
struct NNFNode {
    enum Type { VARIABLE, AND, OR, NOT, XOR, IMPLIES, EQUIV };
    Type type;
    char variable;  // For VARIABLE nodes
    std::unique_ptr<NNFNode> left;
    std::unique_ptr<NNFNode> right;
};
```

### **Key Functions**

#### **1. parse_rpn_to_ast()**
```cpp
// Converts RPN string to AST using stack-based parsing
// Handles all operators: &, |, ^, >, =, !
// Uses std::move for efficient memory management
```

#### **2. eliminate_complex_operators()**
```cpp
// Recursively transforms complex operators to basic ones:
// - IMPLIES → OR with NOT
// - EQUIV → OR of two AND expressions  
// - XOR → OR of two AND expressions
// Uses clone_node() for safe tree duplication
```

#### **3. convert_to_nnf()**
```cpp
// Main NNF transformation engine
// Calls push_negation_down() for NOT nodes
// Recursively processes children
```

#### **4. push_negation_down()**
```cpp
// Core De Morgan's law implementation:
// - NOT(AND) → OR of NOTs
// - NOT(OR) → AND of NOTs  
// - NOT(NOT) → original (double negation elimination)
// - NOT(VARIABLE) → unchanged (already NNF)
```

#### **5. ast_to_rpn()**
```cpp
// Post-order traversal to rebuild RPN
// Only outputs allowed operators: !, &, |
```

