#ifndef __STACK_H
#define __STACK_H

#include "tokenizer.h"
#include "ast.h"

#define EMPTY_STACK -999

#define STACK_DEPTH 1024

typedef struct token_stack_t {
	token_t stack[STACK_DEPTH];
	int top;
} token_stack_t;

token_stack_t create_token_stack();

int token_stack_peek(token_stack_t* stack, token_t** item);

int token_stack_pop(token_stack_t* stack, token_t** item);

int token_stack_push(token_stack_t* stack, token_t item);

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
