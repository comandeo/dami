#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

static const char WHITESPACES[] = " \n\t";

static const char DELIMITERS[] = "()";

static const char QUOTES = '"';

tokenizer_t::tokenizer_t(const char* input)
{
	if (input != NULL) {
		input_ = (char*) malloc(strlen(input) + 1);
		strcpy(input_, input);
	}
	current_position_ = input_;
}

tokenizer_t::~tokenizer_t()
{
	if (input_ != NULL) {
		free(input_);
	}
}

token_t* tokenizer_t::get_next_token()
{
	if (current_position_ == NULL ||
		current_position_ == '\0' ||
		strlen(current_position_) == 0
	) {
        return new token_t(END_OF_INPUT, std::string(""));
	}
	char* begin_token_pos = current_position_;
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
    token_type_t token_type = UNKNOWN;
    std::string token_value("");
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
		token_type = LBRACE;
	} else if (strcmp(token_string, ")") == 0) {
		token_type = RBRACE;
	} else if (token_string[0] == QUOTES) {
        token_value = std::string(token_string + 1, strlen(token_string) - 2);
		token_type = STRING;
	} else {
		token_value = std::string(token_string);
		char* p = NULL;
		long int long_value = strtol(token_string, &p, 10);
		if (!(long_value == 0L && p == token_string)) {
			token_type = INTEGER;
		} else {
			token_type = IDENTIFIER;
		}
	}
	free(token_string);
	current_position_ = end_token_pos;
	return new token_t(token_type, token_value);
}

token_t::token_t(token_type_t t, std::string v) : type(t), value(v) {}

std::string token_t::name()
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
