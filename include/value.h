#ifndef __VALUE_H
#define __VALUE_H 1

#include <string>

typedef enum type {
	T_INTEGER = 1,
	T_STRING,
	T_ANY,
	T_UNKNOWN
} type_t;

class value_t {
public:
    virtual ~value_t() {}
    virtual void* content() = 0;
    virtual type_t type() = 0;
    virtual void print() = 0;
};

class integer_value_t : public virtual value_t {
public:
    integer_value_t(long val);
    virtual ~integer_value_t();
    virtual void* content();
    virtual type_t type();
    virtual void print();
private:
    long value_;
};

class string_value_t : public virtual value_t {
public:
    string_value_t(std::string& val);
    virtual ~string_value_t();
    virtual void* content();
    virtual type_t type();
    virtual void print();
private:
    std::string value_;
};

#endif
