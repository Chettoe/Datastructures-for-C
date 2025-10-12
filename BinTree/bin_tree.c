#include "bin_tree.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void _bin_tree_sorted(TreeNode* n, int* arr, size_t* index);
void _bin_tree_destroy(TreeNode *n);
void _check_memory(const void* p);
void* _copy_value(void* p, size_t data_size);

void* _copy_value(void* value, size_t data_size){
    void* copy = malloc(data_size);
    _check_memory(copy);
    memcpy(copy, value, data_size);
    return copy;
}

void _check_memory(const void* p){
    if(p == NULL){
        printf("Memory error!\n");
        assert(p != NULL);
    }
}

void bin_tree_init(BinTree* bt, bool is_owner, size_t data_size){
    bt->size = 0;
    bt->root = NULL;
    bt->is_owner = is_owner;
    bt->data_size = data_size;
}
BinTree* create_bin_tree(size_t data_size){
    BinTree* bt = malloc(sizeof(BinTree));
    _check_memory(bt);
    bin_tree_init(bt, true, data_size);
    return bt;
}
void bin_tree_destroy(BinTree* bt){
    if(bt->is_owner == false) return;
    _bin_tree_destroy(bt->root);
    bt->root = NULL;
    bt->size = 0;    
    bt->is_owner = false;
}
void _bin_tree_destroy(TreeNode* n){
    if(n == NULL) return;
    _bin_tree_destroy(n->left);
    _bin_tree_destroy(n->right);
    destroy_tree_node(n);
}

TreeNode* create_tree_node(int key, void* element, size_t data_size){
    TreeNode* n = malloc(sizeof(TreeNode));
    _check_memory(n);
    n->element = _copy_value(element, data_size);
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}
void destroy_tree_node(TreeNode* n){
    free(n->element);
    free(n);
}

//return NULL if key is added to the tree so was not inside previous
TreeNode* bin_tree_add(BinTree* bt, int key, void* element){
    if(bt->size == 0){
        TreeNode* n = create_tree_node(key, element, bt->data_size);
        bt->root = n;
        bt->size++;
        return NULL;
    }
    TreeNode** link = bin_tree_find_link(bt, key);
    if(*link) return *link;

    *link = create_tree_node(key, element, bt->data_size);
    bt->size++;
    return NULL;
}

bool bin_tree_find_key(BinTree* bt, const int key){
    TreeNode** link = bin_tree_find_link(bt, key);
    if(*link != NULL && (*link)->key == key){
        return true;
    }
    return false;
}

TreeNode** bin_tree_find_link(BinTree* bt, const int key){
    TreeNode** link = &bt->root;

    while(*link && (*link)->key != key){
        if(key > (*link)->key){
            link = &((*link)->right);
        }
        else if(key < (*link)->key){
            link = &((*link)->left);
        }
    }
    return link;
}

void bin_tree_remove(BinTree* bt, int key){
    TreeNode** link = bin_tree_find_link(bt, key);
    
    if((*link) == NULL) return;

    if((*link)->left == NULL && (*link)->right == NULL){
        destroy_tree_node((*link));
        (*link) = NULL;
        bt->size--;
        return;
    }

    TreeNode** big_left = link;

    if((*link)->left != NULL){
        big_left = &((*link)->left);
    }

    while((*big_left)->left != NULL || (*big_left)->right != NULL){
        if((*big_left)->right != NULL){
            big_left = &((*link)->right);
        }
        else if((*big_left)->left != NULL){
            big_left = &((*link)->left);
        }
    }

    (*link)->key = (*big_left)->key;
    destroy_tree_node((*big_left));
    *big_left = NULL;
    bt->size--;
}

int* bin_tree_sorted(BinTree* bt){
    size_t index = 0;
    int* arr = malloc(sizeof(int) * bt->size);
    _check_memory(arr);
    _bin_tree_sorted(bt->root, arr, &index);
    return arr;
}

void _bin_tree_sorted(TreeNode* n, int* arr, size_t* index){
    if(n == NULL) return;
    _bin_tree_sorted(n->left, arr, index);
    arr[*index] = n->key;
    (*index)++;
    _bin_tree_sorted(n->right, arr, index);
}                    
