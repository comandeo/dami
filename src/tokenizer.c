#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

static const char WHITESPACES[] = " \n\t";

static const char DELIMITERS[] = "()";

static const char QUOTES = '"';

tokenizer_t* create_tokenizer(const char* input)
{
	tokenizer_t* tokenizer = malloc(sizeof(tokenizer_t));
	tokenizer->input = NULL;
	if (input != NULL) {
		tokenizer->input = (char*) malloc(strlen(input) + 1);
		strcpy(tokenizer->input, input);
	}
	tokenizer->current_position = tokenizer->input;
	return tokenizer;
}

void release_tokenizer(tokenizer_t* tokenizer)
{
	if (tokenizer->input != NULL) {
		free(tokenizer->input);
	}
	free(tokenizer);
}

token_t get_next_token(tokenizer_t* tokenizer)
{
	if (tokenizer == NULL) {
		exit(-1);
	}
	token_t token;
	token.value = NULL;
	if (tokenizer->current_position == NULL ||
		tokenizer->current_position == '\0' ||
		strlen(tokenizer->current_position) == 0
	) {
		token.type = END_OF_INPUT;
		return token;
	}
	char* begin_token_pos = tokenizer->current_position;
	while(strchr(WHITESPACES, begin_token_pos[0]) != NULL) {
		begin_token_pos++;
	}
	char* end_token_pos = begin_token_pos;
	while(
		strchr(DELIMITERS, end_token_pos[0]) == NULL &&
		strchr(WHITESPACES, end_token_pos[0]) == NULL
	) {
		end_token_pos++;
	}
	char* token_string = NULL;
	if (begin_token_pos == end_token_pos) {
		token_string = (char*) malloc(2);
		token_string[0] = begin_token_pos[0];
		token_string[1] = '\0';
		end_token_pos++;
	} else {
		int token_string_length = end_token_pos - begin_token_pos;
		token_string = (char*) malloc(token_string_length + 1);
		strncpy(token_string, begin_token_pos, token_string_length);
	}
	if (token_string) {
		printf("Token string: '%s'\n", token_string);
	}
	if (strcmp(token_string, "(") == 0) {
		token.type = LBRACE;
	} else if (strcmp(token_string, ")") == 0) {
		token.type = RBRACE;
	} else if (token_string[0] == QUOTES) {
		token.value = (char*) malloc(strlen(token_string) - 1);
		strncpy(token.value, token_string + 1, strlen(token_string) - 2);
		token.type = STRING;
	} else {
		token.value = (char*) malloc(strlen(token_string) + 1);
		strcpy(token.value, token_string);
		char* p = NULL;
		long int long_value = strtol(token_string, &p, 10);
		if (!(long_value == 0L && p == token_string)) {
			token.type = INTEGER;
		} else {
			token.type = IDENTIFIER;
		}
	}
	free(token_string);
	tokenizer->current_position = end_token_pos;
	// printf("Input left: '%s'\n", tokenizer->current_position);
	return token;
}

void release_token(token_t token)
{
	if (token.value != NULL) {
		free(token.value);
	}
}

char* get_token_name(token_type_t type)
{
	switch (type) {
		case INTEGER:
			return "INTEGER";
		case STRING:
			return "STRING";
		case IDENTIFIER:
			return "IDENTIFIER";
		case LBRACE:
			return "LBRACE";
		case RBRACE:
			return "RBRACE";
		case NODE:
			return "NODE";
		case END_OF_INPUT:
			return "END_OF_INPUT";
		default:
			return "UNKNOWN TOKEN";
	}
}
