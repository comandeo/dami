#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"
#include "tokenizer.h"

static type_t get_type_by_node_type(ast_node_type_t node_type)
{
    switch(node_type) {
        case INTEGER_VALUE:
        return T_INTEGER;

        default:
        return T_UNKNOWN;
    }
}

static value_t* create_value_by_node_type(ast_node_t* node) {
    switch (node->type) {
        case INTEGER_VALUE:
            return new integer_value_t(*static_cast<long*>(node->value));

        default:
            return nullptr;
    }
}

static int plus(std::stack<value_t *> &stack) {
    value_t *first_value = stack.top();
    stack.pop();
    if (!first_value || !first_value->content() || first_value->type() != T_INTEGER) {
        return -1;
    }
    long int first_argument = *static_cast<long*>(first_value->content());
    value_t *second_value = stack.top();
    stack.pop();
    if (!second_value || !second_value->content() || second_value->type() != T_INTEGER) {
        return -1;
    }
    long int second_argument = *static_cast<long*>(second_value->content());
    integer_value_t *return_value = new integer_value_t(first_argument + second_argument);
    stack.push(return_value);
    return 0;
}

static int print(std::stack<value_t *> &stack) {
    value_t *value = NULL;
    value = stack.top();
    stack.pop();
    if (!value) {
        return -1;
    }
    value->print();
    return 0;
}

interpreter_t::interpreter_t() {
    setup_standard_library();
}

void interpreter_t::setup_standard_library() {
    function_t *plus_fn = (function_t *) malloc(sizeof(function_t));
    plus_fn->name = "+";
    plus_fn->arguments_number = 2;
    plus_fn->argument_types = (type_t *) calloc(plus_fn->arguments_number, sizeof(type_t));
    plus_fn->argument_types[0] = T_INTEGER;
    plus_fn->argument_types[1] = T_INTEGER;
    plus_fn->call = &plus;
    functions_table[plus_fn->name] = plus_fn;

    function_t *print_fn = (function_t *) malloc(sizeof(function_t));
    print_fn->name = "print";
    print_fn->arguments_number = 1;
    print_fn->argument_types = (type_t *) calloc(print_fn->arguments_number, sizeof(type_t));
    print_fn->argument_types[0] = T_ANY;
    print_fn->call = &print;
    functions_table[print_fn->name] = print_fn;

}

int interpreter_t::process_function_call_node(ast_node_t *node) {
    function_t *function = functions_table[node->token->value];
    if (function == NULL) {
        return -1;
    }
    value_t *argument = NULL;
    ast_node_t *argument_node = node->first_child;
    size_t argument_number = 0;
    while (argument_node) {
        if (argument_node->type == FUNCTION_CALL) {
            process_function_call_node(argument_node);
            argument_number++;
            argument_node = argument_node->next_sibling;
        } else if (
                function->argument_types[argument_number] == T_ANY ||
                get_type_by_node_type(argument_node->type) == function->argument_types[argument_number]
                ) {
            argument = create_value_by_node_type(argument_node);
            stack.push(argument);
            argument_number++;
            argument_node = argument_node->next_sibling;
        } else {
            puts("OMG Panic!");
            return -1;
        }
    }
    if (argument_number < function->arguments_number - 1) {
        size_t i;
        for (i = 0; i < argument_number; i++) {
            argument = stack.top();
            stack.pop();
        }
        return -1;
    }
    int return_code = function->call(stack);
    if (return_code != 0) {
        puts("OMG Panic!");
        exit(-1);
    }
    return 0;
}

int interpreter_t::process_ast_node(ast_node_t *root) {
    ast_node_t *node = NULL;
    switch (root->type) {
        case PROGRAM:
            node = root->first_child;
            while (node) {
                process_ast_node(node);
                node = node->next_sibling;
            }
            return 0;

        case FUNCTION_CALL:
            return process_function_call_node(root);

        default:
            printf("Unknown node type: %d\n", node->type);
            return -1;
    }
}
