#include <stdlib.h>
#include "stack.h"

node_stack_t* create_node_stack()
{
	node_stack_t* stack = malloc(sizeof(node_stack_t));
	stack->top = 0;
	return stack;
}

void release_node_stack(node_stack_t* stack)
{
	if (stack == NULL) {
		return;
	}
	while (stack->top != 0) {
		ast_node_t* node;
		node_stack_pop(stack, &node);
		free(node);
	}
	free(stack);
}

int node_stack_peek(node_stack_t* stack, ast_node_t** item)
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

int node_stack_pop(node_stack_t* stack, ast_node_t** item)
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

int node_stack_push(node_stack_t* stack, ast_node_t* item)
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

int node_stack_size(node_stack_t* stack)
{
		if (stack == NULL) {
			return 0;
		}
		return stack->top;
}
