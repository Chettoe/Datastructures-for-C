#include "stack.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void _check_memory_stack(const void* p);

void _check_memory_stack(const void* p){
    if(p == NULL){
        printf("Memory error!\n");
        assert(p != NULL);
    }
}

void stack_init(Stack* s, bool is_owner, size_t data_size){
    s->list = create_linked_list(data_size);
    s->tos = NULL;
    s->is_owner = is_owner;
    s->data_size = data_size;
    s->size = 0;
}
Stack* create_stack(size_t data_size){
    Stack* s = malloc(sizeof(Stack));
    stack_init(s, true, data_size);
    return s;
}
void stack_destroy(Stack* s){
    if(s->is_owner == false) return;
    linked_list_destroy(s->list);
    free(s->list);
    s->list = NULL;
    s->tos = NULL;
    s->size = 0;
    s->is_owner = false;
}
Stack* stack_deep_copy(Stack* s){
    Stack* copy = create_stack(s->data_size);
    copy->list = linked_list_deep_copy(s->list);
    copy->size = s->size;
    copy->is_owner = true;
    copy->tos = copy->list->head->next;
    return copy;
}
void stack_push(Stack* s, void* value){
    linked_list_push_front(s->list, value);
    s->tos = s->list->head->next;
    s->size++;
}
void stack_pop(Stack* s){
    if(s->size == 0) return;
    linked_list_delete_index(s->list, 0);
    s->tos = s->list->head->next;
    s->size--;
}
void* stack_peek(Stack* s){
    if(s->size == 0) return NULL;
    void* value = malloc(s->data_size);
    _check_memory_stack(value);
    memcpy(value, s->tos->value, s->data_size);
    return value;
}