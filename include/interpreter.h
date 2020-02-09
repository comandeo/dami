#ifndef __INTERPRETER_H
#define __INTERPRETER_H 1

#include <stack>
#include <unordered_map>
#include <string>
#include "ast.h"
#include "value.h"

struct function_t {
	std::string name;
	unsigned int arguments_number;
	type_t* argument_types;
	int (*call)(std::stack<value_t*> &stack);
};

struct interpreter_t {
	public:
		interpreter_t();
		int process_ast_node(ast_node_t* root);
	private:
		void setup_standard_library();
		int process_function_call_node(ast_node_t* node);
	private:
		std::stack<value_t*> stack;
		std::unordered_map<std::string, function_t*> functions_table;
};

#endif
