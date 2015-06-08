#ifndef __PARSER_H
#define __PARSER_H

#include "stack.h"
#include "tokenizer.h"

typedef struct parser_t {
	dami_stack_t stack;
	tokenizer_t* tokenizer;

} parser_t;

parser_t create_parser(tokenizer_t* tokenizer);

void parse(parser_t* parser);

#endif
