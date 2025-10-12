#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"
#include <stdbool.h>

#define INT sizeof(int)
#define LONG sizeof(long)
#define FLOAT sizeof(float)
#define DOUBLE sizeof(double)
#define CHAR sizeof(char)
//add custom

typedef struct Queue{
    LinkedList* list;
    Node* front;
    Node* back;
    size_t size;
    bool is_owner;
    size_t data_size;
}Queue;

void queue_init(Queue* q, bool is_owner, size_t data_size);
Queue* create_queue(size_t data_size);
void destroy_queue(Queue* q);
void queue_pop(Queue* q);
void queue_push(Queue* q, void* value);
void* queue_peek(Queue* q);
Queue* queue_deep_copy(Queue* q);

#endif