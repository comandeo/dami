#ifndef __TOKENIZER_H
#define __TOKENIZER_H

#include <string>

typedef enum token_type {
	INTEGER = 1,
	STRING,
	IDENTIFIER = 100,
	LBRACE,
	RBRACE,
	NODE,
	END_OF_INPUT,
    UNKNOWN
} token_type_t;

struct token_t {
public:
    token_t(token_type_t t, std::string v = std::string(""));
    ~token_t();
    std::string name();

	token_type_t type;
	std::string value;
};

class tokenizer_t {
public:
    tokenizer_t(const char* input);
    ~tokenizer_t();
    token_t* get_next_token();
private:
	char* input_;
	char* current_position_;
};

#endif
