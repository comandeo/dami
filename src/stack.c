#include <stdlib.h>
#include "stack.h"

stack_t* create_stack()
{
	stack_t* stack = malloc(sizeof(stack_t));
	stack->top = 0;
	return stack;
}

void release_stack(stack_t* stack)
{
	if (stack == NULL) {
		return;
	}
	while (stack->top != 0) {
		void* node;
		stack_pop(stack, &node);
		free(node);
	}
	free(stack);
}

int stack_peek(stack_t* stack, void** item)
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
	*item = stack->stack[stack->top];
	return 0;
}

int stack_pop(stack_t* stack, void** item)
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
	*item = stack->stack[stack->top];
	stack->top--;
	return 0;
}

int stack_push(stack_t* stack, void* item)
{
	if (stack == NULL) {
		return -1;
	}
	if (stack->top == STACK_DEPTH) {
		return -1;
	}
	stack->top++;
	stack->stack[stack->top] = item;
	return 0;
}

int stack_size(stack_t* stack)
{
		if (stack == NULL) {
			return 0;
		}
		return stack->top;
}
