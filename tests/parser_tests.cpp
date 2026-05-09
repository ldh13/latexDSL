#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ast/node.h"
#include "utils/ast_utils.h"


// ### AST-PARSING TEST-CASES ###

// ## ATOMIC CORRECTNESS ##

const std::string atomic_test1 = "1";
const std::string atomic_test2 = "42";
const std::string atomic_test3 = "3.14";
const std::string atomic_test4 = "0.13";
const std::string atomic_test5 = "123 + 456";

static const std::vector<std::string> atomic_tests = {
	atomic_test1, atomic_test2, atomic_test3,
	atomic_test4, atomic_test5
};

// ## BINARY OPERATORS ##

const std::string binary_test1 = "1 + 2";
const std::string binary_test2 = "2-1";
const std::string binary_test3 = "2 *3";
const std::string binary_test4 = "6/ 2";
const std::string binary_test5 = "2^3";

static const std::vector<std::string> binary_tests = {
	binary_test1, binary_test2, binary_test3,
	binary_test4, binary_test5
};

// ## PRECEDENCE CORRECTNESS ##
const std::string precedence_test1 = "1 + 2 * 3";
const std::string precedence_test2 = "1*2 +3";
const std::string precedence_test3 = "1 + 2 * 3 + 4";
const std::string precedence_test4 = "1 *2+ 3 * 4";
const std::string precedence_test5 = "2^3*4";

static const std::vector<std::string> precedence_tests = {
	precedence_test1, precedence_test2, precedence_test3,
	precedence_test4, precedence_test5
};

// ## ASSOCIATIVITY RULES ##
const std::string associativity_test1 = "1 - 2 - 3";
const std::string associativity_test2 = "1 + 2 + 3";
const std::string associativity_test3 = "8 / 4 / 2";
const std::string associativity_test4 = "2 ^3 ^ 2";

static const std::vector<std::string> associativity_tests = {
	associativity_test1, associativity_test2, associativity_test3,
	associativity_test4
};

// ## PARENTHESIS ##
const std::string parentheses_test1 = "(1 + 2)* 3";
const std::string parentheses_test2 = "1*(2+ 3 )";
const std::string parentheses_test3 = "(1+2) *(3 + 4 )";
const std::string parentheses_test4 = "(1)";
const std::string parentheses_test5 = "((1 + 2))";

static const std::vector<std::string> parentheses_tests = {
	parentheses_test1, parentheses_test2, parentheses_test3,
	parentheses_test4, parentheses_test5
};

// ## NESTED RECURSION DEPTH ##
const std::string nested_test1 = "1 + (2 + (3 + 4))";
const std::string nested_test2 = "1 * (2 * (3 * (4 * 5)))";
const std::string nested_test3 = "(1 + (2 * (3 + (4*5))))";

static const std::vector<std::string> nested_tests = {
	nested_test1, nested_test2, nested_test3
};

// ## MIXED COMPLEXITY ##
const std::string mixed_test1 = "1 + 2 * (3 + 4)";
const std::string mixed_test2 = "(1 + 2) * (3 + 4) + 5";
const std::string mixed_test3 = "1 + (2 * 3) + (4 * 5)";
const std::string mixed_test4 = "1 * 2 + 3 * (4 + 5) + 6";

static const std::vector<std::string> mixed_tests = {
	mixed_test1, mixed_test2, mixed_test3,
	mixed_test4
};

// ## EDGE CASE STRUCTURE ##
const std::string edge_structure_test1 = "((1))";
const std::string edge_structure_test2 = "(((1 + 2)))";
const std::string edge_structure_test3 = "(1 + (2))";

static const std::vector<std::string> edge_structure_tests = {
	edge_structure_test1, edge_structure_test2, edge_structure_test3
};

// ## UNARY OPERATORS ##
const std::string unary_test1 = "-1";
const std::string unary_test2 ="+1";
const std::string unary_test3 = "-1 + 2";
const std::string unary_test4 = "-(1+2)";
const std::string unary_test5 = "-3 * 4";

static const std::vector<std::string> unary_tests = {
	unary_test1, unary_test2, unary_test3,
	unary_test4, unary_test5
};

// ## HIGH COMPLEXITY ##
const std::string high_test1 = "1 + 2 * (3 + 4) - 5";
const std::string high_test2 = "(1 + 2) * (3 + 5 * (5 + 6))";
const std::string high_test3 = "1 + (2 * (3 + (4 * 5))) - 6 / 2";
const std::string high_test4 = "2 ^3 * (4 + 5) - 6 / (1 + 2)";

static const std::vector<std::string> high_tests = {
	high_test1, high_test2, high_test3,
	high_test4
};


// ### TEST-FUNCTIONS DEFINITIONS ###

void run_tests(const std::vector<std::string> &test_cases, const std::string &output_message) {
	std::cout << output_message << "\n\n";
	std::vector<Token> tokens{};
	for (const std::string &test_str : test_cases) {
		tokens.clear();
		std::cout << "TEST INPUT: " << test_str << "\nTEST OUTPUT:\n";
		// Initialize Lexer
		Lexer lexer(test_str);
		// Tokenize
		tokens = lexer.tokenize();
		// Initialize Parser
		Parser parser(tokens);
		// Parse expression into AST
		std::unique_ptr<Node> root = parser.parse();
		// Print AST
		print_ast(root.get(), 0);
		std::cout << '\n';
	}
}


// ### GLOBAL CONSTANTS ###

const std::string atomic_message = "===== ATOMIC TESTS =====";
const std::string binary_message = "===== BINARY TESTS =====";
const std::string precedence_message = "===== PRECEDENCE TESTS =====";
const std::string associativity_message = "===== ASSOCIATIVITY TESTS =====";
const std::string parentheses_message = "===== PARENTHESES MESSAGE =====";
const std::string nested_message = "===== NESTED TESTS =====";
const std::string mixed_message = "===== MIXED COMPLEXITY TESTS =====";
const std::string edge_structure_message = "===== EDGE STRUCTURE TESTS =====";
const std::string unary_message = "===== UNARY TESTS =====";
const std::string high_message = "===== HIGH COMPLEXITY TESTS =====";

// ### TESTING - MAIN FUNCTION ###

int main() {
	run_tests(high_tests, high_message);
	
	return 0;
}