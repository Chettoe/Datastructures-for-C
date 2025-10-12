#include "bin_heap.h"
#include "array_list.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void _heapify_up(BinHeap* bh);
void _heapify_down(BinHeap* bh);

void _switch_element(BinHeapElement* x, BinHeapElement* y);

void _bin_heap_check_memory(void* p);
void* _bin_heap_copy_of(void* value, size_t data_size);

///////////////////////////////////////////////////////////////////////

BinHeapElement* create_bin_heap_element(size_t key, void* data, size_t data_size){
    BinHeapElement* e = malloc(sizeof(BinHeapElement));
    _bin_heap_check_memory(e);
    e->key = key;
    e->pos = (size_t)-1;
    e->data = _bin_heap_copy_of(data, data_size);
    return e;
}

void bin_heap_element_destroy(BinHeapElement* e){
    free(e->data);
    e->data = NULL;
}


BinHeap* make_bin_heap(size_t* arr, size_t n){
    BinHeap* bh = create_bin_heap(NULL); //geht vielleicht nicht wegen malloc(NULL)
    for(size_t i = 0; i < n; ++i){
        bin_heap_insert(bh, arr[i], NULL);
    }
    return bh;
}

BinHeap* create_bin_heap(size_t data_size){
    BinHeap* bh = malloc(sizeof(BinHeap));
    bin_heap_init(bh, true, data_size);
    return bh;
}

void bin_heap_init(BinHeap* bh, bool is_owner, size_t data_size){
    bh->arr = create_array_list(sizeof(BinHeapElement));
    bh->data_size = data_size;
    bh->is_owner = is_owner;
    bh->size = 0;
    bh->capacity = bh->arr->capacity;
}

void bin_heap_destroy(BinHeap* bh){
    for(size_t i = 0; i < bh->arr->size; ++i){
        free(((BinHeapElement*)bh->arr->array[i])->data);
    }
    array_list_destroy(bh->arr);
    free(bh->arr);
}

void bin_heap_insert(BinHeap* bh, size_t key, void* e){
    BinHeapElement* bhe = create_bin_heap_element(key, e, bh->data_size);
    bhe->pos = bh->arr->size;
    array_list_push_back(bh->arr, bhe);
    free(bhe);
}
void bin_heap_extract_max(BinHeap* bh);
BinHeapElement** bin_heap_sort(BinHeap* bh);

void bin_heap_increase_key(BinHeap* bh, size_t key, size_t new_key);
void bin_heap_decrease_key(BinHeap* bh, size_t key, size_t new_key);



void _heapify_up(BinHeap* bh);
void _heapify_down(BinHeap* bh);

void _switch_element(BinHeapElement* x, BinHeapElement* y){
    void* temp_data = x->data;
    size_t temp_key = x->key;
    size_t temp_pos = x->pos;

    x->data = y->data;
    x->key = y->key;
    x->pos = y->pos;

    y->data = temp_data;
    y->key = temp_key;
    y->pos = temp_pos;
}

void _bin_heap_check_memory(void* p){
    if(p == NULL){
        printf("Memory Error!\n");
        assert(p != NULL);
    }
}

void* _bin_heap_copy_of(void* value, size_t data_size){
    if(value == NULL) return NULL;
    void* copy = malloc(data_size);
    memcpy(copy, value, data_size);
    return copy;
}