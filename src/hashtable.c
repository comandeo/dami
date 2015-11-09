#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashtable.h"

static unsigned long hash(char *str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++)) {
    	hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

hashtable_t* create_hashtable(unsigned int buckets_number)
{
	hashtable_t* hashtable = malloc(sizeof(hashtable_t));
	hashtable->buckets_number = buckets_number;
	hashtable->buckets = calloc(buckets_number, sizeof(hashtable_item_t*));
	return hashtable;
}

int put_to_hashtable(hashtable_t* hashtable, char* key, void* value, size_t value_size)
{
	hashtable_item_t* hashtable_item = malloc(sizeof(hashtable_item_t));
	hashtable_item->key = (char*)malloc(strlen(key) + 1);
	strcpy(hashtable_item->key, key);
	hashtable_item->value = malloc(value_size);
	memcpy(hashtable_item->value, value, value_size);
	unsigned int bucket_number = hash(key) % hashtable->buckets_number;
	hashtable_item_t* bucket = hashtable->buckets[bucket_number];
	if (bucket == NULL) {
		hashtable->buckets[bucket_number] = hashtable_item;
		return 0;
	}
	while (bucket->next != NULL) {
		bucket = bucket->next;
	}
	bucket->next = hashtable_item;
	return 0;
}

void* get_from_hashtable(hashtable_t* hashtable, char* key)
{
	unsigned int bucket_number = hash(key) % hashtable->buckets_number;
	hashtable_item_t* item = hashtable->buckets[bucket_number];
	if (item == NULL) {
		return NULL;
	}
	while (item) {
		if (strcmp(key, item->key) == 0) {
			return item->value;
		}
		item = item->next;
	}
	return NULL;
}
