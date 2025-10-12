#include "hash_map.h"
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HMElement* _hm_element_link(HMElement* prev, HMElement* e);
HMElement* _hm_element_unlink(HMElement* e);

HashFunction _random_hash_function();

void* _copy_of(void* value, size_t data_size);
void _check_memory(void* p);

size_t _get_hash(const HashFunction* hf, size_t key);
void _resize(HashMap* hm, double factor);
bool _hash_map_exists(HashMap* hm, size_t key);

size_t _probe_offset(size_t key, size_t try);

///////////////////////////////////////////////////////////////////////////////////////////////////////

HMElement* create_hm_element(size_t key, void* element, size_t data_size){
    HMElement* hm_element = malloc(sizeof(HMElement));
    _check_memory(hm_element);
    hm_element->key = key;
    hm_element->element = _copy_of(element, data_size);
    hm_element->next = NULL;
    hm_element->prev = NULL;
    return hm_element;
}

void hm_element_destroy(HMElement* hm_element){
    free(hm_element->element);
}

void hash_map_init(HashMap* hm, size_t data_size, bool is_owner){
    hm->table = malloc(sizeof(HMElement*) * 8);
    _check_memory(hm->table);
    hm->capacity = 8;
    hm->size = 0;
    hm->is_owner = is_owner;
    hm->data_size = data_size;

    hm->n_insert_fails = 0;
    hm->n_probing_steps = 0;
    hm->n_resizes = 0;

    hm->hash_function = _random_hash_function();
    hm->max_load_factor = 0.75;
    hm->min_load_factor = 0.25;

    hm->head = create_hm_element((size_t) -1, NULL, 0); // was passiert bei malloc(0)???
    hm->tail = create_hm_element((size_t) -1, NULL, 0);
    hm->DELETED = create_hm_element((size_t) -1, NULL, 0);
    
    hm->head->next = hm->tail;
    hm->head->prev = NULL;

    hm->tail->prev = hm->head;
    hm->tail->next = NULL;
}

HashMap* create_hash_map(size_t data_size){
    HashMap* hm = malloc(sizeof(HashMap));
    _check_memory(hm);
    hash_map_init(hm, data_size, true);
    return hm;
}

void hash_map_destroy(HashMap* hm){
    if(hm->is_owner == false) return;
    HMElement* current = hm->head->next;
    HMElement* delete = current;
    while(current != hm->tail){
        delete = current;
        current = current->next;
        hm_element_destroy(delete);
        free(delete);
    }
    free(hm->table);
    hm_element_destroy(hm->head);
    hm_element_destroy(hm->tail);
    hm_element_destroy(hm->DELETED); //??? noch gucken wie das implementiert ist
}

void hash_map_insert(HashMap* hm, size_t key, void* element);
void* hash_map_find(HashMap* hm, size_t key);
void hash_map_delete(HashMap* hm, size_t key);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

HMElement* _hm_element_link(HMElement* prev, HMElement* e){
    prev->next->prev = e;
    e->next = prev->next;
    prev->next = e;
    e->prev = prev;
    return e;
}

HMElement* _hm_element_unlink(HMElement* e){
    e->prev->next = e->next;
    e->next->prev = e->prev;
    e->next = NULL;
    e->prev = NULL;
    return e;
}

HashFunction _random_hash_function(){
    const int a = (rand() % (INT_MAX -1)) +1;
    const int b = rand();
    HashFunction hf;
    hf.a = a;
    hf.b = b;
    return hf;
}

void* _copy_of(void* value, size_t data_size){
    void* copy = malloc(data_size);
    _check_memory(copy);
    memcpy(copy, value, data_size);
    return copy;
}

void _check_memory(void* p){
    if(p == NULL){
        printf("Memory error!\n");
        assert(p != NULL);
    }
}

//achtung vor overflow
size_t _get_hash(const HashFunction* hf, size_t key){
    //return hf->a * key + hf->b % INT_MAX;       also size_t zurück geben aber hf->a und hf->b sind int
    return hf->a * key + hf->b % ((size_t) -1);
}

void _resize(HashMap* hm, double factor);
bool _hash_map_exists(HashMap* hm, size_t key);

size_t _probe_offset(size_t key, size_t try);