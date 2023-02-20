#ifndef __MATRIX_CONVERISON_H__
#define __MATRIX_CONVERISON_H__

#include "menu_and_errors.h"
#include <stdio.h>
#include <stdlib.h>

void default_to_sparse(int *const matrix, const int n, const int m, \
const int number_nonzero_el, int **a, int **ai, int **ja, int **pa, int **pai, int **pja);

#endif
