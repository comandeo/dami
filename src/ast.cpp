#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "tokenizer.h"

static char* get_node_name(ast_node_type_t type)
{
	switch (type) {
		case PROGRAM:
		return "PROGRAM";
		case FUNCTION_CALL:
		return "FUNCTION_CALL";
		case INTEGER_VALUE:
		return "INTEGER_VALUE";
		case STRING_VALUE:
		return "STRING_VALUE";
		default:
		return "UNKNOWN NODE TYPE";
	}
}

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
	printf("Node: (%s) ", get_node_name(root->type));
	if (root->token) {
		printf("Token: %s", get_token_name(root->token->type));
		if (root->token->value) {
			printf(" (%s)", root->token->value);
		}
	} else {
		printf("(no token)");
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
		node = node->next_sibling;
		child_number++;
	}
}

ast_node_t* create_ast_node()
{
	ast_node_t* node = (ast_node_t*) malloc(sizeof(ast_node_t));
	node->token = NULL;
	node->value = NULL;
	node->first_child = NULL;
	node->next_sibling = NULL;
	return node;
}

void release_ast_node(ast_node_t* node)
{
	if (!node) {
		return;
	}
	free(node);
}
