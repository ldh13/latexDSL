#include <iostream>
#include <string>
#include <vector>
#include "lexer/lexer.h"
#include "lexer/token_names.h"


// ### LEXER TEST-CASES ###

const std::string test_str = "1 + 2 * 3";

// ### TESTING - MAIN FUNCTION ###

int main() {
	// Initialize Lexer
	Lexer lexer(test_str);
	// Tokenize
	std::vector<Token> tokens = lexer.tokenize();
	// Print token vector
	for (const Token &t : tokens) {
		std::cout << "Type: " << lexer::tokenTypeNames.at(t.type) << "\tLexeme: " << t.lexeme << '\n';
	}

	return 0;
}