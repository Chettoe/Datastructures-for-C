#include "linked_list.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void _check_memory(const void *p);
void* _get_copy_of(void* value, size_t data_size);

void _check_memory(const void* p){
    if(p == NULL){
        printf("Memory Error\n");
        assert(p != NULL);
    }
}

void* _get_copy_of(void* value, size_t data_size){
    if(value == NULL) return NULL;
    void* copy = malloc(data_size);
    _check_memory(copy);

    memcpy(copy, value, data_size);
    return copy;
}

void linked_list_init(LinkedList* list, const bool is_owner, size_t data_size){
    list->head = list_node_create(list, NULL);
    list->tail = list_node_create(list, NULL);
    list->head->next = list->tail;
    list->tail->prev = list->head;

    list->size = 0;
    list->is_owner = is_owner;
    list->data_size = data_size;
}

LinkedList* create_linked_list(size_t data_size){
    LinkedList* list = malloc(sizeof(LinkedList));
    _check_memory(list);
    linked_list_init(list, true, data_size);
    return list;
}

void linked_list_destroy(LinkedList* list){
    if(list->is_owner == false){
        return;
    }
    while(list->size != 0){
        Node* e = linked_list_unlink_node(list, list->head->next);
        list_node_destroy(e);
    }
    list->is_owner = false;
    list->size = 0;
    free(list->head);
    free(list->tail);
    list->head = NULL;
    list->tail = NULL;
}

void list_node_destroy(Node* node){
    free(node->value);
    free(node);
    node = NULL;
}

Node* list_node_create(LinkedList* list, void* value){
    Node* n = malloc(sizeof(Node));
    _check_memory(n);
    n->value = _get_copy_of(value, list->data_size);
    n->next = NULL;
    n->prev = NULL;
    return n;
}

LinkedList* linked_list_flat_copy(const LinkedList* list){
    LinkedList* copy = malloc(sizeof(LinkedList));
    _check_memory(copy);
    copy->head = list->head;
    copy->tail = list->tail;
    copy->is_owner = false;
    copy->size = list->size;
    return copy;
}

LinkedList* linked_list_deep_copy(const LinkedList* list){
    LinkedList* copy = malloc(sizeof(LinkedList));
    _check_memory(copy);
    linked_list_init(copy, true, list->data_size);
    Node* current = list->head->next;
    while(current != list->tail){
        linked_list_push_back(copy, current->value);
        current = current->next;
    }
    return copy;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void linked_list_insert(LinkedList* list, Node* prev, Node* e){
    Node* copy = list_node_create(list, e->value);
    Node* next = prev->next;
    copy->prev = prev;
    copy->next = next;
    prev->next = copy;
    next->prev = copy;
    list->size++;
}
void linked_list_push_back(LinkedList* list, void* value){
    Node* n = list_node_create(list, value);
    Node* tail = list->tail;
    Node* prev = list->tail->prev;
    n->next = tail;
    n->prev = prev;
    prev->next = n;
    tail->prev = n;
    list->size++;
}
void linked_list_push_front(LinkedList* list, void* value){
    Node* n = list_node_create(list, value);
    n->prev = list->head;
    n->next = list->head->next;
    list->head->next->prev = n;
    list->head->next = n;
    list->size++;
}

void linked_list_delete_index(LinkedList* list, const size_t index){
    Node* n = linked_list_get_index(list, index);
    Node* d = linked_list_unlink_node(list, n);
    list_node_destroy(d);
}

Node* linked_list_get_index(const LinkedList* list, const size_t index){
    assert(index < list->size);
    Node* current = list->head->next;
    for(size_t i = 0; i < index; i++){
        current = current->next;
    }
    return current;
}

void* linked_list_unlink_node(LinkedList* list, Node* e){
    assert(e != list->head);
    assert(e != list->tail);
    e->prev->next = e->next;
    e->next->prev = e->prev;
    e->next = NULL;
    e->prev = NULL;
    list->size--;
    return e;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void linked_list_int_print(const LinkedList* l){
    Node* node = l->head->next;
    for(size_t i = 0; i < l->size; i++){
        int* value = node->value;
        printf("%d ", *value);
        node = node->next;
    }
    printf("\n");
}

void linked_list_long_print(const LinkedList* l){
    Node* node = l->head->next;
    for(size_t i = 0; i < l->size; i++){
        long* value = node->value;
        printf("%lu ", *value);
        node = node->next;
    }
    printf("\n");
}

void linked_list_float_print(const LinkedList* l){
    Node* node = l->head->next;
    for(size_t i = 0; i < l->size; i++){
        float* value = node->value;
        printf("%f ", *value);
        node = node->next;
    }
    printf("\n");
}

void linked_list_double_print(const LinkedList* l){
    Node* node = l->head->next;
    for(size_t i = 0; i < l->size; i++){
        double* value = node->value;
        printf("%lf ", *value);
        node = node->next;
    }
    printf("\n");
}

void linked_list_char_print(const LinkedList* l){
    Node* node = l->head->next;
    for(size_t i = 0; i < l->size; i++){
        char* value = node->value;
        printf("%c ", *value);
        node = node->next;
    }
    printf("\n");
}



