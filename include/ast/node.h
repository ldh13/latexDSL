#pragma once

#include <string>
#include <memory>

// ### ENUM AND STRUCT DEFINITIONS ###

// ## NodeType ENUM ##
enum class NodeType {
    NUMBER,
    IDENTIFIER,
    BINARYOP,
    UNARYOP
};

// ## Node STRUCT ##
struct Node {
    NodeType type;
    std::string lexeme;
    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;
	
	// # Getter-Setter functions #
	const Node* leftChild() const {
		return left.get();
	}
	const Node* rightChild() const {
		return right.get();
	}
};