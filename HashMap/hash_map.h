#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HMElement HMElement;

typedef struct HashFunction{
    size_t a;
    size_t b;
}HashFunction;

typedef struct HMElement{
    size_t key;
    void* element;
    HMElement* next;
    HMElement* prev;
}HMElement;

typedef struct HashMap{
    HMElement** table;
    size_t size;
    size_t capacity;
    bool is_owner;
    size_t data_size;

    size_t n_insert_fails;
    size_t n_probing_steps; //häufigkeit der sondierung 
    size_t n_resizes;

    //hier noch lineare oder quadratische sondierung hinzufügen, mit macros sodass man diese übergeben kann
    HashFunction hash_function;
    double max_load_factor; // 3/4
    double min_load_factor; // 1/4

    HMElement* head;
    HMElement* tail;
    HMElement* DELETED;
}HashMap;

void hash_function_init(HashFunction* hf);
void hash_function_destroy(HashFunction* hf);

HMElement* create_hm_element(size_t key, void* element, size_t data_size);
void hm_element_destroy(HMElement* hm_element);


void hash_map_init(HashMap* hm, size_t data_size, bool is_owner);
HashMap* create_hash_map(size_t data_size);
void hash_map_destroy(HashMap* hm);

void hash_map_insert(HashMap* hm, size_t key, void* element);
void* hash_map_find(HashMap* hm, size_t key);
void hash_map_delete(HashMap* hm, size_t key);


#endif