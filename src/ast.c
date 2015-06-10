#include <stdio.h>
#include "ast.h"
#include "tokenizer.h"

void print_tree(ast_node_t* root, int spaces)
{
	int i = 0;
	for(i = 0; i < spaces; i++) {
		putchar(' ');
	}
	if (root == NULL) {
		puts("(empty)");
		return;
	}
	if (root->token) {
		printf("%s", get_token_name(root->token->type));
		if (root->token->value) {
			printf(" (%s)", root->token->value);
		}
	}
	printf("\n");
	int child_number = 1;
	ast_node_t* node = root->first_child;
	while (node != NULL) {
		for(i = 0; i < spaces; i++) {
			putchar(' ');
		}
		printf("Child #%d\n", child_number);
		print_tree(node, spaces + 1);
		node = node->next_sibiling;
		child_number++;
	}
}

ast_node_t create_ast_node()
{
	ast_node_t node;
	node.token = NULL;
	node.first_child = NULL;
	node.next_sibiling = NULL;
	return node;
}
