#ifndef ANALYS_H
#define ANALYS_H

#include "sys/time.h"
#include "sort_arr.h"
#include "sort_list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void analys(void);
void copy_arr(arr_stack_t *src, arr_stack_t *dst);
list_stack_t* copy_list(list_stack_t **src, int cnt);

#endif // analys