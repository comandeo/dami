#ifndef __NODE_H
#define __NODE_H value

#include "tokenizer.h"

typedef struct ast_node_t {
	token_t* token;
	struct ast_node_t* first_child;
	struct ast_node_t* next_sibiling;
} ast_node_t;

void print_tree(ast_node_t* root, int spaces);

ast_node_t* create_ast_node();

void release_ast_node(ast_node_t* node);

#endif
