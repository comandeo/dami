#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"
#include "tokenizer.h"

int plus(ast_node_t* node, value_t* return_value)
{
	puts("Called plus");
	long int first_argument = *(long int*)node->first_child->value;
	long int second_argument = *(long int*)node->first_child->next_sibiling->value;
	return_value->type = T_INTEGER;
	return_value->content = malloc(sizeof(long int));
	*((long int*)return_value->content) = first_argument + second_argument;
	return 0;
}

static void setup_standard_library(interpreter_t* interpreter)
{
	function_t* plus_fn = malloc(sizeof(function_t));
	plus_fn->name = "+";
	plus_fn->arguments_number = 2;
	plus_fn->call = &plus;
	put_to_hashtable(interpreter->functions_table, "+", plus_fn, sizeof(function_t));
}

interpreter_t* create_interpreter()
{
	interpreter_t* interpreter = malloc(sizeof(interpreter_t));
	interpreter->functions_table = create_hashtable(1024);
	setup_standard_library(interpreter);
	return interpreter;
}

void release_interpreter(interpreter_t* interpreter)
{
	if (interpreter == NULL) {
		return;
	}
	// TODO: release hashtable
	free(interpreter);
}

int process_ast_node(interpreter_t* interpreter, ast_node_t* root)
{
	if (interpreter == NULL || root == NULL) {
		return -1;
	}
	function_t* function = NULL;
	ast_node_t* node = NULL;
	value_t return_value;
	switch (root->type) {
		case PROGRAM:
		puts("Program started");
		node = root->first_child;
		while (node) {
			process_ast_node(interpreter, node);
			node = node->next_sibiling;
		}
		return 0;

		case FUNCTION_CALL:
		function = get_from_hashtable(interpreter->functions_table, root->token->value);
		if (function == NULL) {
			return -1;
		}
		printf("Calling function: %s\n", function->name);
		function->call(root, &return_value);
		printf("Returned %ld\n", *(long int*)return_value.content);
		return 0;

		default:
		printf("Unknown node type: %d\n", node->type);
		return -1;
	}
}
