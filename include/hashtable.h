#ifndef __HASHTABLE_H
#define __HASHTABLE_H 1

#include <stdlib.h>

typedef struct hashtable_item {
	char* key;
	void* value;
	struct hashtable_item* next;
} hashtable_item_t;

typedef struct hashtable {
	unsigned int buckets_number;
	hashtable_item_t **buckets;
} hashtable_t;

hashtable_t* create_hashtable(unsigned int buckets_number);

int put_to_hashtable(hashtable_t* hashtable, char* key, void* value, size_t value_size);

void* get_from_hashtable(hashtable_t* hashtable, char* key);

#endif
