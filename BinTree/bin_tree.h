#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define INT sizeof(int)
#define LONG sizeof(long)
#define FLOAT sizeof(float)
#define DOUBLE sizeof(double)
#define CHAR sizeof(char)
//add custom

typedef struct TreeNode TreeNode;

typedef struct TreeNode{
    int key;
    void* element;
    TreeNode* left;
    TreeNode* right;
}TreeNode;

typedef struct BinTree{
    TreeNode* root;
    size_t size;
    bool is_owner;
    size_t data_size;
}BinTree;

void bin_tree_init(BinTree* bt, bool is_owner, size_t data_size);
BinTree* create_bin_tree(size_t data_size);
void bin_tree_destroy(BinTree* bt);

TreeNode* create_tree_node(int key, void* element, size_t data_size);
void destroy_tree_node(TreeNode* n);


TreeNode* bin_tree_add(BinTree* bt, int key, void* element);
bool bin_tree_find_key(BinTree* bt, const int key);
TreeNode** bin_tree_find_link(BinTree* bt, const int key);
void bin_tree_remove(BinTree* bt, int key);
int* bin_tree_sorted(BinTree* bt);

#endif