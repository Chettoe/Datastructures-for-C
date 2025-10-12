#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdlib.h> 
#include <stdbool.h>

#define INT sizeof(int)
#define LONG sizeof(long)
#define FLOAT sizeof(float)
#define DOUBLE sizeof(double)
#define CHAR sizeof(char)
//add custom

typedef struct Node Node;
typedef struct Node{
    void* value;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct LinkedList{
    Node* head;
    Node* tail;
    size_t size;
    bool is_owner;
    size_t data_size;
}LinkedList;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void linked_list_init(LinkedList* list, const bool is_owner, size_t data_size);
LinkedList* create_linked_list(size_t data_size);
void linked_list_destroy(LinkedList* list);

Node* list_node_create(LinkedList* list, void* value);
void list_node_destroy(Node* node);

LinkedList* linked_list_flat_copy(const LinkedList* list);
LinkedList* linked_list_deep_copy(const LinkedList* list);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void linked_list_delete_value(LinkedList* list, void* value);
void linked_list_delete_index(LinkedList* list, const size_t index);
Node* linked_list_get_index(const LinkedList* list, const size_t index);

void linked_list_insert(LinkedList* list, Node* prev, Node* e);
void linked_list_push_back(LinkedList* list, void* value);
void linked_list_push_front(LinkedList* list, void* value);

void* linked_list_unlink_node(LinkedList* list, Node* e);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void linked_list_int_print(const LinkedList* l);
void linked_list_long_print(const LinkedList* l);
void linked_list_float_print(const LinkedList* l);
void linked_list_double_print(const LinkedList* l);
void linked_list_char_print(const LinkedList* l);
//add custom

#endif