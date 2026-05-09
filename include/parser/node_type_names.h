#pragma once

#include <unordered_map>
#include <string>
#include "ast/node.h"


// ### NodeType LOOKUP-TABLE ###

namespace parser {
	
inline std::unordered_map<NodeType, std::string> nodeTypeNames = {
	{ NodeType::NUMBER, "NUMBER" }, {NodeType::IDENTIFIER, "IDENTIFIER"},
	{ NodeType::BINARYOP, "BINARYOP" }, {NodeType::UNARYOP, "UNARYOP" }
};
	
}
