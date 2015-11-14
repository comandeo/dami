#ifndef __STACK_H
#define __STACK_H

#include "tokenizer.h"
#include "ast.h"

#define EMPTY_STACK -999

#define STACK_DEPTH 1024

typedef struct stack_t {
	void* stack[STACK_DEPTH];
	int top;
} stack_t;

stack_t* create_stack();

void release_stack(stack_t* stack);

int stack_peek(stack_t* stack, void** item);

int stack_pop(stack_t* stack, void** item);

int stack_push(stack_t* stack, void* item);

int stack_size(stack_t* stack);

#endif
