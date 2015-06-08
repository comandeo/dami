#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"
#include "ast.h"
#include "stack.h"

int main(int argc, char** argv)
{
	char input[] = "( + 2 ( + 4 5 ) )";
	printf("Input: %s\n", input);
	tokenizer_t tokenizer = create_tokenizer(input);
	parser_t parser = create_parser(&tokenizer);
	ast_node_t* root = parse(&parser);
	puts("TREE LOADED");
	if (root != NULL) {
		print_tree(root);
	}
	return 0;
}
