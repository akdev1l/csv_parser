#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"

#define DELIM ","
#define MAX_LINE 301
#define MAX_ENTRIES 100



void strip_newline(char* str)
{
    if(str[strlen(str)-1] == '\n') {
        str[strlen(str)-1] = '\0';
    }
}
void clear_buffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int count_keys(const char* line, const char* delimiter)
{
    char* cpy_line = malloc(strlen(line)+1);
    strcpy(cpy_line, line);
    char* key = strtok(cpy_line, delimiter);
    int key_count = key?1:0;
    while(key) {
        key = strtok(NULL, delimiter);
        ++key_count;
    }
    free(cpy_line);
    return key_count;
} 

void get_keys(char** keys, int* count_keys, char* line, const char* delimiter)
{
    char* key = strtok(line, delimiter);
    while(key) {
        keys[*count_keys] = malloc(strlen(key)+1);
        strcpy(keys[*count_keys], key);
        ++*count_keys;
        key = strtok(NULL, delimiter);
    }
}

void get_fields(hashmap** entry, char** keys, int count_keys, char* line, const char* delimiter)
{
    char* field = strtok(line, delimiter);
    for(int i = 0; i < count_keys; ++i) {
        if(i == 0 && field) {
            *entry = create_hashmap(keys[i], create_value(field));
        }
        else if(field) {
            set_value(*entry, keys[i], create_value(field));
        }
        field = strtok(NULL, delimiter);
    }
}

void readline(FILE* file, char* line, int max_length)
{
    fgets(line, max_length, file);
    strip_newline(line);
}

void get_filename(char* out, int length)
{
    printf("Enter filename: ");
    readline(stdin, out, length);
}

void free_entries(hashmap** entries, int num_entries)
{
    for(int i = 0; i < num_entries; ++i) {
        destroy_hashmap(entries[i]);
    }
}
void print_entries(hashmap** entries, int num_entries, char** keys, int num_keys)
{
    for(int i = 0; i < num_entries; ++i) {
        for(int j = 0; j < num_keys; ++j) {
            printf("%s: %s\t", keys[j], get_value(entries[i], keys[j]).data);
        }
        printf("\n");
    }
}

int main(void)
{
    char filename[31] = {0};
    hashmap* entries[MAX_ENTRIES] = {NULL};
    int entry_pos = 0;
    int num_entries = 0;
    char** keys = NULL;
    int key_count = 0;
    char line[MAX_LINE] = {0};
    FILE* csv_file = NULL;
    
    get_filename(filename, 31);
    csv_file = fopen(filename, "r");

    if(csv_file && !feof(csv_file)) {
        readline(csv_file, line, MAX_LINE);
        keys = malloc(count_keys(line, DELIM) * sizeof(char*));
        get_keys(keys, &key_count, line, DELIM);
        while(!feof(csv_file)) {
            readline(csv_file, line, MAX_LINE);
            get_fields(&entries[entry_pos], keys, key_count, line, DELIM);
            ++entry_pos;
            if(entry_pos >= MAX_ENTRIES - 1) {
                print_entries(entries, entry_pos, keys, key_count);
                free_entries(entries, entry_pos);
                entry_pos = 0;
            }
            ++num_entries;
        }
        printf("Keys in csv file: %d\n", key_count);
        printf("Entries in csv file: %d\n", num_entries);
        print_entries(entries, entry_pos, keys, key_count);
        for(int i = 0; i < key_count; ++i) {
            free(keys[i]);
        }
        fclose(csv_file);
    }
    free(keys);
    return 0;
}
