#include "test_stack.h"
#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Stack* create_stack_stub(void){
    Stack* s = create_stack(INT);
    int a = 10; int b = 20; int c = 30;
    stack_push(s, &a);
    stack_push(s, &b);
    stack_push(s, &c);
    return s;
}

void test(void){
    test_push();
    test_pop(); 
    test_peek();                                                                                     
    printf("Tests finished!\n");
}

void test_push(void){
    Stack* s = create_stack_stub();
    int* c = s->tos->value;
    int* b = s->tos->next->value;
    int* a = s->tos->next->next->value;

    assert(*c == 30);
    assert(*b == 20);
    assert(*a == 10);
    assert(s->size == 3);

    stack_destroy(s);
    free(s);
}

void test_pop(void){
    Stack* s = create_stack_stub();

    stack_pop(s);
    stack_pop(s);
    stack_pop(s);

    assert(s->size == 0);

    stack_pop(s);
    stack_pop(s);
    stack_pop(s);

    stack_destroy(s);
    free(s);
}

void test_peek(void){
    Stack* s = create_stack_stub();

    int* a = stack_peek(s);
    assert(*a == 30);
    assert(s->size == 3);

    stack_pop(s);

    int* b = stack_peek(s);
    assert(*b == 20);
    assert(s->size == 2);

    stack_pop(s);

    int* c = stack_peek(s);
    assert(*c == 10);
    assert(s->size == 1);
    stack_pop(s);

    assert(stack_peek(s) == NULL);

    stack_pop(s);
    stack_pop(s);

    free(a);
    free(b);
    free(c);

    stack_destroy(s);
    free(s);
}
void test_deep_copy(void){
    Stack* s = create_stack_stub();
    Stack* copy = stack_deep_copy(s);
    
    int* s1 = s->tos->value;
    int* s2 = s->tos->next->value;
    int* s3 = s->tos->next->next->value;

    int* copy1 = copy->tos->value;
    int* copy2 = copy->tos->next->value;
    int* copy3 = copy->tos->next->next->value;


    assert(*s1 == *copy1);
    assert(*s2 == *copy2);
    assert(*s3 == *copy3);

    stack_destroy(s);
    free(s);
}