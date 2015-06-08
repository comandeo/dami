#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

parser_t create_parser(tokenizer_t* tokenizer)
{
	if (tokenizer == NULL) {
		exit(-1);
	}
	parser_t parser;
	parser.stack = create_stack();
	parser.tokenizer = tokenizer;
	return parser;

}

void parse(parser_t* parser)
{
	while (1) {
		token_t token = get_next_token(parser->tokenizer);
		switch (token.type) {
			case END_OF_INPUT:
				puts("End reached");
				return;
			case INTEGER:
				printf("INTEGER with value %s\n", token.value);
				push(&parser->stack, token);
				break;
			case IDENTIFIER:
				puts("IDENTIFIER");
				push(&parser->stack, token);
				break;
			case LBRACE:
				puts("LBRACE");
				push(&parser->stack, token);
				break;
			case RBRACE:
				puts("RBRACE");
				token_t* op1;
				token_t* op2;
				token_t* fn;
				if (pop(&parser->stack, &op2) == EMPTY_STACK) {
					puts("ERROR!");
					exit(-1);
				}
				if (pop(&parser->stack, &op1) == EMPTY_STACK) {
					puts("ERROR!");
					exit(-1);
				}
				if (pop(&parser->stack, &fn) == EMPTY_STACK) {
					puts("ERROR!");
					exit(-1);
				}
				printf("Node: (%d %s %s)\n", fn->type, op1->value, op2->value);
				break;
			default:
				puts("UNKNOWN TOKEN");
		}
	}
}
