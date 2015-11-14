#ifndef __VALUE_H
#define __VALUE_H 1

typedef enum type {
	T_INTEGER = 1,
	T_STRING,
	T_UNKNOWN
} type_t;

typedef struct integer_value {
	type_t type;
	long int content;
} integer_value_t;

typedef struct string_value {
	type_t type;
	char* content;
	int length;
} string_value_t;

typedef struct value {
	type_t type;
	void* content;
} value_t;

value_t* create_value(type_t type);

void release_value(value_t* value);

#endif
