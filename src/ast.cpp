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

void ast_node_t::print_tree(int spaces)
{
	int i = 0;
	for(i = 0; i < spaces; i++) {
		putchar(' ');
	}
	printf("Node: (%s) ", get_node_name(type));
	if (token) {
		printf("Token: %s", token->name().c_str());
        printf(" (%s)", token->value.c_str());
	} else {
		printf("(no token)");
	}
	printf("\n");
	int child_number = 1;
	ast_node_t* node = first_child;
	while (node != NULL) {
		for(i = 0; i < spaces; i++) {
			putchar(' ');
		}
		printf("Child #%d\n", child_number);
		node->print_tree(spaces + 1);
		node = node->next_sibling;
		child_number++;
	}
}

ast_node_t::~ast_node_t()
{
    
}
