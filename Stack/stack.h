#ifndef STACK_H
#define STACK_H

#include "linked_list.h"
#include <stdbool.h>

#define INT sizeof(int)
#define LONG sizeof(long)
#define FLOAT sizeof(float)
#define DOUBLE sizeof(double)
#define CHAR sizeof(char)
//add custom

typedef struct Stack{
    LinkedList* list;
    Node* tos;
    size_t size;
    bool is_owner;
    size_t data_size;
}Stack;

void stack_init(Stack* s, bool is_owner, size_t data_size);
Stack* create_stack(size_t data_size);
void stack_destroy(Stack* s);
Stack* stack_deep_copy(Stack* s);
void stack_push(Stack* s, void* value);
void stack_pop(Stack* s);
void* stack_peek(Stack* s);


#endif