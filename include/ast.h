#ifndef __NODE_H
#define __NODE_H value

#include "tokenizer.h"

typedef struct ast_node_t {
	token_t* token;
	struct ast_node_t* left_child;
	struct ast_node_t* right_child;
} ast_node_t;

void print_tree(ast_node_t* root);

ast_node_t create_ast_node();

#endif
