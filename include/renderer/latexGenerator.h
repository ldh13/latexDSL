#pragma once

#include <string>
#include <memory>
#include "ast/node.h"
#include "lexer/token_symbols.h"

// ### STRUCT DEFINITIONS ###
struct BoolPair {
	bool first;
	bool second;
};

// ### CLASS DEFINITIONS ###

// ## LatexRenderer CLASS ##
class LatexGenerator {
	private:
		
		// # Helper Functions #
		bool match(Node *node, NodeType type) {
			return node->type == type;
		}
		BoolPair needsParenthesis(const Node *node) {
			return {
				node->leftChild()->lexeme == "+" || node->leftChild()->lexeme == "-",
				node->rightChild()->lexeme == "+" || node->rightChild()->lexeme == "-"
			};
		}
		
		// # Helper Latex generation Functions #
		std::string renderExpression(const Node *node) {
			std::string result;
			switch (node->type) {
				case NodeType::NUMBER:
					result = node->lexeme;
					break;
				case NodeType::IDENTIFIER:
					result = node->lexeme;
					break;
				case NodeType::BINARYOP:
					result = renderBinaryOp(node);
					break;
				default:
				// BUG: This needs proper handling
					result = "Error";
					break;
			}
			return result;
		}
		
		std::string renderBinaryOp(const Node *node) {
			std::string lexeme = node->lexeme;
			std::string result;
			if (lexeme == tokens::PLUS) {
				result =  renderExpression(node->leftChild()) + " + " + renderExpression(node->rightChild());
			} else if (lexeme == tokens::MINUS) {
				result = renderExpression(node->leftChild()) + " - " + renderExpression(node->rightChild());
			} else if (lexeme == tokens::MULT || lexeme == tokens::DIV) {
				BoolPair parenthesis = needsParenthesis(node);
				
				if (lexeme == tokens::MULT) {
					result += parenthesis.first ? R"(\left()" : "";
					result += renderExpression(node->leftChild());
					result += parenthesis.first ? R"(\right) \cdot )" : R"( \cdot )";
					result += parenthesis.second ? R"(\left()" : "";
					result += renderExpression(node->rightChild());
					result += parenthesis.second ? R"(\right))" : "";
				} else {
					result += parenthesis.first ? R"(\frac{\left()" : R"(\frac{)";
					result += renderExpression(node->leftChild());
					result += parenthesis.first ? R"(\right)}{)" : "}{"; 
					result += parenthesis.second ? R"(\left()" : "";
					result += renderExpression(node->rightChild());
					result += parenthesis.second ? R"(\right)})" : "}";
				}
			}
			return result;
		}
	
	public:
		std::string render(const Node *root) {
			return renderExpression(root);
		}
};