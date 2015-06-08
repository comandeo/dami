#ifndef __TOKENIZER_H
#define __TOKENIZER_H

typedef enum token_type {
	INTEGER = 1,
	STRING,
	IDENTIFIER = 100,
	LBRACE,
	RBRACE,
	NODE,
	END_OF_INPUT
} token_type_t;

typedef struct token {
	token_type_t type;
	char* value;
} token_t;

typedef struct tokenizer {
	char* input;
	int first_call;
} tokenizer_t;

tokenizer_t create_tokenizer(const char* input);

void release_tokenizer(tokenizer_t tokenizer);

token_t get_next_token(tokenizer_t* tokenizer);

void release_token(token_t token);

char* get_token_name(token_type_t type);

#endif
