#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"

#define DELIM ","
#define MAX_LINE 301
#define MAX_ENTRIES 100



void strip_newline(char* str)
{
    int len = strlen(str);
    if(str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int count_keys(const char* line, const char* delimiter)
{
    // Count all the keys in the csv file //
    char* cpy_line = malloc(strlen(line)+1);
    strcpy(cpy_line, line);
    char* key = strtok(cpy_line, delimiter);
    int key_count = 0; //if key was found then key_count = 1
    while(key) {
        key = strtok(NULL, delimiter);
        ++key_count;
    }
    free(cpy_line);
    return key_count;
} 

void get_keys(char** keys, char* line, const char* delimiter)
{
    // Retrieves all keys in one line delimited by delimiter //
    char* key = strtok(line, delimiter);
    int count_keys = 0;
    while(key) {
        keys[count_keys] = malloc(strlen(key)+1);
        strcpy(keys[count_keys], key);
        ++count_keys;
        key = strtok(NULL, delimiter);
    }
}

void get_fields(hashmap** entry, char** keys, int count_keys, char* line, const char* delimiter)
{
    // Retrieves field by field assigning into hashmap['key'] //
    char* field = strtok(line, delimiter);
    for(int i = 0; i < count_keys; ++i) {
        if(i == 0 && field) {
            *entry = create_hashmap(keys[i], field);
        }
        else if(field) {
            set_value(*entry, keys[i], field);
        }
        field = strtok(NULL, delimiter);
    }
}

char* readline(FILE* file, char* line, int max_length)
{
    char* return_val = fgets(line, max_length, file);
    strip_newline(line);
    return return_val;
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
            printf("%s: %s\t", keys[j], get_value(entries[i], keys[j]));
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    char filename[MAX_LINE] = {0};
    hashmap* entries[MAX_ENTRIES] = {NULL};
    int entry_pos = 0;
    int num_entries = 0;
    char** keys = NULL;
    int key_count = 0;
    char line[MAX_LINE] = {0};
    FILE* csv_file = NULL;
    
    if(argc <= 1) {
        get_filename(filename, MAX_LINE);
    }
    else {
        strcpy(filename, argv[1]);
    }
    csv_file = fopen(filename, "r");

    if(csv_file && !feof(csv_file)) {
        readline(csv_file, line, MAX_LINE);
        key_count = count_keys(line, DELIM);
        keys = malloc(key_count * sizeof(char*));
        get_keys(keys, line, DELIM);
        while(readline(csv_file, line, MAX_LINE) && !feof(csv_file)) {
            get_fields(&entries[entry_pos], keys, key_count, line, DELIM);
            ++entry_pos;
            if(entry_pos >= MAX_ENTRIES) {
                print_entries(entries, entry_pos, keys, key_count);
                free_entries(entries, entry_pos);
                entry_pos = 0;
            }
            ++num_entries;
        }
        print_entries(entries, entry_pos, keys, key_count);
        fprintf(stderr, "Keys in csv file: %d\n", key_count);
        fprintf(stderr, "Entries in csv file: %d\n", num_entries);
        free_entries(entries, entry_pos);
        for(int i = 0; i < key_count; ++i) {
            free(keys[i]);
        }
        fclose(csv_file);
    }
    free(keys);
    return 0;
}
