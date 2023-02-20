#ifndef __GET_SUM_MATRIX_H__
#define __GET_SUM_MATRIX_H__

#include <stdlib.h>

void default_matrix_sum(int **matrix3, int *n3, int *m3, int *const matrix1, \
int *const matrix2, const int n, const int m);
void sparse_matrix_sum(int **a3, int **ai3, int **ja3, int **pa3, int **pai3, int **pja3, \
int *a1, int *ai1, int *ja1, int *pa1, int *pai1, int *pja1, int *a2, int *ai2, int *ja2, \
int *pa2, int *pai2, int *pja2, const int number_nonzero_el1, const int number_nonzero_el2, const int m);

#endif
