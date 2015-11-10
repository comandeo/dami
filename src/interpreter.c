#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"
#include "tokenizer.h"

void plus(ast_node_t* node)
{
	puts("Called plus");
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
	token_t* token = root->token;
	if (token == NULL) {
		return -1;
	}
	function_t* function = NULL;
	switch (token->type) {
		case IDENTIFIER:
		function = get_from_hashtable(interpreter->functions_table, token->value);
		if (function == NULL) {
			return -1;
		}
		printf("Calling function: %s\n", function->name);
		function->call(root);
		return 0;
		break;

		default:
		return -1;
	}
}
