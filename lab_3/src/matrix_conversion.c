#include "../inc/matrix_conversion.h"

void default_to_sparse(int *const matrix, const int n, const int m, \
const int number_nonzero_el, int **a, int **ai, int **ja, int **pa, int **pai, int **pja)
{
    *a = (int*)malloc(number_nonzero_el * sizeof(int));
    *ai = (int*)malloc(number_nonzero_el * sizeof(int));
    *ja = (int*)malloc((m + 1) * sizeof(int));
    *pa = *a;
    *pai = *ai;
    *pja = *ja;

    int a_ind = 0, ja_ind = 0;
    *(*ja + ja_ind) = 0;
    ja_ind++;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (*(matrix + j * m + i) != 0)
            {
                *(*a + a_ind) = *(matrix + j * m + i);
                *(*ai + a_ind) = j;
                a_ind++;
            }
        }
        *(*ja + ja_ind) = a_ind;
        ja_ind++;
    }

    *pa = *a + a_ind;
    *pai = *ai + a_ind;
    *pja = *ja + ja_ind;

}
