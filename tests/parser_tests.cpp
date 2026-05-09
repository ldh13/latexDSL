#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ast/node.h"
#include "utils/ast_utils.h"


// ### AST-PARSING TEST-CASES ###

const std::string test_expression = "1 + 2 * 3";

// ### TESTING - MAIN FUNCTION ###

int main() {
	// Initialize Lexer object
	Lexer lexer(test_expression);
	// Tokenize
	std::vector<Token> tokens = lexer.tokenize();
	// Initialize parser object
	Parser parser(tokens);
	// Parse expression into AST
	std::unique_ptr<Node> root = parser.parse();
	// Print AST
	print_ast(root.get(), 0);
	
	return 0;
}