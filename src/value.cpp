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
