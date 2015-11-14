#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"
#include "tokenizer.h"

static type_t get_type_by_node_type(ast_node_type_t node_type)
{
	switch(node_type) {
		case INTEGER_VALUE:
		return T_INTEGER;

		default:
		return T_UNKNOWN;
	}
}

static int plus(value_t** arguments, value_t* return_value)
{
	puts("Called plus");
	long int first_argument = ((integer_value_t*)arguments[0])->content;
	long int second_argument = ((integer_value_t*)arguments[1])->content;
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
	plus_fn->argument_types = calloc(2, sizeof(type_t));
	plus_fn->argument_types[0] = T_INTEGER;
	plus_fn->argument_types[1] = T_INTEGER;
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

int process_function_call_node(interpreter_t* interpreter, ast_node_t* node)
{
	function_t* function  = get_from_hashtable(interpreter->functions_table, node->token->value);
	if (function == NULL) {
		return -1;
	}
	value_t** arguments = calloc(function->arguments_number, sizeof(value_t*));
	ast_node_t* argument_node = node->first_child;
	size_t argument_number = 0;
	while (argument_node) {
		if (get_type_by_node_type(argument_node->type) != function->argument_types[argument_number]) {
			// TODO: free memory
			return -1;
		}
		arguments[argument_number] = create_value(function->argument_types[argument_number]);
		arguments[argument_number]->content = argument_node->value;
		argument_number++;
		argument_node = argument_node->next_sibiling;
	}
	if (argument_number < function->arguments_number - 1) {
		// TODO: free memory
		return -1;
	}
	printf("Calling function: %s\n", function->name);
	value_t return_value;
	function->call(arguments, &return_value);
	printf("Returned %ld\n", *(long int*)return_value.content);
	// TODO: free memory
	return 0;
}

int process_ast_node(interpreter_t* interpreter, ast_node_t* root)
{
	if (interpreter == NULL || root == NULL) {
		return -1;
	}
	ast_node_t* node = NULL;
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
		return process_function_call_node(interpreter, root);

		default:
		printf("Unknown node type: %d\n", node->type);
		return -1;
	}
}
