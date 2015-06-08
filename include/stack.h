#ifndef __STACK_H
#define __STACK_H

#include "tokenizer.h"

#define EMPTY_STACK -999

static const int STACK_DEPTH = 1024;

typedef struct dami_stack_t {
	token_t _stack[STACK_DEPTH];
	int top;
} dami_stack_t;

dami_stack_t create_stack();

int peek(dami_stack_t* stack, token_t** item);

int pop(dami_stack_t* stack, token_t** item);

int push(dami_stack_t* stack, token_t item);

#endif
