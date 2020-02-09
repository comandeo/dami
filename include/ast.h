#ifndef __NODE_H
#define __NODE_H value

#include "tokenizer.h"

typedef enum ast_node_type {
	PROGRAM = 1,
	FUNCTION_CALL,
	INTEGER_VALUE,
	STRING_VALUE
} ast_node_type_t;

struct ast_node_t {
	token_t* token;
	ast_node_type_t type;
	void* value;
	struct ast_node_t* first_child;
	struct ast_node_t* next_sibling;
};

void print_tree(ast_node_t* root, int spaces);

ast_node_t* create_ast_node();

void release_ast_node(ast_node_t* node);

#endif
