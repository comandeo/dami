#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

static const char DELIMITERS[] = " \n";

tokenizer_t create_tokenizer(const char* input)
{
	tokenizer_t tokenizer;
	tokenizer.first_call = 1;
	tokenizer.input = NULL;
	if (input != NULL) {
		tokenizer.input = (char*) malloc(strlen(input) + 1);
		strcpy(tokenizer.input, input);
	}
	return tokenizer;
}

void release_tokenizer(tokenizer_t tokenizer)
{
	if (tokenizer.input != NULL) {
		free(tokenizer.input);
	}
}

token_t get_next_token(tokenizer_t* tokenizer)
{
	if (tokenizer == NULL) {
		exit(-1);
	}
	token_t token;
	token.value = NULL;
	char* tok = NULL;
	if (tokenizer->first_call) {
		tok = strtok(tokenizer->input, DELIMITERS);
		tokenizer->first_call = 0;
	} else {
		tok = strtok(NULL, DELIMITERS);
	}
	if (tok == NULL) {
		token.type = END_OF_INPUT;
		return token;
	} else if (strcmp(tok, "(") == 0) {
		token.type = LBRACE;
		return token;
	} else if (strcmp(tok, ")") == 0) {
		token.type = RBRACE;
		return token;
	} else {
		token.value = (char*) malloc(strlen(tok) + 1);
		strcpy(token.value, tok);
		// Check if number
		char* p = NULL;
		long int long_value = strtol(tok, &p, 10);
		if (!(long_value == 0L && p == tok)) {
			token.type = INTEGER;
			return token;
		}
		// Check if string
		// TODO implement me
		// Identifier
		token.type = IDENTIFIER;
		return token;
	}
}

void release_token(token_t token)
{
	if (token.value != NULL) {
		free(token.value);
	}
}
