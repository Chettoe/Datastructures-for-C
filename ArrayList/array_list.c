#include "array_list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void _check_memory(const void* p);
void _check_capacity(ArrayList* al);
void* _get_copy_of(const void* value, const size_t data_size);
void** _array_list_resize(const ArrayList* al, const double factor);


void array_list_init(ArrayList* al, bool is_owner, size_t data_size){
    al->array = calloc(8, sizeof(void*));
    al->size = 0;
    al->capacity = 8;
    al->data_size = data_size;
    al->is_owner = is_owner;
}

void array_list_destroy(ArrayList* al){
    if(al->is_owner == false) return;
    for(size_t i = 0; i < al->size; ++i){
        free(al->array[i]);
    }
    free(al->array);
    al->array = NULL;
    al->is_owner = false;
    al->size = 0;
    al->capacity = 0;
}

ArrayList* create_array_list(size_t data_size){
    ArrayList* al = malloc(sizeof(ArrayList));
    array_list_init(al, true, data_size);
    return al;
}

void array_list_push_back(ArrayList* al, void* value){
    _check_capacity(al);

    void* copy = _get_copy_of(value, al->data_size);
    al->array[al->size] = copy;
    al->size++;
}

void array_list_push_front(ArrayList* al, void* value){
    _check_capacity(al);
    if(al->size != 0){
        for(size_t i = al->size -1; i > 0; --i){
            al->array[i+1] = al->array[i];
        }
        //da size_t nicht negativ werden kann muss, falls an index 0 etwas steht, das separat hier verschoben werden
        if(al->size > 0){
            al->array[1] = al->array[0];
        }
    }
    void* copy = _get_copy_of(value, al->data_size);
    al->array[0] = copy;
    al->size++;
}

void array_list_insert(ArrayList* al, void* value, size_t index){
    if(index > al->size) return;
    _check_capacity(al);
    if(al->size != 0){
        for(size_t i = al->size -1; i > index; --i){
            al->array[i+1] = al->array[i];
        }
        //weil letzter index übersprungen wird
        al->array[index+1] = al->array[index];
    }

    void* copy = _get_copy_of(value, al->data_size);
    al->array[index] = copy;
    al->size++;
}

void* array_list_get(ArrayList* al, size_t index){
    if(index >= al->size) return NULL;
    void* copy = malloc(al->data_size);
    memcpy(copy, al->array[index], al->data_size);
    return copy;
}

void array_list_remove(ArrayList* al, size_t index){
    if(index >= al->size) return;
    free(al->array[index]);
    for(size_t i = index; i < al->size -1; ++i){
        al->array[i] = al->array[i+1];
    }
    al->size--;
    _check_capacity(al);
}

size_t array_list_find(ArrayList* al, void* value){
    for(size_t i = 0; i < al->size; ++i){
        if(memcmp(value, al->array[i], al->data_size) == 0){
            return i;
        }
    }
    return (size_t) -1;
}

ArrayList* array_list_deep_copy(ArrayList* al){
    ArrayList* copy = malloc(sizeof(ArrayList));
    _check_memory(copy);
    copy->size = al->size;
    copy->capacity = al->capacity;
    copy->is_owner = true;
    copy->data_size = al->data_size;

    copy->array = calloc(copy->data_size, copy->capacity);
    _check_memory(copy->array);
    for(size_t i = 0; i < al->size; ++i){
        copy->array[i] = _get_copy_of(al->array[i], al->data_size);
    }
    return copy;
}

void _check_memory(const void* p){
    if(p == NULL){
        printf("Memory error!\n");
        assert(p != NULL);
    }
}

void* _get_copy_of(const void* value, const size_t data_size){
    void* copy = malloc(data_size);
    _check_memory(copy);
    memcpy(copy, value, data_size);
    return copy;
}

void** _array_list_resize(const ArrayList* al, const double factor){
    size_t new_size = al->capacity * factor;
    void** x = realloc(al->array,  sizeof(void*) * new_size);
    _check_memory(x);
    return x;
}

void _check_capacity(ArrayList* al){
    if(al->size == al->capacity){
        al->array = _array_list_resize(al, 2.0);
        al->capacity = al->capacity * 2;
    }
    else if((al->size * 4 <= al->capacity) && al->capacity > 8){
        al->array = _array_list_resize(al, 0.5);
        al->capacity = al->capacity / 2;
    }
}