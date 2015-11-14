#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"
#include "ast.h"
#include "stack.h"
#include "interpreter.h"
#include "value.h"

int main(int argc, char** argv)
{
	if (argc < 2) {
		puts("Usage: dami source_file");
		return -1;
	}
	FILE* input_file = fopen (argv[1], "rb");
	if (!input_file) {
		puts("Cannot open imput file");
		return -1;
	}
	char* buffer = NULL;
	long length;
	fseek (input_file, 0, SEEK_END);
	length = ftell (input_file);
	fseek (input_file, 0, SEEK_SET);
	buffer = malloc(length + 1);
	fread (buffer, 1, length, input_file);
	printf("Input: %s\n", buffer);
	buffer[length] = 0;
	tokenizer_t* tokenizer = create_tokenizer(buffer);
	parser_t* parser = create_parser(tokenizer);
	ast_node_t* root = parse(parser);
	puts("***********");
	puts("TREE LOADED");
	puts("***********");
	if (root != NULL) {
		print_tree(root, 0);
	}
	release_tokenizer(tokenizer);
	puts("***********");
	puts("RUNNING INTERPRETER");
	puts("***********");
	interpreter_t* interpreter = create_interpreter();
	process_ast_node(interpreter, root);
	fclose(input_file);
	return 0;
}
