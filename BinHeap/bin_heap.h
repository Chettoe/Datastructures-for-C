#ifndef BIN_HEAP_H
#define BIN_HEAP_H

#include "array_list.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct BinHeapElement{
    size_t key;
    void* data;
    size_t pos;
}BinHeapElement;

typedef struct BinHeap{
    size_t size;
    size_t capacity;
    ArrayList* arr;

    bool is_owner;
    size_t data_size;
}BinHeap;

BinHeapElement* create_bin_heap_element(size_t key, void* data, size_t data_size);
void bin_heap_element_destroy(BinHeapElement* e);


BinHeap* make_bin_heap(size_t* arr, size_t n);
BinHeap* create_bin_heap(size_t data_size);

void bin_heap_init(BinHeap* bh, bool is_owner, size_t data_size);
void bin_heap_destroy(BinHeap* bh);

void bin_heap_insert(BinHeap* bh, size_t key, void* e);
void bin_heap_extract_max(BinHeap* bh);
BinHeapElement** bin_heap_sort(BinHeap* bh);

void bin_heap_increase_key(BinHeap* bh, size_t key, size_t new_key);
void bin_heap_decrease_key(BinHeap* bh, size_t key, size_t new_key);

#endif