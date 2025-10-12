#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define INT sizeof(int)
#define LONG sizeof(long)
#define FLOAT sizeof(float)
#define DOUBLE sizeof(double)
#define CHAR sizeof(char)
//add custom

typedef struct ArrayList{
    void** array;
    size_t data_size;
    size_t capacity;
    size_t size;
    bool is_owner;
}ArrayList;

void array_list_init(ArrayList* al, bool is_owner, size_t data_size);
void array_list_destroy(ArrayList* al);
ArrayList* create_array_list(size_t data_size);

void array_list_push_back(ArrayList* al, void* value);
void array_list_push_front(ArrayList* al, void* value);
void array_list_insert(ArrayList* al, void* value, size_t index);
void* array_list_get(ArrayList* al, size_t index);
void array_list_remove(ArrayList* al, size_t index);
size_t array_list_find(ArrayList* al, void* value);
ArrayList* array_list_deep_copy(ArrayList* al);

#endif