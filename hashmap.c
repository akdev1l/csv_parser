#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hashmap.h"

hashmap* create_hashmap(const char* key, const char* value)
{
    hashmap* tmp = malloc(sizeof(hashmap));
    tmp->value = malloc(strlen(value)+1);
    assert(tmp->value != NULL);
    strcpy(tmp->value, value);
    tmp->key = malloc(strlen(key)+1);
    assert(tmp->key != NULL);
    strcpy(tmp->key, key);
    tmp->next = NULL;
    return tmp;
}

const char* get_value(hashmap* container, const char* key)
{
    if(container) {
        hashmap* current = container;
        while(current) {
            if(strcmp(key, current->key) == 0) {
                return current->value;
            }
            current = current->next;
        }
    }
    return NULL;
}
int key_exists(hashmap* container, const char* key)
{
    if(container) {
        hashmap* current = container;
        while(current) {
            if(strcmp(key, current->key) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
void set_value(hashmap* container, const char* key, const char* value)
{
    hashmap* current = container;
    hashmap* previous = NULL;
    while(current && strcmp(current->key, key) != 0) {
        previous = current;
        current = current->next;
    }
    if(current) {
        free(current->value);
        current->value = malloc(strlen(value)+1);
        assert(current->value != NULL);
        strcpy(current->value, value);
    }
    else {
        previous->next = create_hashmap(key, value);
    }
}

void destroy_hashmap(hashmap* container)
{
    if(container) {
        free(container->key);
        free(container->value);
        destroy_hashmap(container->next);
        free(container);
    }
}
