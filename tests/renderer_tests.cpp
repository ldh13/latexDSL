#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "renderer/latexGenerator.h"


// ### TEST-CASES ###

const std::string test_string1 = "3 + 2 * (1 + 4) - 6 / 3";
const std::string test_string2 = "(1 + 2) * (3 + 4 * (5 - 2)) / 7";
const std::string test_string3 = "8 / 4 / 2 + 1";
const std::string test_string4 = "(2 + 3) * (4 - 1) + (6 / 3) * 5";
const std::string test_string5 = "5 + (6 / (1 + 2)) * (3 + 4 * (2 - 1)) - 7 / (2 * 3)";

static const std::vector<std::string> tests = {
	test_string1, test_string2, test_string3,
	test_string4, test_string5
};


// ### FUNCTION DEFINITIONS ###

void run_tests(const std::vector<std::string> &test_cases) {
	std::cout << "\n===== TESTING LATEX-GENERATOR =====\n\n";
	for (const std::string &test_string : test_cases) {
		// Initialize Lexer
		Lexer lexer(test_string);
		// Tokenize
		std::vector<Token> tokens = lexer.tokenize();
		// Initialize Parser
		Parser parser(tokens);
		// Instantiate AST
		std::unique_ptr<Node> root = parser.parse();
		// Instantiate LatexGenerator
		LatexGenerator latexGenerator;
		// Generate latex code
		std::string genLatex = latexGenerator.render(root.get());
		// Results
		std::cout << "Input:\t" << test_string << '\n';
		std::cout << "Output:\t" << genLatex << '\n';
	}
}

// ### TESTING LatexGenerator ###

int main() {
	run_tests(tests);
	
	return 0;
}