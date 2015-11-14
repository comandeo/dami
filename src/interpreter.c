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

static int plus(stack_t* stack)
{
	if (!stack) {
		return -1;
	}
	puts("Called plus");
	integer_value_t *value = NULL;
	stack_pop(stack, (void**)&value);
	if (!value || !value->content) {
		return -1;
	}
	long int first_argument = *value->content;
	release_value((value_t*)value);
	value = NULL;
	printf("Plus first argument: %ld\n", first_argument);
	stack_pop(stack, (void**)&value);
	if (!value || !value->content) {
		return -1;
	}
	long int second_argument = *value->content;
	release_value((value_t*)value);
	value = NULL;
	printf("Plus second argument: %ld\n", second_argument);
	integer_value_t* return_value = (integer_value_t*)create_value(T_INTEGER);
	return_value->content = malloc(sizeof(long int));
	if (!return_value->content) {
		release_value((value_t*)return_value);
		return -1;
	}
	*return_value->content = first_argument + second_argument;
	stack_push(stack, (void *)return_value);
	return 0;
}

static int print(stack_t* stack)
{
	if (!stack) {
		return -1;
	}
	puts("Called plus");
	value_t *value = NULL;
	stack_pop(stack, (void**)&value);
	if (!value || !value->content) {
		return -1;
	}
	print_value(value);
	release_value(value);
	return 0;
}

static void setup_standard_library(interpreter_t* interpreter)
{
	function_t* plus_fn = malloc(sizeof(function_t));
	plus_fn->name = "+";
	plus_fn->arguments_number = 2;
	plus_fn->argument_types = calloc(plus_fn->arguments_number, sizeof(type_t));
	plus_fn->argument_types[0] = T_INTEGER;
	plus_fn->argument_types[1] = T_INTEGER;
	plus_fn->call = &plus;
	put_to_hashtable(interpreter->functions_table, plus_fn->name, plus_fn, sizeof(function_t));

	function_t* print_fn = malloc(sizeof(function_t));
	print_fn->name = "print";
	print_fn->arguments_number = 1;
	print_fn->argument_types = calloc(print_fn->arguments_number, sizeof(type_t));
	print_fn->argument_types[0] = T_ANY;
	print_fn->call = &print;
	put_to_hashtable(interpreter->functions_table, print_fn->name, print_fn, sizeof(function_t));

}

interpreter_t* create_interpreter()
{
	interpreter_t* interpreter = malloc(sizeof(interpreter_t));
	interpreter->functions_table = create_hashtable(1024);
	interpreter->stack = create_stack();
	setup_standard_library(interpreter);
	return interpreter;
}

void release_interpreter(interpreter_t* interpreter)
{
	if (interpreter == NULL) {
		return;
	}
	// TODO: release hashtable
	release_stack(interpreter->stack);
	free(interpreter);
}

int process_function_call_node(interpreter_t* interpreter, ast_node_t* node)
{
	function_t* function  = get_from_hashtable(interpreter->functions_table, node->token->value);
	if (function == NULL) {
		return -1;
	}
	value_t* argument = NULL;
	ast_node_t* argument_node = node->first_child;
	size_t argument_number = 0;
	while (argument_node) {
		if (argument_node->type == FUNCTION_CALL) {
			process_function_call_node(interpreter, argument_node);
			argument_number++;
			argument_node = argument_node->next_sibiling;
		} else if (
			function->argument_types[argument_number] == T_ANY ||
			get_type_by_node_type(argument_node->type) == function->argument_types[argument_number]
		) {
			argument = create_value(get_type_by_node_type(argument_node->type));
			argument->content = argument_node->value;
			stack_push(interpreter->stack, (void*)argument);
			argument_number++;
			argument_node = argument_node->next_sibiling;
		} else {
			puts("OMG Panic!");
			return -1;
		}
	}
	if (argument_number < function->arguments_number - 1) {
		size_t i;
		for (i = 0; i < argument_number; i++) {
			stack_pop(interpreter->stack, (void**)&argument);
			if (argument) {
				release_value(argument);
			}
		}
		return -1;
	}
	printf("Calling function: %s\n", function->name);
	int return_code = function->call(interpreter->stack);
	if (return_code != 0) {
		puts("OMG Panic!");
		exit(-1);
	}
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
