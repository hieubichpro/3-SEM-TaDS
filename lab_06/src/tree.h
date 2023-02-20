#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sys/time.h"

#define N 100

typedef struct node
{
    char info[N];         // информационная чачть
    struct node *left;    // левое под-дерево
    struct node *right;   // правое под-дерево
} node;

typedef void (*ptr_action_t)(node*, void*);

int search_in_file(FILE *f, char c);
void node_to_dot(node *tree, void *param);
void apply_pre(node *tree, ptr_action_t f, void *arg);
void apply_post(node *tree, ptr_action_t f, void *arg);
void btree_export_to_dot(FILE *f, const char *tree_name, node *tree);

void make_color(node *tree, char c, FILE *f);
void print_tree(node *head, int down, int lr);
node *create_node(char infor[N]);
node *find_node_by_word(node *tree, char *word);
node *find_node_by_char(node *tree, char c);
void free_node(node *tree, void *param);
void free_tree(node *tree);
void node_print(node *node, void *param);
node *binary_tree_insert(node *tree, char *word);
node *read_binary_tree_from_file(FILE *f);
node *minValueNode(node *root);
node *deleteNode(node *root, char *word);
void compare_time(char *name, int lever, node *b_tree);

#endif
