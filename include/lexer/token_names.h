#pragma once

#include <unordered_map>
#include <string>
#include "lexer/lexer.h"


// ### TokenType LOOKUP-TABLE ###

namespace lexer {
	
inline std::unordered_map<TokenType, std::string> tokenTypeNames = {
	{ TokenType::NUMBER, "NUMBER" }, { TokenType::IDENTIFIER, "IDENTIFIER" },
	{ TokenType::LPAREN, "LPAREN" }, { TokenType::RPAREN, "RPAREN" },
	{ TokenType::PLUS, "PLUS" }, { TokenType::MINUS, "MINUS" },
	{ TokenType::MULTIPLY, "MULTIPLY" }, { TokenType::DIVIDE, "DIVIDE" },
	{ TokenType::EXPONENT, "EXPONENT" }, { TokenType::END, "END" }
};
	
}
