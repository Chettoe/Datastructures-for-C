#include "test_queue.h"
#include "queue.h"
#include <assert.h>
#include <stdio.h>
Queue* create_queue_stub(void){
    Queue* q = create_queue(INT);
    int a = 10; int b = 2; int c = 8;
    queue_push(q, &a);
    queue_push(q, &b);
    queue_push(q, &c);
    return q;
}
void test(void){
    test_push();
    test_pop();
    test_peek();
    test_deep_copy();
    printf("Tests finished!\n");
}

void test_push(void){
    Queue* q = create_queue_stub();
    assert(q->size == 3);

    int* first = q->front->value;
    int* mid = q->list->head->next->next->value;
    int* last = q->back->value;

    assert(*first == 10);
    assert(*mid == 2);
    assert(*last == 8);

    int x = 20;
    queue_push(q, &x);
    last = q->back->value;

    assert(*last == 20);
    assert(q->size == 4);
    destroy_queue(q);
    free(q);
}

void test_pop(void){
    Queue* q = create_queue_stub();
    queue_pop(q);
    assert(q->size == 2);
    int* first = q->front->value;
    assert(*first == 2);
    queue_pop(q);
    queue_pop(q);
    queue_pop(q);
    queue_pop(q);
    assert(q->size == 0);
    destroy_queue(q);
    free(q);
}

void test_peek(void){
    Queue* q = create_queue_stub();

    int* front = q->front->value;
    int* peek = queue_peek(q);
    assert(*front == *peek);
    free(peek);

    queue_pop(q);

    front = q->front->value;
    peek = queue_peek(q);
    assert(*front == *peek);
    free(peek);

    queue_pop(q);

    front = q->front->value;
    peek = queue_peek(q);
    assert(*front == *peek);
    free(peek);

    queue_pop(q);

    void* peek_end = queue_peek(q);
    assert(peek_end == NULL);

    destroy_queue(q);
    free(q);
}

void test_deep_copy(void){
    Queue* q = create_queue_stub();

    Queue* copy = queue_deep_copy(q);

    int* q1 = q->front->value;
    int* q2 = q->front->next->value;
    int* q3 = q->back->value;

    int* copy1 = q->front->value;
    int* copy2 = q->front->next->value;
    int* copy3 = q->back->value;

    assert(*q1 == *copy1);
    assert(*q2 == *copy2);
    assert(*q3 == *copy3);

    destroy_queue(copy);
    free(copy);

    destroy_queue(q);
    free(q);
}
