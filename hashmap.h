#include <stdlib.h>
#include <string.h>

typedef struct value_t
{
    char* data;
} value_t;

value_t create_value(const char* data);

void destroy_value(value_t* value);

int equal(const value_t v1, const value_t v2);

static const value_t NULL_VALUE = { .data = NULL };

typedef struct hashmap
{
    struct hashmap* next;
    char* key;
    value_t value;
} hashmap;

hashmap* create_hashmap(const char* key, value_t value);

value_t get_value(hashmap* container, const char* key);

void set_value(hashmap* container, const char* key, value_t value);

int key_exists(hashmap* container, const char* key);

void destroy_hashmap(hashmap* container);