/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_algebra.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:39:51 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/08/28 12:07:25 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOLEAN_ALGEBRA
# define BOOLEAN_ALGEBRA

# include <iostream>
# include <stack>
# include <set>
# include <vector>
# include <algorithm>
# include <exception>
# include <stdexcept>
# include <memory>

// ex00
int adder(int a, int b) {
	while (b != 0) {
		int sum = a ^ b;
		int carry = (a & b) << 1;
		a = sum;
		b = carry;
	}

	return (a);
}

// ex01
// helper to change int sign (O(1) - constant time)
int negate(int n) {
    int all_ones = 0;
    for (int i = 0; i < 32; ++i) {
        all_ones = (all_ones << 1) | 1;
    }
    return adder(n ^ all_ones, 1);
}

int multiplier(int a, int b) {
    if (a == 0 || b == 0) return 0;

    int result = 0;
    bool result_negative = (a < 0) ^ (b < 0);

    if (a < 0) a = negate(a);
    if (b < 0) b = negate(b);

    while (b > 0) {
        if (b & 1) {
            result = adder(result, a);
        }
        a = a << 1;
        b = b >> 1;
    }

    if (result_negative) result = negate(result);
    return result;
}

// ex02
int gray_code(int n) {
	return n ^ (n >> 1);
}

//ex03
bool process_operand(bool a, bool b, char operand) {
    if (operand == '!') {
        return !b;
    } else if (operand == '&') {
		return (a && b);
	} else if (operand == '|') {
		return (a || b);
	} else if (operand == '^') {
		return (a ^ b);
	} else if (operand == '>') {
		return (!a || b);
	} else if (operand == '=') {
		return (a == b);
	} else return (false); // will never reach this point
}

bool check_operand(const char c) {
	char operands[] = {'!', '&', '|', '^', '>', '='};

	for (const char o : operands) {
		if (c == o) { return (true); }
	}

	return (false);
}

bool eval_formula(const std::string &expression) {
    std::stack<bool> data;
    
    for (char c : expression) {
        if (c == '0' || c == '1') {
            data.push(c == '1');
        } else if (c == '!') {
            if (data.empty()) {
                throw std::invalid_argument("Error: Invalid RPN expression: not enough operands");
            }
            bool operand = data.top(); 
            data.pop();
            data.push(!operand);
        } else if (check_operand(c)) {
            if (data.size() < 2) {
                throw std::invalid_argument("Error: Invalid RPN expression: not enough operands");
            }
            bool b = data.top(); data.pop();
            bool a = data.top(); data.pop();
            bool result = process_operand(a, b, c);
            data.push(result);
        } else {
            throw std::invalid_argument("Error: Invalid RPN expression: bad operand");
        }
    }

    if (data.size() != 1) {
        throw std::invalid_argument("Error: Invalid RPN expression: bad construction");
    }
    
    return data.top();
}

// ex04
void print_truth_table(const std::string &expression) {
	std::set<char> variables;

	for (const char c : expression) {
		if (c >= 'A' && c <= 'Z') {
			variables.insert(c);
		} else if (c == '1' || c == '0') {
			throw std::invalid_argument("Error: invalid expression for truth table: only A-Z characters and valid operators admitted");
		}
	}

	std::vector<char> vars(variables.begin(), variables.end());
	int n = vars.size();

	for (char var : vars) {
		std::cout << var << " | ";
	}
		std::cout << "Result" << std::endl;

		for (int i = 0; i < (1 << n); ++i) {
		std::string sub = expression;
		std::vector<bool> values(n);
		
		for (int j = 0; j < n; ++j) {
			values[j] = (i >> (n - 1 - j)) & 1;
			char value = values[j] ? '1' : '0';
			std::replace(sub.begin(), sub.end(), vars[j], value);
		}
		
		bool result = eval_formula(sub);
		
		for (bool val : values) {
			std::cout << (val ? 1 : 0) << " | ";
		}
		std::cout << (result ? 1 : 0) << std::endl;
	}
}

// ex05
struct NNFNode {
    enum Type { VARIABLE, AND, OR, NOT, XOR, IMPLIES, EQUIV };
    Type type;
    char variable;
    std::unique_ptr<NNFNode> left;
    std::unique_ptr<NNFNode> right;
    
    NNFNode(char var) : type(VARIABLE), variable(var) {}
    NNFNode(Type op) : type(op) {}
};

