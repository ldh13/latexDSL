#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <iterator>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "renderer/latexGenerator.h"
#include "ast/node.h"


// ### GLOBAL CONSTANTS ###

const std::string fileName = "../tools/repl/template.html";
const std::string outFileName = "../tools/repl/preview.html";
const std::string keyword = "{{LATEX}}";
const size_t kwSize = keyword.size();


// ### MAIN FUNCTION ###

int main() {
	// Load template
	std::ifstream file(fileName);
	// istreambuf_iterator treats the input buffer as an iterator of char
	const std::string htmlTemplate{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};  // () signifies the default EOF
	size_t pos = htmlTemplate.find(keyword);
	// Safety-check
	if (pos == std::string::npos) {
		std::cerr << "Error: Did not find keyword in template\n" << std::endl;
		return 1;
	}
	
	std::cout << "\n===== LATEX-DSL REPL V.1.0 =====\n\n";
	std::cout << ">> ";
	std::string input;
	std::vector<Token> tokens;
	std::string output;
	LatexGenerator lxgenerator;
	std::string outFileContent;
	
	while (true) {
		if (!std::getline(std::cin, input)) {
			break;
		}
		if (input == "exit") {
			break;
		}
		
		// BUG: Should add validation through a try-catch
		// Initialize Lexer
		Lexer lexer(input);
		// Tokenize
		tokens = lexer.tokenize();
		// Initialize Parser
		Parser parser(tokens);
		// Initialize AST
		std::unique_ptr<Node> root = parser.parse();  // Better to declare in the while for Node destruction???
		// Generate latex output
		output = lxgenerator.render(root.get());
		// Write latex to console
		std::cout << "Latex:\t" << output << '\n';
		// Inject latex
		outFileContent = htmlTemplate;
		outFileContent.replace(pos, kwSize, output);
		// Write to preview file
		std::ofstream outFile(outFileName);
		outFile << outFileContent;
	}
}