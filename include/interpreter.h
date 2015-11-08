#ifndef __INTERPRETER_H
#define __INTERPRETER_H 1

#include "ast.h"

typedef struct function {
	char* name;
} function_t;

typedef struct interpreter {

} interpreter_t;

interpreter_t* create_interpreter();

void release_interpreter(interpreter_t* interpreter);

void process_ast_node(interpreter_t* interpreter, ast_node_t* root);

#endif
