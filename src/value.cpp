#include <stdlib.h>
#include <stdio.h>
#include "value.h"

integer_value_t::integer_value_t(long val) : value_(val) {}

integer_value_t::~integer_value_t() {}

void* integer_value_t::content() {
    return static_cast<void*>(&value_);
}

type_t integer_value_t::type() {
    return T_INTEGER;
}

void integer_value_t::print() {
    printf("%ld\n", value_);
}

string_value_t::string_value_t(std::string& val) : value_(val) {}

string_value_t::~string_value_t() {}

void* string_value_t::content() {
    return static_cast<void*>(&value_);
}

type_t string_value_t::type() {
    return T_STRING;
}

void string_value_t::print() {
    printf("%s\n", value_.c_str());
}

