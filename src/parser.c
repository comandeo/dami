#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "ast.h"

parser_t* create_parser(tokenizer_t* tokenizer)
{
	if (tokenizer == NULL) {
		exit(-1);
	}
	parser_t* parser = malloc(sizeof(parser_t));
	parser->node_stack = create_stack();
	parser->tokenizer = tokenizer;
	return parser;

}

ast_node_t* parse(parser_t* parser)
{
	int end_reached = 0;
	ast_node_t* root_node = create_ast_node();
	root_node->type = PROGRAM;
	stack_push(parser->node_stack, root_node);
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
				if (stack_peek(parser->node_stack, (void**)&node) == EMPTY_STACK) {
					exit(-1);
				}
				ast_node_t* integer_node = create_ast_node();
				integer_node->token = token;
				integer_node->type = INTEGER_VALUE;
				integer_node->value = malloc(sizeof(long int));
				*((long int*)integer_node->value) = strtol(token->value, NULL, 10);
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
			case STRING:
				printf("STRING %s\n", token->value);
				if (stack_peek(parser->node_stack, (void**)&node) == EMPTY_STACK) {
					exit(-1);
				}
				if (node->token == NULL) {
					node->token = token;
					node->type = STRING_VALUE;
				} else {
					ast_node_t* new_node = create_ast_node();
					new_node->token = token;
					new_node->type = STRING_VALUE;
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
			case IDENTIFIER:
				printf("IDENTIFIER %s\n", token->value);
				if (stack_peek(parser->node_stack, (void**)&node) == EMPTY_STACK) {
					exit(-1);
				}
				if (node->token == NULL && node->type != PROGRAM) {
					node->type = FUNCTION_CALL;
					node->token = token;
				} else {
					ast_node_t* new_node = create_ast_node();
					new_node->token = token;
					new_node->type = FUNCTION_CALL;
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
				stack_push(parser->node_stack, (void*)create_ast_node());
				break;
			case RBRACE:
				puts("RBRACE");
				stack_pop(parser->node_stack, (void**)&node);
				ast_node_t* parent_node;
				if (stack_peek(parser->node_stack, (void**)&parent_node) != EMPTY_STACK) {
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
					return NULL;
				}
				break;
			default:
				puts("UNKNOWN TOKEN");
				return NULL;
		}
	}
	return root_node;
}
