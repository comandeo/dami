#include <stdlib.h>
#include "stack.h"

dami_stack_t create_stack()
{
	dami_stack_t stack;
	stack.top = 0;
	return stack;
}

int peek(dami_stack_t* stack, token_t** item)
{
	if (stack == NULL) {
		return -1;
	}
	if (stack->top == 0) {
		return EMPTY_STACK;
	}
	if (item == NULL) {
		return -1;
	}
	*item = &stack->_stack[stack->top];
	return 0;
}

int pop(dami_stack_t* stack, token_t** item)
{
	if (stack == NULL) {
		return -1;
	}
	if (stack->top == 0) {
		return EMPTY_STACK;
	}
	if (item == NULL) {
		return -1;
	}
	*item = &stack->_stack[stack->top];
	stack->top--;
	return 0;
}

int push(dami_stack_t* stack, token_t item)
{
	if (stack == NULL) {
		return -1;
	}
	if (stack->top == STACK_DEPTH) {
		return -1;
	}
	stack->top++;
	stack->_stack[stack->top] = item;
	return 0;
}
