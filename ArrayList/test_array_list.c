#include "test_array_list.h"
#include "array_list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void _print_stats(ArrayList* al);
ArrayList* _create_array_list_stub(void);
void _test_push_back(void);
void _test_push_front(void);
void _test_insert(void);
void _test_remove(void);
void _test_get(void);
void _test_find(void);
void _test_resize(void);
void _test_deep_copy(void);

void test(void){
    _test_push_back();
    _test_push_front();
    _test_insert();
    _test_remove();
    _test_get();
    _test_find();
    _test_resize();
    _test_deep_copy();
    printf("Tests finished!\n");
}


ArrayList* _create_array_list_stub(void){
    ArrayList* arr = create_array_list(INT);
    int a = 10; int b = 20; int c = 3;
    array_list_push_back(arr, &a);
    array_list_push_back(arr, &b);
    array_list_push_back(arr, &c);
    return arr;
}

void _test_push_back(void){
    ArrayList* arr = _create_array_list_stub();
    int a = 5; int b = 4; int c = 2;
    array_list_push_back(arr, &a);
    assert(arr->size == 4);
    array_list_push_back(arr, &b);
    assert(arr->size == 5);
    array_list_push_back(arr, &c);
    assert(arr->size == 6);
    int* d = arr->array[3];
    int* e = arr->array[4];
    int* f = arr->array[5];
    assert(*d == 5);
    assert(*e == 4);
    assert(*f == 2);

    array_list_destroy(arr);
    free(arr);
}

void _test_push_front(void){
    ArrayList* arr = _create_array_list_stub();
    int a = 5; int b = 4; int c = 2;

    array_list_push_front(arr, &a);
    assert(arr->size == 4);
    int* d = arr->array[0];
    assert(*d == 5);

    array_list_push_front(arr, &b);
    assert(arr->size == 5);
    int* e = arr->array[0];
    assert(*e == 4);

    array_list_push_front(arr, &c);
    assert(arr->size == 6);
    int* f = arr->array[0];
    assert(*f == 2);

    array_list_destroy(arr);
    free(arr);

    ArrayList al;
    array_list_init(&al, true, INT);
    int x = 10;
    array_list_push_front(&al, &x);
    int* y = al.array[0];
    assert(*y == 10);
    array_list_destroy(&al);
}

void _test_insert(void){
    ArrayList* arr = _create_array_list_stub();
    int a = 8; int b = 0; int c = 9;

    array_list_insert(arr, &a, 0);
    assert(arr->size == 4);
    int* temp = arr->array[0];
    assert(*temp == 8);

    array_list_insert(arr, &b, 4);
    assert(arr->size == 5);
    temp = arr->array[4];
    assert(*temp == 0);

    array_list_insert(arr, &c, 2);
    assert(arr->size == 6);
    temp = arr->array[2];
    assert(*temp == 9);


    array_list_destroy(arr);
    free(arr);


    ArrayList al;
    array_list_init(&al, true, INT);
    int x = 10;
    array_list_insert(&al, &x, 0);
    int* y = al.array[0];
    assert(*y == 10);
    array_list_insert(&al, &x, 9999999);
    array_list_destroy(&al);
}

void _test_remove(void){
    ArrayList* al = _create_array_list_stub();
    array_list_remove(al, 0);
    int* a = al->array[0];
    int* b = al->array[1];
    assert(*a == 20);
    assert(*b == 3);
    assert(al->size == 2);

    array_list_remove(al, 1);
    assert(al->size == 1);
    int* c = al->array[0];
    assert(*c == 20);

    array_list_remove(al, 0);
    assert(al->size == 0);

    array_list_destroy(al);
    free(al);
}

void _test_get(void){
    ArrayList* al = _create_array_list_stub();
    int* a = array_list_get(al, 0);
    int* b = array_list_get(al, 1);
    int* c = array_list_get(al, 2);

    assert(*a == 10);
    assert(*b == 20);
    assert(*c == 3);

    array_list_destroy(al);
    free(al);
    free(a); free(b); free(c);
}

void _test_find(void){
    ArrayList* al = _create_array_list_stub();
    int a = 10; int b = 20; int c = 100;

    assert(array_list_find(al, &a) == 0);
    assert(array_list_find(al, &b) == 1);
    assert(array_list_find(al, &c) == (size_t) -1);

    array_list_destroy(al);
    free(al);
}

void _test_resize(void){
    ArrayList al;
    array_list_init(&al, true, INT);
    for(int i = 0; i < 10; i++){
        int* x = &i;
        array_list_push_back(&al, x);
    }
    assert(al.capacity == 16);

    for(size_t i = 0; i < al.size; ++i){
        int* a = al.array[i];
        printf("%d ", *a);
    }
    printf("\n");
    _print_stats(&al);

    for(int i = 0; i < 6; i++){
        array_list_remove(&al, 0);
    }
    assert(al.capacity == 8);

    for(size_t i = 0; i < al.size; ++i){
        int* a = al.array[i];
        printf("%d ", *a);
    }
    printf("\n");
    _print_stats(&al);

    array_list_destroy(&al);
}

void _test_deep_copy(void){
    ArrayList* al = _create_array_list_stub();
    ArrayList* copy = array_list_deep_copy(al);
    
    assert(al->capacity == copy->capacity);
    assert(al->data_size == al->data_size);
    assert(al->size == al->size);
    int* a_al = al->array[0]; int* b_al = al->array[1]; int* c_al = al->array[2];
    int* a_copy = al->array[0]; int* b_copy = al->array[1]; int* c_copy = al->array[2];

    assert(*a_al == *a_copy);
    assert(*b_al == *b_copy);
    assert(*c_al == *c_copy);

    array_list_destroy(al);
    array_list_destroy(copy);
    free(al);
    free(copy);
}

void _print_stats(ArrayList* al){
    printf("Size: %lu\n", al->size);
    printf("Capacity: %lu\n", al->capacity);
    printf("Data Size: %lu\n", al->data_size);
    int* x = array_list_get(al, 0);
    printf("Size of Value: %lu\n", sizeof(*x));
    free(x);
}