std::unique_ptr<NNFNode> push_negation_down(std::unique_ptr<NNFNode> not_node);

std::unique_ptr<NNFNode> convert_to_nnf(std::unique_ptr<NNFNode> ast) {
    if (!ast) return ast;
    
    // Base case: variables are already in NNF
    if (ast->type == NNFNode::VARIABLE) {
        return ast;
    }
    
    // Handle NOT operator (the complex case)
    if (ast->type == NNFNode::NOT) {
        return push_negation_down(std::move(ast));
    }
    
    // For AND and OR: recursively convert children
    if (ast->type == NNFNode::AND || ast->type == NNFNode::OR) {
        ast->left = convert_to_nnf(std::move(ast->left));
        ast->right = convert_to_nnf(std::move(ast->right));
        return ast;
    }
    
    // Should not reach here if eliminate_complex_operators worked correctly
    throw std::invalid_argument("Unexpected operator in NNF conversion");
}

std::unique_ptr<NNFNode> push_negation_down(std::unique_ptr<NNFNode> not_node) {
    auto inner = std::move(not_node->right);
    
    if (inner->type == NNFNode::NOT) {
        // Double negation: !!A -> A
        return convert_to_nnf(std::move(inner->right));
    }
    
    if (inner->type == NNFNode::VARIABLE) {
        // Variable negation: !A -> !A (already NNF)
        not_node->right = std::move(inner);
        return not_node;
    }
    
    if (inner->type == NNFNode::AND) {
        // De Morgan: !(A & B) -> !A | !B
        auto left_neg = std::make_unique<NNFNode>(NNFNode::NOT);
        left_neg->right = std::move(inner->left);
        
        auto right_neg = std::make_unique<NNFNode>(NNFNode::NOT);
        right_neg->right = std::move(inner->right);
        
        auto or_node = std::make_unique<NNFNode>(NNFNode::OR);
        or_node->left = convert_to_nnf(std::move(left_neg));
        or_node->right = convert_to_nnf(std::move(right_neg));
        
        return or_node;
    }
    
    if (inner->type == NNFNode::OR) {
        // De Morgan: !(A | B) -> !A & !B
        auto left_neg = std::make_unique<NNFNode>(NNFNode::NOT);
        left_neg->right = std::move(inner->left);
        
        auto right_neg = std::make_unique<NNFNode>(NNFNode::NOT);
        right_neg->right = std::move(inner->right);
        
        auto and_node = std::make_unique<NNFNode>(NNFNode::AND);
        and_node->left = convert_to_nnf(std::move(left_neg));
        and_node->right = convert_to_nnf(std::move(right_neg));
        
        return and_node;
    }
    
    throw std::invalid_argument("Unexpected node type in negation");
}

std::unique_ptr<NNFNode> clone_node(const NNFNode* node) {
	if (!node) return nullptr;
	
	if (node->type == NNFNode::VARIABLE) {
		return std::make_unique<NNFNode>(node->variable);
	}
	
	auto cloned = std::make_unique<NNFNode>(node->type);
	if (node->left) cloned->left = clone_node(node->left.get());
	if (node->right) cloned->right = clone_node(node->right.get());
	
	return cloned;
}

