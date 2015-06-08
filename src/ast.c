#include <stdio.h>
#include "ast.h"
#include "tokenizer.h"

void print_tree(ast_node_t* root)
{
	if (root == NULL) {
		puts("(empty)");
		return;
	}
	printf("%s", get_token_name(root->token->type));
	if (root->token->value) {
		printf(" (%s)", root->token->value);
	}
	printf("\n");
	puts("Left child:");
	if (root->left_child) {
		print_tree(root->left_child);
	} else {
		puts("(x)");
	}
	puts("Right child:");
	if (root->right_child) {
		print_tree(root->right_child);
	} else {
		puts("(x)");
	}
}

ast_node_t create_ast_node()
{
	ast_node_t node;
	node.token = NULL;
	node.left_child = NULL;
	node.right_child = NULL;
	return node;
}
