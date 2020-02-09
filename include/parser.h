#ifndef __PARSER_H
#define __PARSER_H

#include <stack>
#include "ast.h"

class parser_t {
	public:
		parser_t(tokenizer_t* tokenizer);
		ast_node_t* parse();
	private:
		tokenizer_t* tokenizer;
		std::stack<ast_node_t*> node_stack;

};

#endif
