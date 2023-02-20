#include "../inc/in_out_matrix.h"

int input_matrix_default_format(int **matrix, int *const n, int *const m, int *const number_nonzero_el)
{
    printf("Введите количество строк матрицы (0 < x < 1000): ");
    if (fscanf(stdin, "%d", n) != 1)
        return IO_ERROR;
    if (*n < 1)
        return IO_ERROR;

    printf("Введите количество столбцов матрицы (0 < x < 1000): ");
    if (fscanf(stdin, "%d", m) != 1)
        return IO_ERROR;
    if (*m < 1)
        return IO_ERROR;

    printf("Введите количество ненулевых элементов матрицы (0 < x < 100): ");
    if (fscanf(stdin, "%d", number_nonzero_el) != 1)
        return IO_ERROR;
    if (*number_nonzero_el < 0 || *number_nonzero_el > *n * *m)
        return IO_ERROR;

    *matrix = (int*)calloc(*n * *m, sizeof(int));

    for (int _ = 0, i, j, val; _ < *number_nonzero_el; _++)
    {
        printf("Введите номер строки элемента (0 <= x < %d): ", *n);
        if (fscanf(stdin, "%d", &i) != 1)
            return IO_ERROR;
        if (i < 0 || i >= *n)
            return IO_ERROR;
            
        printf("Введите номер столбца элемента (0 <= x < %d): ", *m);
        if (fscanf(stdin, "%d", &j) != 1)
            return IO_ERROR;
        if (j < 0 || j >= *m)
            return IO_ERROR;

        printf("Введите значение элемента (x != 0): ");
        if (fscanf(stdin, "%d", &val) != 1)
            return IO_ERROR;
        if (val == 0)
            return IO_ERROR;
        *(*matrix + i * *m + j) = val;
    }

    return OK;
}

void print_matrix_default_format(int *const matrix, const int n, const int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%4d", *(matrix + i * m + j));
        }
        printf("\n");
    }
}

void print_matrix_sparse_format(int *a, int *ai, int *ja, int *pa, int *pai, int *pja)
{
    printf(" A = [ ");
    for (; a < pa; a++)
    {
        printf("%d ", *a);
    }
    printf("]\n");

    printf("IA = [ ");
    for (; ai < pai; ai++)
    {
        printf("%d ", *ai);
    }
    printf("]\n");

    printf("JA = [ ");
    for (; ja < pja; ja++)
    {
        printf("%d ", *ja);
    }
    printf("]\n");
}
