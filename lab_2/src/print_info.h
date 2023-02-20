#include "struct.h"

#ifndef PRINT_INFO_H

#define PRINT_INFO_H

#define MAX_SIZE 1000

#define OK_SEARCH 0

#define ERR_START_COST -15
#define ERR_END_COST -16
#define ERR_RANGE_COST -17

void print_table(table_t table);
void print_table_keys(table_t table);
void print_table_by_keys(table_t table);
int search(table_t table);

#endif
