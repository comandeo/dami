#ifndef __INTERPRETER_H
#define __INTERPRETER_H 1

#include "ast.h"
#include "hashtable.h"
#include "value.h"
#include "stack.h"

typedef struct function {
	char* name;
	unsigned int arguments_number;
	type_t* argument_types;
	int (*call)(stack_t* stack);
} function_t;

typedef struct interpreter {
	stack_t* stack;
	hashtable_t* functions_table;
} interpreter_t;

interpreter_t* create_interpreter();

void release_interpreter(interpreter_t* interpreter);

int process_ast_node(interpreter_t* interpreter, ast_node_t* root);

#endif
