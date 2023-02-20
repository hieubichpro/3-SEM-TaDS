#ifndef __MENU_AND_ERRORS_H__
#define __MENU_AND_ERRORS_H__

#include <stdio.h>

#define OK 0
#define IO_ERROR 1
#define EMPTY_MATRIX_ERROR 2
#define MENU_NUMBER_ERROR 3
#define MATRIX_GENERATE_ERROR 4

void menu(void);
void error_message(const int rc);

#endif
