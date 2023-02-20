#ifndef MENU_H
#define MENU_H

#define CREATE 1
#define PRINT  2
#define SORT   3
#define POP    4
#define PUSH   5
#define ANALYS 6
#define EXIT   8

#define ARR_TYPE  9
#define LIST_TYPE 10

#define FIRST_ST 11
#define SECOND_ST 12

#define MAX_SIZE 3002
#define ERR_ACT -1

#include <stdio.h>
#include <stdlib.h>
#include "io.h"

int choose_action(int *act);
int choose_stack_type(int *act);
int choose_stack(int *act);
void info(void);

#endif // menu