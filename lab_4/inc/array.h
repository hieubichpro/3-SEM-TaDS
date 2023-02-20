#ifndef ARRAY_H
#define ARRAY_H

#define ERR_FULL_ARR_STACK -3
#define ERR_READ -4
#define ERR_EMPTY_ARR_STACK -5

#include "menu.h"

typedef struct
{
    int a[MAX_SIZE];
    int *ptr;
} arr_stack_t;

int read_arr(arr_stack_t *st);
int push_arr(arr_stack_t *st, int item);
void init_arr(arr_stack_t *st);
void print_arr(arr_stack_t *st);
int pop_arr(arr_stack_t *st, int *item);
int get_item(int *item);

#endif // io_arr