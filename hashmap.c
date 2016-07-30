#include "hashmap.h"

value_t create_value(const char* data)
{
    value_t tmp;
    tmp.data = malloc(strlen(data)+1);
    strcpy(tmp.data, data);
    return tmp;
}

void destroy_value(value_t* value)
{
    free(value->data);
}

int equal(const value_t v1, const value_t v2)
{
    return strcmp(v1.data, v2.data) == 0;
}

hashmap* create_hashmap(const char* key, value_t value)
{
    hashmap* tmp = malloc(sizeof(hashmap));
    tmp->value = value;
    tmp->key = malloc(strlen(key)+1);
    strcpy(tmp->key, key);
    tmp->next = NULL;
    return tmp;
}

value_t get_value(hashmap* container, const char* key)
{
    if(container) {
        if(strcmp(key, container->key) == 0) {
            return container->value;
        }
        else {
            return get_value(container->next, key);
        }
    }
    return NULL_VALUE;
}
int key_exists(hashmap* container, const char* key)
{
    if(container) {
        if(strcmp(container->key, key) == 0) {
            return 1;
        }
        else {
            return key_exists(container->next, key);
        }
    }
    return 0;
}
void set_value(hashmap* container, const char* key, value_t value)
{
    hashmap* current = container;
    hashmap* previous = NULL;
    while(current && strcmp(current->key, key) != 0) {
        previous = current;
        current = current->next;
    }
    if(current) {
        destroy_value(&current->value);
        current->value = value;
    }
    else {
        previous->next = create_hashmap(key, value);
    }
}

void destroy_hashmap(hashmap* container)
{
    if(container) {
        destroy_value(&container->value);
        destroy_hashmap(container->next);
        free(container->key);
        free(container);
    }
}