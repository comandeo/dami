#ifndef __PARSER_H
#define __PARSER_H

#include "ast.h"
#include "stack.h"
#include "tokenizer.h"

typedef struct parser_t {
	node_stack_t* node_stack;
	tokenizer_t* tokenizer;

} parser_t;

parser_t* create_parser(tokenizer_t* tokenizer);

ast_node_t* parse(parser_t* parser);

#endif
