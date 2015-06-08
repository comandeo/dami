#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "ast.h"

parser_t create_parser(tokenizer_t* tokenizer)
{
	if (tokenizer == NULL) {
		exit(-1);
	}
	parser_t parser;
	parser.token_stack = create_token_stack();
	parser.node_stack = create_node_stack();
	parser.tokenizer = tokenizer;
	return parser;

}

ast_node_t* parse(parser_t* parser)
{
	while (1) {
		ast_node_t* node;
		token_t* token = (token_t*) malloc(sizeof(token_t));
		*token = get_next_token(parser->tokenizer);
		switch (token->type) {
			case END_OF_INPUT:
				puts("End reached");
				return NULL;
			case INTEGER:
				printf("INTEGER with value %s\n", token->value);
				if (node_stack_peek(&parser->node_stack, &node) == EMPTY_STACK) {
					exit(-1);
				}
				ast_node_t* integer_node = (ast_node_t*) malloc(sizeof(ast_node_t));
				integer_node->token = token;
				integer_node->left_child = NULL;
				integer_node->right_child = NULL;
				if (node->left_child == NULL) {
					node->left_child = integer_node;
				} else if (node->right_child == NULL) {
					node->right_child = integer_node;
				} else {
					puts("ERROR");
					exit(-1);
				}
				break;
			case IDENTIFIER:
				puts("IDENTIFIER");
				if (node_stack_peek(&parser->node_stack, &node) == EMPTY_STACK) {
					exit(-1);
				}
				if (node->token == NULL) {
					node->token = token;
				}
				break;
			case LBRACE:
				puts("LBRACE");
				node_stack_push(&parser->node_stack, create_ast_node());
				break;
			case RBRACE:
				puts("RBRACE");
				node_stack_pop(&parser->node_stack, &node);
				ast_node_t* parent_node;
				if (node_stack_peek(&parser->node_stack, &parent_node) != EMPTY_STACK) {
					if (parent_node->left_child == NULL) {
						parent_node->left_child = node;
					} else if (parent_node->right_child == NULL) {
						parent_node->right_child = node;
					} else {
						puts("ERROR");
						exit(-1);
					}
				} else {
					return node;
				}
				break;
			default:
				puts("UNKNOWN TOKEN");
		}
	}
}
