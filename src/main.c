#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"
#include "ast.h"
#include "stack.h"

int main(int argc, char** argv)
{
	printf("Input: %s\n", argv[1]);
	tokenizer_t tokenizer = create_tokenizer(argv[1]);
	parser_t parser = create_parser(&tokenizer);
	ast_node_t* root = parse(&parser);
	puts("***********");
	puts("TREE LOADED");
	puts("***********");
	if (root != NULL) {
		print_tree(root, 0);
	}
	
	return 0;
}
