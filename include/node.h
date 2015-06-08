#ifndef __NODE_H
#define __NODE_H value

#include "tokenizer.h"

typedef struct ast_node_t {
	token_t* token;
	ast_node_t* left_child;
	ast_node_t* right_child;
} ast_node_t;

#endif
