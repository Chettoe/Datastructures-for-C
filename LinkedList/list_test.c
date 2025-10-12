#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include "list_test.h"

void _test_get_index(void);
void _test_delete_index(void);
void _test_push_front(void);
void _test_insert(void);
void _test_deep_copy(void);
LinkedList* _create_test_linked_list(void);
void _destroy_test_linked_list(LinkedList* l);

LinkedList* _create_test_linked_list(void){
    LinkedList* list = create_linked_list(INT);
    for(int i = 0; i < 10; i++){
        linked_list_push_back(list, &i);
    }
    return list;
} 

void _destroy_test_linked_list(LinkedList* l){
    if(l->is_owner == false){
        return;
    }
    linked_list_destroy(l);
    free(l);
}

void test_list(){
    _test_get_index();
    _test_delete_index();
    _test_push_front();
    _test_insert();
    _test_deep_copy();
    printf("Tests finished!\n");
}

void _test_get_index(void){
    LinkedList* l = _create_test_linked_list();

    int* a = linked_list_get_index(l, 0)->value;
    int* b = linked_list_get_index(l, 5)->value;
    int* c = linked_list_get_index(l, 9)->value;

    assert(*a == 0);
    assert(*b == 5);
    assert(*c == 9);
    assert(l->size == 10);

    _destroy_test_linked_list(l);
}

void _test_delete_index(void){
    LinkedList* l = _create_test_linked_list();

    linked_list_delete_index(l, 0);
    assert(l->size == 9);

    linked_list_delete_index(l, 8);
    assert(l->size == 8);

    linked_list_delete_index(l, 3);
    assert(l->size == 7);

    _destroy_test_linked_list(l);
}

void _test_push_front(void){
    LinkedList* l = _create_test_linked_list();
    int a = 100;

    linked_list_push_front(l, &a);

    assert(l->size == 11);
    int* start = linked_list_get_index(l, 0)->value;
    assert(*start == 100);

    _destroy_test_linked_list(l);
}

void _test_insert(void){
    LinkedList* l = _create_test_linked_list();
    Node* prev = linked_list_get_index(l, 4);
    int x = 999;
    Node* e = list_node_create(l, &x);

    linked_list_insert(l, prev, e);

    int* y = linked_list_get_index(l, 5)->value;
    assert(*y == 999);
    assert(l->size == 11);


    prev = linked_list_get_index(l, 0);
    linked_list_insert(l, prev, e);

    y = linked_list_get_index(l, 1)->value;
    assert(*y == 999);
    assert(l->size == 12);


    prev = linked_list_get_index(l, 11);
    linked_list_insert(l, prev, e);

    y = linked_list_get_index(l, 12)->value;
    assert(*y == 999);
    assert(l->size == 13);

    free(e->value);
    free(e);
    _destroy_test_linked_list(l);
}

void _test_deep_copy(void){
    LinkedList l;
    linked_list_init(&l, true, INT);
    int x = 1; int y = 2;
    linked_list_push_back(&l, &x);
    linked_list_push_back(&l, &y);
    LinkedList* copy = linked_list_deep_copy(&l);
    linked_list_destroy(&l);
    linked_list_destroy(copy);
    free(copy);
}

