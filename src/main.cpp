#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"
#include "ast.h"
#include "interpreter.h"
#include "value.h"

int main(int argc, char** argv)
{
    /*
	if (argc < 2) {
		puts("Usage: dami source_file");
		return -1;
	}
     */
	FILE* input_file = fopen ("/Users/mitja/my/dami/test/test1.dami", "rb");
	if (!input_file) {
		puts("Cannot open input file");
		puts((char*)NULL);
		return -1;
	}
	char* buffer = NULL;
	long length;
	fseek (input_file, 0, SEEK_END);
	length = ftell (input_file);
	fseek (input_file, 0, SEEK_SET);
	buffer = (char*) malloc(length + 1);
	fread (buffer, 1, length, input_file);
	printf("Input: %s\n", buffer);
	buffer[length] = 0;
	tokenizer_t* tokenizer = new tokenizer_t(buffer);
	parser_t* parser = new parser_t(tokenizer);
	ast_node_t* root = parser->parse();
	puts("***********");
	puts("TREE LOADED");
	puts("***********");
	if (root != NULL) {
		root->print_tree(0);
	} else {
		puts("Parsing error");
		exit(1);
	}
	puts("*******************");
	puts("RUNNING INTERPRETER");
	puts("*******************");
	interpreter_t* interpreter = new interpreter_t();
	interpreter->process_ast_node(root);
	fclose(input_file);
	return 0;
}
