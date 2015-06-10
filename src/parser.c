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
	parser.node_stack = create_node_stack();
	parser.tokenizer = tokenizer;
	return parser;

}

ast_node_t* parse(parser_t* parser)
{
	int end_reached = 0;
	while (!end_reached) {
		ast_node_t* node;
		token_t* token = (token_t*) malloc(sizeof(token_t));
		*token = get_next_token(parser->tokenizer);
		switch (token->type) {
			case END_OF_INPUT:
				puts("End reached");
				end_reached = 1;
				break;
			case INTEGER:
				printf("INTEGER with value %s\n", token->value);
				if (node_stack_peek(&parser->node_stack, &node) == EMPTY_STACK) {
					exit(-1);
				}
				ast_node_t* integer_node = (ast_node_t*) malloc(sizeof(ast_node_t));
				*integer_node = create_ast_node();
				integer_node->token = token;
				if (node->first_child == NULL) {
					node->first_child = integer_node;
				} else {
					ast_node_t* last_child = node->first_child;
					while(last_child->next_sibiling != NULL) {
						last_child = last_child->next_sibiling;
					}
					last_child->next_sibiling = integer_node;
				}
				break;
			case IDENTIFIER:
				printf("IDENTIFIER %s\n", token->value);
				if (node_stack_peek(&parser->node_stack, &node) == EMPTY_STACK) {
					exit(-1);
				}
				if (node->token == NULL) {
					node->token = token;
				} else {
					ast_node_t* new_node = (ast_node_t*) malloc(sizeof(ast_node_t));
					*new_node = create_ast_node();
					new_node->token = token;
					ast_node_t* last_child = node->first_child;
					if (node->first_child == NULL) {
						node->first_child = new_node;
					} else {
						ast_node_t* last_child = node->first_child;
						while(last_child->next_sibiling != NULL) {
							last_child = last_child->next_sibiling;
						}
						last_child->next_sibiling = new_node;
					}
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
					if (parent_node->first_child == NULL) {
						parent_node->first_child = node;
					} else {
						ast_node_t* last_child = parent_node->first_child;
						while(last_child->next_sibiling != NULL) {
							last_child = last_child->next_sibiling;
						}
						last_child->next_sibiling = node;
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
