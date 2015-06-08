#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"

int main(int argc, char** argv)
{
	char input[] = "( + 2 3 )";
	printf("Input: %s\n", input);
	tokenizer_t tokenizer = create_tokenizer(input);
	parser_t parser = create_parser(&tokenizer);
	parse(&parser);
	return 0;
}
