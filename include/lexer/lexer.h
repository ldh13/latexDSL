#pragma once

#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include "errors/LexicalError.h"

// ### ENUMS/STRUCTS DEFINITIONS ###

enum class TokenType {
    NUMBER,
    IDENTIFIER,
    LPAREN,
    RPAREN,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    EXPONENT,
    END
};

struct Token {
    TokenType type;
    std::string lexeme;
};


// ### CLASS DEFINITIONS ###

// ## Lexer CLASS ##
class Lexer {
    private:
        std::string input;
        const size_t inputLength;
        size_t currentIndex;

        // THIS FUNCTION THROWS LEXICALERROR
        Token scanNumber() {
            // We are at the start of a number
            std::string number{};
            bool dot = false;
            size_t dot_index = std::string::npos;
            while (currentIndex < inputLength && (std::isdigit(static_cast<unsigned char>(input[currentIndex])) || input[currentIndex] == '.')) {
                // Starting with . error checked at the tokenize function
                if (input[currentIndex] == '.') {
                    if (dot) {
                        throw LexicalError("Invalid number: two instances of \".\"");
                    }
                    dot = true;
                    dot_index = currentIndex;
                }
                number += input[currentIndex++];
            }

            if (dot && dot_index == currentIndex - 1) {
                std::stringstream message;
                message << "Invalid number: " << number;
                throw LexicalError(message.str());
            }

            Token token = { TokenType::NUMBER, number };
            return token;
        }

        Token scanIdentifier() {
            std::string identifier{};
            while (currentIndex < inputLength && (std::isalnum(static_cast<unsigned char>(input[currentIndex])) || input[currentIndex] == '_')) {
                identifier += input[currentIndex++];
            }

            Token token = { TokenType::IDENTIFIER, identifier};
            return token;
        }

        Token scanOperator() {
            TokenType type;
            switch (input[currentIndex]) {
                case '+':
                    type = TokenType::PLUS;
                    break;
                case '-':
                    type = TokenType::MINUS;
                    break;
                case '*':
                    type = TokenType::MULTIPLY;
                    break;
                case '/':
                    type = TokenType::DIVIDE;
                    break;
                case '^':
                    type = TokenType::EXPONENT;
                    break;
                default:
                    std::stringstream message;
                    message << "Invalid Operator: " << input[currentIndex];
                    throw LexicalError(message.str());
            }

            Token token = { type, std::string(1, input[currentIndex++]) };
            return token;
        }
		// TODO: SHOULD THIS THROW IF IT ENCOUNTERS SOMETHING ELSE???
        Token scanPunctuation() {
            TokenType type;
            if (input[currentIndex] == '(') {
                type = TokenType::LPAREN;
            } else {
                type = TokenType::RPAREN;
            }

            Token token = { type, std::string(1, input[currentIndex++]) };
            return token;
        }

    public:
        Lexer(const std::string &source)
            : input(source), inputLength(source.size()), currentIndex(0) {}

        std::vector<Token> tokenize() {
            std::vector<Token> tokens;
            char current;

            while (currentIndex < inputLength) {
                current = input[currentIndex];
                if (std::isdigit(static_cast<unsigned char>(current))) {
                    tokens.push_back(scanNumber());
                } else if (std::isalpha(static_cast<unsigned char>(current)) || current == '_') {
                    tokens.push_back(scanIdentifier());
                } else if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') {
                    tokens.push_back(scanOperator());
                } else if (current == '(' || current == ')') {
                    tokens.push_back(scanPunctuation());
                } else if (std::isspace(static_cast<unsigned char>(current))) {
                    ++currentIndex;
                    continue;
                } else {
                    std::stringstream message;
                    message << "Unknown character: " << input[currentIndex];
                    throw LexicalError(message.str());
                }
            }

			tokens.push_back({ TokenType::END, "" });
            return tokens;
        }
};