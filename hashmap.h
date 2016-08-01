#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct hashmap
{
    struct hashmap* next;
    char* key;
    char* value;
} hashmap;

hashmap* create_hashmap(const char* key, const char* value);

const char* get_value(hashmap* container, const char* key);

void set_value(hashmap* container, const char* key, const char* value);

int key_exists(hashmap* container, const char* key);

void destroy_hashmap(hashmap* container);

#endif
