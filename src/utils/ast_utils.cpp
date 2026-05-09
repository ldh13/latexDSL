#include "utils/ast_utils.h"


// ### FUNCTION DEFINITIONS ###

void print_ast(const Node *root, size_t level) {
	std::cout << std::string(level * 2, '-') << "(" << root->lexeme << ")\n";
	if (root->left) {
		print_ast(root->left.get(), level + 1);
	}
	if (root->right) {
		print_ast(root->right.get(), level + 1);
	}
}