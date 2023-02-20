#ifndef __TREE_UTILS_H__
#define __TREE_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/macro.h"
#include "include/rc.h"

typedef struct tree_node
{
    char *val;
    unsigned char height;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

typedef struct
{
    tree_node **arr;
    int size;
    int mem_size;
} dynarr_t;

typedef void (*ptr_action_t)(tree_node*, void*);

tree_node *create_node(char *val);

tree_node *insert(tree_node *node, char *val);

void fill_tree(tree_node **root, FILE *f);

void print_tree(tree_node *root, int space);

void tree_depth(tree_node *root, int *vrtxs, int *cmprs, int depth);

void push_back(dynarr_t *arr, tree_node *to_add);

void store_nodes(tree_node *root, dynarr_t *arr);

tree_node *build_tree(dynarr_t *arr, int start, int end);

tree_node *balance_tree(tree_node *root, int *unique);

void free_tree(tree_node *node);

void apply_pre(tree_node *tree, ptr_action_t f, void *arg);

void node_to_dot(tree_node *tree, void *param);

void btree_export_to_dot(FILE *f, const char *tree_name, tree_node *tree);

tree_node *insertbalance(tree_node *head, tree_node *node);

tree_node *balancenode(tree_node *head);

tree_node *returnleft(tree_node *head);

tree_node *returnright(tree_node *head);

int factorlr(tree_node *head);

void newheight(tree_node *head);

int whatheight(tree_node *head);

#endif