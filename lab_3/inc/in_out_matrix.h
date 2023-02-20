#ifndef __IN_OUT_MATRIX_H__
#define __IN_OUT_MATRIX_H__

#include "menu_and_errors.h"
#include <stdio.h>
#include <stdlib.h>

int input_matrix_default_format(int **matrix, int *const n, int *const m, int *const number_nonzero_el);
void print_matrix_default_format(int *const matrix, const int n, const int m);
void print_matrix_sparse_format(int *a, int *ai, int *ja, int *pa, int *pai, int *pja);

#endif