std::unique_ptr<NNFNode> eliminate_complex_operators(std::unique_ptr<NNFNode> ast) {
	if (!ast) return ast;
	if (ast->type == NNFNode::VARIABLE) return ast;

	// Recursively transform children FIRST
	if (ast->left) {
		ast->left = eliminate_complex_operators(std::move(ast->left));
	}
	if (ast->right) {
		ast->right = eliminate_complex_operators(std::move(ast->right));
	}

	if (ast->type == NNFNode::IMPLIES) {
		// A > B becomes !A | B
		auto not_left = std::make_unique<NNFNode>(NNFNode::NOT);
		not_left->right = std::move(ast->left);
		
		auto or_node = std::make_unique<NNFNode>(NNFNode::OR);
		or_node->left = std::move(not_left);
		or_node->right = std::move(ast->right);
		
		return or_node;
	}

	if (ast->type == NNFNode::EQUIV) {
		// A = B becomes (A & B) | (!A & !B)
		auto left_clone = clone_node(ast->left.get());
		auto right_clone = clone_node(ast->right.get());
		
		auto not_left = std::make_unique<NNFNode>(NNFNode::NOT);
		not_left->right = std::move(left_clone);
		
		auto not_right = std::make_unique<NNFNode>(NNFNode::NOT);
		not_right->right = std::move(right_clone);
		
		// (A & B)
		auto case1 = std::make_unique<NNFNode>(NNFNode::AND);
		case1->left = std::move(ast->left);
		case1->right = std::move(ast->right);
		
		// (!A & !B)
		auto case2 = std::make_unique<NNFNode>(NNFNode::AND);
		case2->left = std::move(not_left);
		case2->right = std::move(not_right);
		
		// (A & B) | (!A & !B)
		auto or_node = std::make_unique<NNFNode>(NNFNode::OR);
		or_node->left = std::move(case1);
		or_node->right = std::move(case2);
		
		return or_node;
	}
	
	if (ast->type == NNFNode::XOR) {
		// A ^ B becomes (A & !B) | (!A & B)
		auto left_clone = clone_node(ast->left.get());
		auto right_clone = clone_node(ast->right.get());
		
		auto not_left = std::make_unique<NNFNode>(NNFNode::NOT);
		not_left->right = std::move(left_clone);
		
		auto not_right = std::make_unique<NNFNode>(NNFNode::NOT);
		not_right->right = std::move(right_clone);
		
		// (A & !B)
		auto case1 = std::make_unique<NNFNode>(NNFNode::AND);
		case1->left = std::move(ast->left);
		case1->right = std::move(not_right);
		
		// (!A & B)
		auto case2 = std::make_unique<NNFNode>(NNFNode::AND);
		case2->left = std::move(not_left);
		case2->right = std::move(ast->right);
		
		// (A & !B) | (!A & B)
		auto or_node = std::make_unique<NNFNode>(NNFNode::OR);
		or_node->left = std::move(case1);
		or_node->right = std::move(case2);
		
		return or_node;
	}
	
	// AND, OR, NOT are already basic
	return ast;
}

std::string ast_to_rpn(const NNFNode* node) {
    if (!node) return "";
    
    if (node->type == NNFNode::VARIABLE) {
        return std::string(1, node->variable);
    }
    
    if (node->type == NNFNode::NOT) {
        return ast_to_rpn(node->right.get()) + "!";
    }
    
    // Binary operators (AND, OR)
    std::string left_rpn = ast_to_rpn(node->left.get());
    std::string right_rpn = ast_to_rpn(node->right.get());
    
    char op;
    if (node->type == NNFNode::AND) op = '&';
    else if (node->type == NNFNode::OR) op = '|';
    else throw std::invalid_argument("Unexpected operator in RPN conversion");
    
    return left_rpn + right_rpn + op;
}

std::unique_ptr<NNFNode> parse_rpn_to_ast(const std::string &rpn) {
	std::stack<std::unique_ptr<NNFNode>> stack;

	for (char c : rpn) {
		if (c >= 'A' && c <= 'Z') {
			stack.push(std::make_unique<NNFNode>(c));
		} else if (c == '!') {
			 auto operand = std::move(stack.top()) ; stack.pop();
			 auto node = std::make_unique<NNFNode>(NNFNode::NOT);
			 node->right = std::move(operand);
			 stack.push(std::move(node));
		} else {
			auto right = std::move(stack.top()); stack.pop();
			auto left = std::move(stack.top()); stack.pop();

			NNFNode::Type op_type;
			if (c == '&') op_type = NNFNode::AND;
			else if (c == '|') op_type = NNFNode::OR;
			else if (c == '^') op_type = NNFNode::XOR;
			else if (c == '>') op_type = NNFNode::IMPLIES;
			else if (c == '=') op_type = NNFNode::EQUIV;
			else throw std::invalid_argument("Error: Unknown operator");

			auto node = std::make_unique<NNFNode>(op_type);
			node->left = std::move(left);
			node->right = std::move(right);
			stack.push(std::move(node));
		}
	}

	return (std::move(stack.top()));
}

std::string negation_normal_form(const std::string &rpn) {
	auto ast = parse_rpn_to_ast(rpn);
	ast = eliminate_complex_operators(std::move(ast));
	ast = convert_to_nnf(std::move(ast));
	return (ast_to_rpn(ast.get()));
}

