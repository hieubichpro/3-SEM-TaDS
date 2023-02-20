#ifndef SORT_ARR_H
#define SORT_ARR_H

#include "array.h"

int sort_arr(arr_stack_t *st_a, arr_stack_t *st_b, arr_stack_t *res);
void append_in_sorted_stack(arr_stack_t *src, arr_stack_t *dst);

#endif // sort_arr