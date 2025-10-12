#include "test_bin_tree.h"
#include "bin_tree.h"
#include <assert.h> 
#include <stdio.h>
#include <stdlib.h>

void _test_add(void);
void _test_sorted(void);
void _test_find(void);
BinTree* _create_stub_bin_tree(void);
void _test_find_link(void);
void _test_remove(void);
void _test_no_duplicates(void);

BinTree* _create_stub_bin_tree(void){
    BinTree* bt = create_bin_tree(INT);
    int a = 2; int b = 3; int c = 5; int d = -6; int e = 90;
    bin_tree_add(bt, 10, &a);
    bin_tree_add(bt, 4, &b);
    bin_tree_add(bt, 12, &c);
    bin_tree_add(bt, 6, &d);
    bin_tree_add(bt, 20, &e);
    return bt;
}

void test_bin_tree(void){
    _test_add();
    _test_sorted();
    _test_find();
    _test_find_link();
    _test_remove();
    _test_no_duplicates();
    printf("Tests finished!\n");
}

void _test_add(void){
    BinTree* bt = create_bin_tree(INT);
    int a = 2; int b = 3; int c = 5;
    bin_tree_add(bt, 5, &a);
    assert(bt->size == 1);
    bin_tree_add(bt, 10, &b);
    assert(bt->size == 2);
    bin_tree_add(bt, 2, &c);
    assert(bt->size == 3);
    bin_tree_destroy(bt);
    free(bt);
}

void _test_sorted(void){
    BinTree* bt = _create_stub_bin_tree();
    int* arr = bin_tree_sorted(bt);
    assert(arr[0] == 4);
    assert(arr[1] == 6);
    assert(arr[2] == 10);
    assert(arr[3] == 12);
    assert(arr[4] == 20);
    bin_tree_destroy(bt);
    free(bt);
    free(arr);
}

void _test_find(void){
    BinTree* bt = _create_stub_bin_tree();
    bool x = bin_tree_find_key(bt, 10);
    bool y = bin_tree_find_key(bt, 4);
    bool z = bin_tree_find_key(bt, 12);
    bool a = bin_tree_find_key(bt, 6);
    bool b = bin_tree_find_key(bt, 20);

    assert(x);
    assert(y);
    assert(z);
    assert(a);
    assert(b);

    bool c = bin_tree_find_key(bt, 0);
    bool d = bin_tree_find_key(bt, -1);
    bool e = bin_tree_find_key(bt, 100);

    assert(!c);
    assert(!d);
    assert(!e);

    bin_tree_destroy(bt);
    free(bt);
}

void _test_find_link(void){
    BinTree* bt = _create_stub_bin_tree();
    TreeNode** n = bin_tree_find_link(bt, 10);
    assert((*n)->key == 10);
    bin_tree_destroy(bt);
    free(bt);
}

void _test_remove(void){
    BinTree* bt = _create_stub_bin_tree();

    bin_tree_remove(bt, 20000);
    assert(bt->size == 5);

    bin_tree_remove(bt, 20);
    assert(bt->size == 4);

    bin_tree_remove(bt, 10);
    assert(bt->size == 3);

    bin_tree_remove(bt, 6);
    assert(bt->size == 2);

    bin_tree_remove(bt, 4);
    assert(bt->size == 1);

    bin_tree_remove(bt, 12);
    assert(bt->size == 0);

    bin_tree_destroy(bt);
    free(bt);
}

void _test_no_duplicates(void){
    BinTree* bt = _create_stub_bin_tree();
    int a = 12; int b = 7; int c = 0; int d = 4;
    bin_tree_add(bt, 10, &a);
    bin_tree_add(bt, 10, &b);
    bin_tree_add(bt, 10, &a);
    assert(bt->size == 5);
    bin_tree_add(bt, 1, &c);
    assert(bt->size == 6);
    bin_tree_add(bt, 1, &d);
    assert(bt->size == 6);
    bin_tree_destroy(bt);
    free(bt);
}