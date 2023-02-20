#include "../inc/matrix_generate.h"

int matrix_generate(int **matrix, int *const n, int *const m, int *const number_nonzero_el)
{
    printf("Введите количество строк матрицы (> 0): ");
    if (fscanf(stdin, "%d", n) != 1)
        return MATRIX_GENERATE_ERROR;
    if (*n < 1)
        return MATRIX_GENERATE_ERROR;

    printf("Введите количество столбцов матрицы (> 0): ");
    if (fscanf(stdin, "%d", m) != 1)
        return MATRIX_GENERATE_ERROR;
    if (*m < 1)
        return MATRIX_GENERATE_ERROR;

    float procent_matrix_sparse;
    printf("Введите процент разреженности матрицы (от 0 до 99): ");
    if (fscanf(stdin, "%f", &procent_matrix_sparse) != 1)
        return MATRIX_GENERATE_ERROR;
    if (procent_matrix_sparse < 0 || procent_matrix_sparse > 99)
        return MATRIX_GENERATE_ERROR;

    *matrix = (int*)calloc(*n * *m, sizeof(int));

    *number_nonzero_el = (procent_matrix_sparse / 100 * (*n * *m));

    srand(time(NULL));
    for (int i = 0, row, column; i < *number_nonzero_el; i++)
    {
        row = rand() % *n;
        column = rand() % *m;
        while (*(*matrix + row * *m + column) != 0)
        {
            row = rand() % *n;
            column = rand() % *m;
        }
        *(*matrix + row * *m + column) = rand() % 100 + 1;  
    }

    return OK;
}