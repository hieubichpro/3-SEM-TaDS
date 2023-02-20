#include "../inc/get_sum_matrix.h"
#include <stdio.h>

void default_matrix_sum(int **matrix3, int *n3, int *m3, int *const matrix1, \
int *const matrix2, const int n, const int m)
{
    *n3 = n;
    *m3 = m;
    *matrix3 = (int *)malloc(n * m * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            *(*matrix3 + i * m + j) = *(matrix1 + i * m + j) + *(matrix2 + i * m + j);
        }
    }
}

void sparse_matrix_sum(int **a3, int **ai3, int **ja3, int **pa3, int **pai3, int **pja3, \
int *a1, int *ai1, int *ja1, int *pa1, int *pai1, int *pja1, int *a2, int *ai2, int *ja2, \
int *pa2, int *pai2, int *pja2, const int number_nonzero_el1, const int number_nonzero_el2, const int m)
{
    *a3 = (int *)malloc((number_nonzero_el1 + number_nonzero_el2) * sizeof(int));
    *ai3 = (int *)malloc((number_nonzero_el1 + number_nonzero_el2) * sizeof(int));
    *ja3 = (int *)malloc((m + 1) * sizeof(int));

    *pa3 = *a3;
    *pai3 = *ai3;
    *pja3 = *ja3;

    int size = 0, js_size = 0, check = 0;
    *(*ja3 + js_size) = 0;
    js_size++;
    for(int i = 1; i < pja1 - ja1; i++)
    {
        for(int j = *(ja1 + i - 1); j < *(ja1 + i); j++)
        {
            check = 0;
            for(int k = *(ja2 + i - 1); k < *(ja2 + i); k++)
            {
                if (*(ai1 + j) == *(ai2 + k))
                {
                    if ((*(a1 + j) + *(a2 + k)) != 0)
                    {
                        *(*a3 + size) = *(a1 + j) + *(a2 + k);
                        *(*ai3 + size) = *(ai1 + j);
                        size++;
                    }
                    check = 1;
                }
            }
            if (check == 0)
            {
                *(*a3 + size) = *(a1 + j);
                *(*ai3 + size) = *(ai1 + j);
                size++;
            }
        }
        for(int k = *(ja2 + i - 1); k < *(ja2 + i); k++)
        {
            check = 0;
            for(int j = *(ja1 + i - 1); j < *(ja1 + i); j++)
            {
                if (*(ai1 + j) == *(ai2 + k))
                    check = 1;
            }
            if (check == 0)
            {
                *(*a3 + size) = *(a2 + k);
                *(*ai3 + size) = *(ai2 + k);
                size++;
            }
        }
        *(*ja3 + js_size) = size;
        js_size++;
    }

    *pa3 = *a3 + size;
    *pai3 = *ai3 + size;
    *pja3 = *ja3 + js_size;

    *a3 = (int*)realloc(*a3, (*pa3 - *a3) * sizeof(int));
    *ai3 = (int*)realloc(*ai3, (*pai3 - *ai3) * sizeof(int));
}
