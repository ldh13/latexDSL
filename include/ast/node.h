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
};