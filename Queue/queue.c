#include "queue.h"
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _check_memory_queue(const void* p);

void _check_memory_queue(const void* p){
    if(p == NULL){
        printf("Memory error!\n");
    }
}

void queue_init(Queue* q, bool is_owner, size_t data_size){
    q->list = create_linked_list(data_size);
    q->front = q->list->head->next;
    q->back = q->list->tail->prev;
    q->is_owner = is_owner;
    q->data_size = data_size; 
    q->size = 0;
}
Queue* create_queue(size_t data_size){
    Queue* q = malloc(sizeof(Queue));
    _check_memory_queue(q);
    queue_init(q, true, data_size);
    return q;                                                                        
}
void destroy_queue(Queue* q){
    if(q->is_owner == false) return;
    linked_list_destroy(q->list);
    free(q->list);
    q->list = NULL;
    q->front = NULL;
    q->back = NULL;
    q->is_owner = false;
    q->size = 0;
}
void queue_pop(Queue* q){
    if(q->size == 0) return;
    linked_list_delete_index(q->list, 0);
    q->front = q->list->head->next;
    q->size--;
}
void queue_push(Queue* q, void* value){
    linked_list_push_back(q->list, value);
    q->front = q->list->head->next;
    q->back = q->list->tail->prev;
    q->size++;
}
void* queue_peek(Queue* q){
    if(q->size == 0) return NULL;
    void* copy = malloc(sizeof(q->data_size));
    _check_memory_queue(copy);
    memcpy(copy, q->front->value, q->data_size);
    return copy;
}
Queue* queue_deep_copy(Queue* q){
    Queue* copy = malloc(sizeof(Queue));
    _check_memory_queue(copy);
    copy->list = linked_list_deep_copy(q->list);
    copy->front = copy->list->head->next;
    copy->back = copy->list->tail->prev;
    copy->data_size = q->data_size;
    copy->size = q->size;
    copy->is_owner = true;
    return copy;
}