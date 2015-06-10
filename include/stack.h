#ifndef __STACK_H
#define __STACK_H

#include "tokenizer.h"
#include "ast.h"

#define EMPTY_STACK -999

#define STACK_DEPTH 1024

typedef struct node_stack_t {
	ast_node_t stack[STACK_DEPTH];
	int top;
} node_stack_t;

node_stack_t create_node_stack();

int node_stack_peek(node_stack_t* stack, ast_node_t** item);

int node_stack_pop(node_stack_t* stack, ast_node_t** item);

int node_stack_push(node_stack_t* stack, ast_node_t item);

int node_stack_size(node_stack_t* stack);


#endif
