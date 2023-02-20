#ifndef LIST_H
#define LIST_H

#define ERR_MALLOC -7
#define ERR_EMPTY_STACK -8
#define ERR_FULL_LIST_STACK -9

#include "menu.h"
#include "array.h"

typedef struct list_stack
{
    int data;
    struct list_stack *prev;
} list_stack_t;

typedef struct
{
    list_stack_t* a[MAX_SIZE];
    int index;
} freed_t;

int push_list(list_stack_t **ptr, int item, int *cnt);
int pop_list(list_stack_t **ptr, int *item, int *cnt);
void print_list(list_stack_t *ptr, int *cnt);
void free_list(list_stack_t **ptr, int *cnt);
int read_list(list_stack_t **ptr, int *cnt);
int pop_list_with_freed(list_stack_t **ptr, int *item, freed_t *list, int *cnt);
int push_list_with_freed(list_stack_t **ptr, int item, freed_t *list, int *cnt);

#endif // io_list