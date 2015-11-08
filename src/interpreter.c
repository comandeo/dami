#include <stdlib.h>
#include "interpreter.h"
#include "tokenizer.h"

unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++)) {
    	hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

interpreter_t* create_interpreter()
{
	return malloc(sizeof(interpreter_t));
}

void release_interpreter(interpreter_t* interpreter)
{
	if (interpreter == NULL) {
		return;
	}
	free(interpreter);
}

void process_ast_node(interpreter_t* interpreter, ast_node_t* root)
{
	if (interpreter == NULL || root == NULL) {
		return;
	}
	if (root->token == NULL) {
		return;
	}
	switch (root->token->type) {
		case IDENTIFIER:
		//
		break;
		default:
		return;
	}
}
