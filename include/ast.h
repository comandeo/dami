#ifndef __NODE_H
#define __NODE_H value

#include "value.h"
#include "tokenizer.h"

typedef enum ast_node_type {
	PROGRAM = 1,
	FUNCTION_CALL,
	INTEGER_VALUE,
	STRING_VALUE
} ast_node_type_t;

struct ast_node_t {
    ~ast_node_t();
    void print_tree(int spaces);
    
	token_t* token;
	ast_node_type_t type;
	value_t* value;
	struct ast_node_t* first_child;
	struct ast_node_t* next_sibling;
};

#endif
