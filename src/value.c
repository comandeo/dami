#include <stdlib.h>
#include <stdio.h>
#include "value.h"

value_t* create_value(type_t type)
{
	integer_value_t* integer_value = NULL;
	string_value_t* string_value = NULL;
	switch (type) {
		case T_INTEGER:
		integer_value = (integer_value_t*)malloc(sizeof(integer_value_t));
		integer_value->type = T_INTEGER;
		integer_value->content = 0L;
		return (void*)integer_value;

		case T_STRING:
		string_value = (string_value_t*)malloc(sizeof(string_value_t));
		string_value->type = T_STRING;
		string_value->content = NULL;
		string_value->length = 0;
		return (void*)string_value;

		default:
		return NULL;
	}
}

void release_value(value_t* value)
{
	if (!value) {
		return;
	}
	string_value_t* string_value;
	switch (value->type) {
		case T_INTEGER:
		free((integer_value_t*)value);
		break;

		case T_STRING:
		string_value = (string_value_t*)value;
		if (string_value->content) {
			free(string_value->content);
		}
		free(string_value);
		break;

		case T_UNKNOWN:
		break;
	}
}

void print_value(value_t* value)
{
	if (!value) {
		return;
	}
	switch (value->type) {
		case T_INTEGER:
		printf("%ld\n", *(long int*)value->content);
		break;

		case T_STRING:
		printf("%s\n", (char*)value->content);
		break;

		case T_UNKNOWN:
		break;
	}
}
