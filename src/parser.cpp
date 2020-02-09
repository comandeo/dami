#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "ast.h"

parser_t::parser_t(tokenizer_t* tokenizer)
{
	if (tokenizer == NULL) {
		exit(-1);
	}
	this->tokenizer = tokenizer;
}

ast_node_t* parser_t::parse()
{
	int end_reached = 0;
	ast_node_t* root_node = create_ast_node();
	root_node->type = PROGRAM;
	node_stack.push(root_node);
	while (!end_reached) {
		ast_node_t* node;
		token_t* token = (token_t*) malloc(sizeof(token_t));
		*token = get_next_token(tokenizer);
		switch (token->type) {
			case END_OF_INPUT:
				puts("End reached");
				end_reached = 1;
				break;
			case INTEGER:
			{
				printf("INTEGER with value %s\n", token->value);
				if (node_stack.empty()) {
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
					while(last_child->next_sibling != NULL) {
						last_child = last_child->next_sibling;
					}
					last_child->next_sibling = integer_node;
				}
				break;
			}
			case STRING:
				printf("STRING %s\n", token->value);
				node = node_stack.top();
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
						while(last_child->next_sibling != NULL) {
							last_child = last_child->next_sibling;
						}
						last_child->next_sibling = new_node;
					}
				}
				break;
			case IDENTIFIER:
				printf("IDENTIFIER %s\n", token->value);
				node = node_stack.top();
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
						while(last_child->next_sibling != NULL) {
							last_child = last_child->next_sibling;
						}
						last_child->next_sibling = new_node;
					}
				}
				break;
			case LBRACE:
				puts("LBRACE");
				node_stack.push(create_ast_node());
				break;
			case RBRACE: {
                puts("RBRACE");
                node = node_stack.top();
                node_stack.pop();
                ast_node_t *parent_node = node_stack.top();
                if (parent_node->first_child == NULL) {
                    parent_node->first_child = node;
                } else {
                    ast_node_t *last_child = parent_node->first_child;
                    while (last_child->next_sibling != NULL) {
                        last_child = last_child->next_sibling;
                    }
                    last_child->next_sibling = node;
                }
                break;
            }
			default:
				puts("UNKNOWN TOKEN");
				return NULL;
		}
	}
	return root_node;
}