// ex06
std::unique_ptr<NNFNode> distribute_or_over_and(std::unique_ptr<NNFNode> left, std::unique_ptr<NNFNode> right) {
    // Handle cases where one side is already a single literal or variable
    if (left->type != NNFNode::AND && right->type != NNFNode::AND) {
        // Both are literals, just create OR
        auto or_node = std::make_unique<NNFNode>(NNFNode::OR);
        or_node->left = std::move(left);
        or_node->right = std::move(right);
        return or_node;
    }
    
    // If left is AND: (A & B) | C becomes (A | C) & (B | C)
    if (left->type == NNFNode::AND && right->type != NNFNode::AND) {
        auto right_clone = clone_node(right.get());
        
        auto or1 = distribute_or_over_and(std::move(left->left), std::move(right));
        auto or2 = distribute_or_over_and(std::move(left->right), std::move(right_clone));
        
        auto and_node = std::make_unique<NNFNode>(NNFNode::AND);
        and_node->left = std::move(or1);
        and_node->right = std::move(or2);
        
        return and_node;
    }
    
    // If right is AND: A | (B & C) becomes (A | B) & (A | C)
    if (right->type == NNFNode::AND && left->type != NNFNode::AND) {
        auto left_clone = clone_node(left.get());
        
        auto or1 = distribute_or_over_and(std::move(left), std::move(right->left));
        auto or2 = distribute_or_over_and(std::move(left_clone), std::move(right->right));
        
        auto and_node = std::make_unique<NNFNode>(NNFNode::AND);
        and_node->left = std::move(or1);
        and_node->right = std::move(or2);
        
        return and_node;
    }
    
    // Both are AND: (A & B) | (C & D) becomes (A | C) & (A | D) & (B | C) & (B | D)
    if (left->type == NNFNode::AND && right->type == NNFNode::AND) {
        auto left_left_clone = clone_node(left->left.get());
        auto left_right_clone = clone_node(left->right.get());
        auto right_left_clone = clone_node(right->left.get());
        auto right_right_clone = clone_node(right->right.get());
        
        // (A | C)
        auto or1 = distribute_or_over_and(std::move(left->left), std::move(right->left));
        
        // (A | D)
        auto or2 = distribute_or_over_and(std::move(left_left_clone), std::move(right->right));
        
        // (B | C)
        auto or3 = distribute_or_over_and(std::move(left->right), std::move(right_left_clone));
        
        // (B | D)
        auto or4 = distribute_or_over_and(std::move(left_right_clone), std::move(right_right_clone));
        
        // Build the AND chain: ((A|C) & (A|D)) & ((B|C) & (B|D))
        auto and1 = std::make_unique<NNFNode>(NNFNode::AND);
        and1->left = std::move(or1);
        and1->right = std::move(or2);
        
        auto and2 = std::make_unique<NNFNode>(NNFNode::AND);
        and2->left = std::move(or3);
        and2->right = std::move(or4);
        
        auto final_and = std::make_unique<NNFNode>(NNFNode::AND);
        final_and->left = std::move(and1);
        final_and->right = std::move(and2);
        
        return final_and;
    }
    
    // Should not reach here
    auto or_node = std::make_unique<NNFNode>(NNFNode::OR);
    or_node->left = std::move(left);
    or_node->right = std::move(right);
    return or_node;
}

std::unique_ptr<NNFNode> convert_to_cnf(std::unique_ptr<NNFNode> ast) {
    if (!ast) return ast;
    
    // Base case: variables and negated variables are already in CNF
    if (ast->type == NNFNode::VARIABLE || 
        (ast->type == NNFNode::NOT && ast->right->type == NNFNode::VARIABLE)) {
        return ast;
    }
    
    // Recursively convert children to CNF first
    if (ast->left) {
        ast->left = convert_to_cnf(std::move(ast->left));
    }
    if (ast->right) {
        ast->right = convert_to_cnf(std::move(ast->right));
    }
    
    // Handle AND - already correct for CNF (conjunction at top level)
    if (ast->type == NNFNode::AND) {
        return ast;
    }
    
    // Handle OR - need to distribute if children contain AND
    if (ast->type == NNFNode::OR) {
        return distribute_or_over_and(std::move(ast->left), std::move(ast->right));
    }
    
    // Should not reach here if input is valid NNF
    throw std::invalid_argument("Unexpected node type in CNF conversion");
}

std::string conjunctive_normal_form(const std::string &rpn) {
    auto ast = parse_rpn_to_ast(rpn);
    ast = eliminate_complex_operators(std::move(ast));
    ast = convert_to_nnf(std::move(ast));
    
    ast = convert_to_cnf(std::move(ast));
    
    return ast_to_rpn(ast.get());
}

#endif