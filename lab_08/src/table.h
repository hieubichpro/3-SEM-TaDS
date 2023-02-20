#ifndef __TABLE_H__
#define __TABLE_H__

#include "main.h"
#include "table.h"
#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>

struct table_t *create_table(int size, int count);
int fill_table(struct table_t *matrix);
void free_table(struct table_t *table);
void print_table(FILE *flow, struct table_t *table, int count);

struct table_t *copy_table(struct table_t *table);
int *deicstra(struct table_t *table, int from, int to, int *m, int *amount);


struct table_t
{
    int size;
    int **matrix;
};


#endif
