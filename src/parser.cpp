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
    ast_node_t* root_node = new ast_node_t();
	root_node->type = PROGRAM;
	node_stack.push(root_node);
    ast_node_t* node = nullptr;
	while (!end_reached) {
		token_t* token =  tokenizer->get_next_token();
		switch (token->type) {
			case END_OF_INPUT:
				end_reached = 1;
				break;
			case INTEGER:
			{
				if (node_stack.empty()) {
					exit(-1);
				}
				ast_node_t* integer_node = new ast_node_t();
				integer_node->token = token;
				integer_node->type = INTEGER_VALUE;
                integer_node->value = new integer_value_t(strtol(token->value.c_str(), NULL, 10));
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
				node = node_stack.top();
				if (node->token == NULL) {
					node->token = token;
					node->type = STRING_VALUE;
                    node->value = new string_value_t(token->value);
				} else {
                    ast_node_t* new_node = new ast_node_t();
					new_node->token = token;
					new_node->type = STRING_VALUE;
                    new_node->value = new string_value_t(token->value);
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
				node = node_stack.top();
				if (node->token == NULL && node->type != PROGRAM) {
					node->type = FUNCTION_CALL;
					node->token = token;
				} else {
					ast_node_t* new_node = new ast_node_t();
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
				node_stack.push(new ast_node_t());
				break;
			case RBRACE: {
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
				return NULL;
		}
	}
	return root_node;
}
