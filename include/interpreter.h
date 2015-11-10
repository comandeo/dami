#ifndef __INTERPRETER_H
#define __INTERPRETER_H 1

#include "ast.h"
#include "hashtable.h"

typedef enum type {
	T_INTEGER = 1,
	T_STRING
} type_t;

typedef struct value {
	type_t type;
	void* content;
} value_t;

typedef struct function {
	char* name;
	unsigned int arguments_number;
	int (*call)(ast_node_t* node, value_t* return_value);
} function_t;

typedef struct interpreter {
	hashtable_t* functions_table;
} interpreter_t;

interpreter_t* create_interpreter();

void release_interpreter(interpreter_t* interpreter);

int process_ast_node(interpreter_t* interpreter, ast_node_t* root);

#endif
