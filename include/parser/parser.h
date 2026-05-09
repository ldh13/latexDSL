#pragma once

#include <string>
#include <sstream>
#include <utility>
#include "lexer/lexer.h"
#include "ast/node.h"
#include "errors/ParseError.h"
#include "lexer/token_names.h"


// ### CLASS DEFINITIONS ###

// ## PARSER CLASS ##
class Parser {
    private:
        std::vector<Token> tokens;
        size_t nTokens;
        size_t currentIndex;

        // # Const Helper functions (Do not change attributes of the Parser object) #
        const Token& peek() const {
            return tokens[currentIndex];
        }
        bool match(TokenType type) const {
            if (peek().type == type) {
                return true;
            }

            return false;
        }
		// # Non-Const Helper Functions #
		void advance() {
			++currentIndex;
        }
		// TODO: IMPLEMENT A MAP BETWEEN TYPE AND TYPENAME FOR CLARITY
        void expect(TokenType type) {
            if (!match(type)) {
				std::stringstream message;
				message << "Expected token of type: " << lexer::tokenTypeNames.at(type) << ", but received token of type " << lexer::tokenTypeNames.at(peek().type);
				throw ParseError(message.str());
			}
			advance();
        }

		// # Private parsing functions #
        std::unique_ptr<Node> parsePrimary() {
			// We have received a primary token: NUMBER | IDENTIFIER | "(" EXPRESSION ")"
			const Token &currentNode = peek();
			std::unique_ptr<Node> nodePtr;  // Consider this as an uninitialized "box" that will then contain and control ownership
			switch (currentNode.type) {
				// TODO: THIS IS SCREAMING FOR A GENERATE ABSTRACTION
				case TokenType::NUMBER:
					nodePtr = std::make_unique<Node>();
					nodePtr->type = NodeType::NUMBER;
					nodePtr->lexeme = currentNode.lexeme;
					advance();
					break;
				case TokenType::IDENTIFIER:
					nodePtr = std::make_unique<Node>();
					nodePtr->type = NodeType::IDENTIFIER;
					nodePtr->lexeme = currentNode.lexeme;
					advance();
					break;
				case TokenType::LPAREN:
					advance();
					nodePtr = parseExpr();
					expect(TokenType::RPAREN);
					break;
				default:
					std::stringstream message;
					message << "Expected PRIMARY TOKEN but received TOKEN of TYPE: " << lexer::tokenTypeNames.at(currentNode.type);
					throw ParseError(message.str());
			}
			
			return nodePtr;  // OWNERSHIP IS NOW PASSED TO THE CALLER (NO COPY)
        }
		
		std::unique_ptr<Node> parseUnary() {
			const Token &currentNode = peek();
			std::unique_ptr<Node> nodePtr;
			
			if (match(TokenType::PLUS) || match(TokenType::MINUS)) {
				nodePtr = std::make_unique<Node>();
				nodePtr->type = NodeType::UNARYOP;
				nodePtr->lexeme = currentNode.lexeme;
				advance();
				nodePtr->right = parseUnary();
			} else if (match(TokenType::NUMBER) || match(TokenType::IDENTIFIER) || match(TokenType::LPAREN)) {
				nodePtr = parsePrimary();
			} else {
				std::stringstream message;
				message << "Expected UNARY TOKEN but received TOKEN of TYPE: " << lexer::tokenTypeNames.at(currentNode.type);
				throw ParseError(message.str());
			}
			
			return nodePtr;
		}
		
		std::unique_ptr<Node> parseFactor() {
			std::unique_ptr<Node> nodePtr = parseUnary();
			const Token &currentNode = peek();
			
			if (match(TokenType::EXPONENT)) {
				std::unique_ptr<Node> expNodePtr = std::make_unique<Node>();
				expNodePtr->type = NodeType::BINARYOP;
				expNodePtr->lexeme = currentNode.lexeme;
				expNodePtr->left = std::move(nodePtr);  // nodePtr is an lvalue and ownership must be moved explicitly
				advance();
				expNodePtr->right = parseFactor();  // The return of parseFactor() is an rvalue and will be implicitly moved
				
				return expNodePtr;
			}
			
			return nodePtr;
		}
		
		std::unique_ptr<Node> parseTerm() {
			std::unique_ptr<Node> nodePtr = parseFactor();
			
			while (match(TokenType::MULTIPLY) || match(TokenType::DIVIDE)) {
				std::unique_ptr<Node> opNodePtr = std::make_unique<Node>();
				opNodePtr->lexeme = peek().lexeme;
				advance();
				opNodePtr->type = NodeType::BINARYOP;
				opNodePtr->left = std::move(nodePtr);
				opNodePtr->right = parseFactor();
				nodePtr = std::move(opNodePtr);
			}
			
			return nodePtr;
		}

        std::unique_ptr<Node> parseExpr() {
			std::unique_ptr<Node> nodePtr = parseTerm();
			
			while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
				std::unique_ptr<Node> opNodePtr = std::make_unique<Node>();
				opNodePtr->lexeme = peek().lexeme;
				advance();
				opNodePtr->type = NodeType::BINARYOP;
				opNodePtr->left = std::move(nodePtr);
				opNodePtr->right = parseTerm();
				nodePtr = std::move(opNodePtr);
			}
			
			return nodePtr;
        }

    public:
		// # Constructor/Destructor functions #
        Parser(const std::vector<Token> &tokenList)
            : tokens(tokenList), nTokens(tokenList.size()), currentIndex(0) {}
        
        std::unique_ptr<Node> parse() {
			return parseExpr();
        }
};