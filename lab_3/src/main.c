#include "../inc/menu_and_errors.h"
#include "../inc/in_out_matrix.h"
#include "../inc/matrix_conversion.h"
#include "../inc/get_sum_matrix.h"
#include "../inc/matrix_generate.h"
#include "../inc/free.h"
#include <sys/time.h>

/*
Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов: 
- вектор A содержит значения ненулевых элементов;
- вектор IA содержит номера строк для элементов вектора A;
- связный список JA, в элементе Nk которого находится номер компонент
в A и IA, с которых начинается описание столбца Nk матрицы A.
*/

int main(void)
{
    int *matrix1 = NULL;
    int n1, m1;
    int number_nonzero_el1 = 0;
    int *a1 = NULL, *ai1 = NULL, *ja1 = NULL;
    int *pa1 = NULL, *pai1 = NULL, *pja1 = NULL; 

    int *matrix2 = NULL;
    int n2, m2;
    int number_nonzero_el2 = 0;
    int *a2 = NULL, *ai2 = NULL, *ja2 = NULL;
    int *pa2 = NULL, *pai2 = NULL, *pja2 = NULL;

    int *matrix3 = NULL;
    int n3, m3;
    int *a3 = NULL, *ai3 = NULL, *ja3 = NULL;
    int *pa3 = NULL, *pai3 = NULL, *pja3 = NULL; 

    int menu_number;

    do
    {
        menu();
        int rc = fscanf(stdin, "%d", &menu_number);

        if (menu_number < 0 || menu_number > 7 || rc != 1)
        {
            error_message(MENU_NUMBER_ERROR);
            continue;
        }
        if (menu_number == 1)
        {
            printf("\nВведите первую матрицу:\n");
            if (input_matrix_default_format(&matrix1, &n1, &m1, &number_nonzero_el1) != OK)
            {
                error_message(IO_ERROR);
                if (matrix1)
                    free(matrix1);
                matrix1 = NULL;
                continue;
            }
            printf("\nВведите вторую матрицу:\n");
            if (input_matrix_default_format(&matrix2, &n2, &m2, &number_nonzero_el2) != OK || \
            m1 != m2 || n1 != n2 || (number_nonzero_el1 == 0 && number_nonzero_el2 == 0))
            {
                error_message(IO_ERROR);
                if (matrix1)
                    free(matrix1);
                if (matrix2)
                    free(matrix2);
                matrix1 = NULL;
                matrix2 = NULL;
                continue;
            }
            default_to_sparse(matrix1, n1, m1, number_nonzero_el1, &a1, &ai1, &ja1, &pa1, &pai1, &pja1);
            default_to_sparse(matrix2, n2, m2, number_nonzero_el2, &a2, &ai2, &ja2, &pa2, &pai2, &pja2);
            continue;
        }
        if (menu_number == 2)
        {
            printf("\nГенерирование первой матрицы:\n");
            if (matrix_generate(&matrix1, &n1, &m1, &number_nonzero_el1) != OK)
            {
                error_message(MATRIX_GENERATE_ERROR);
                if (matrix1)
                    free(matrix1);
                matrix1 = NULL;
                continue;
            }
            printf("\nГенерирование второй матрицы:\n");
            if (matrix_generate(&matrix2, &n2, &m2, &number_nonzero_el2) != OK || \
            m1 != m2 || n1 != n2)
            {
                error_message(MATRIX_GENERATE_ERROR);
                if (matrix1)
                    free(matrix1);
                if (matrix2)
                    free(matrix2);
                matrix1 = NULL;
                matrix2 = NULL;
                continue;
            }
            default_to_sparse(matrix1, n1, m1, number_nonzero_el1, &a1, &ai1, &ja1, &pa1, &pai1, &pja1);
            default_to_sparse(matrix2, n2, m2, number_nonzero_el2, &a2, &ai2, &ja2, &pa2, &pai2, &pja2);
            continue;
        }
        if (menu_number == 3)
        {
            if (matrix1 == NULL || matrix2 == NULL)
            {
                error_message(EMPTY_MATRIX_ERROR);
                continue;
            }
            default_matrix_sum(&matrix3, &n3, &m3, matrix1, matrix2, n2, m2);
            printf("\nРезультат сложения матриц:\n");
            print_matrix_default_format(matrix3, n3, m3);
            continue;

        }
        if (menu_number == 4)
        {
            if (matrix1 == NULL || matrix2 == NULL)
            {
                error_message(EMPTY_MATRIX_ERROR);
                continue;
            }
            sparse_matrix_sum(&a3, &ai3, &ja3, &pa3, &pai3, &pja3, a1, ai1, ja1, pa1, pai1, pja1, a2, ai2, ja2, \
            pa2, pai2, pja2, number_nonzero_el1, number_nonzero_el2, m1);
            printf("\nРезультат сложения матриц:\n");
            print_matrix_sparse_format(a3, ai3, ja3, pa3, pai3, pja3);
            continue;
        }
        if (menu_number == 5)
        {
            if (matrix1 == NULL || matrix2 == NULL)
            {
                error_message(EMPTY_MATRIX_ERROR);
                continue;
            }
            printf("\nВывод первой матрицы:\n");
            print_matrix_default_format(matrix1, n1, m1);
            printf("\nВывод второй матрицы:\n");
            print_matrix_default_format(matrix2, n2, m2);
            continue;
        }
        if (menu_number == 6)
        {
            if (matrix1 == NULL || matrix2 == NULL)
            {
                error_message(EMPTY_MATRIX_ERROR);
                continue;
            }
            printf("\nВывод первой матрицы:\n");
            print_matrix_sparse_format(a1, ai1, ja1, pa1, pai1, pja1);
            printf("\nВывод второй матрицы:\n");
            print_matrix_sparse_format(a2, ai2, ja2, pa2, pai2, pja2);
            continue;
        }
        if (menu_number == 7)
        {
            if (matrix1 == NULL || matrix2 == NULL)
            {
                error_message(EMPTY_MATRIX_ERROR);
                continue;
            }

            struct timeval ta, te;

            printf("Размер %d x %d:\n", n2, m2);
            printf("Разреженности процент: %.1f", (float)number_nonzero_el1/(n2 * m2)*100);

            printf("\nСтандартный формат:\n");
            printf("Время: ");
            gettimeofday(&ta, NULL);
            default_matrix_sum(&matrix3, &n3, &m3, matrix1, matrix2, n2, m2);
            gettimeofday(&te, NULL);
            printf("%lf sec\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);
            printf("Объем памяти: ");
            printf("%lu\n", n3 * m3 * sizeof(int));

            printf("\nРезреженный формат\n");
            printf("Время: ");
            gettimeofday(&ta, NULL);
            sparse_matrix_sum(&a3, &ai3, &ja3, &pa3, &pai3, &pja3, a1, ai1, ja1, pa1, pai1, pja1, a2, ai2, ja2, \
            pa2, pai2, pja2, number_nonzero_el1, number_nonzero_el2, m1);
            gettimeofday(&te, NULL);
            printf("%lf sec\n",\
            te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec)/1000000.0);
            printf("Объем памяти: ");
            printf("%lu\n", (pa3 - a3) * sizeof(int) + (pai3 - ai3) * sizeof(int) + (pja3 - ja3) * sizeof(int));
        }
        if (menu_number == 0)
        {
            free_all(&matrix1, &matrix2, &matrix3, &a1, &a2, &a3, &ai1, &ai2, &ai3, &ja1, &ja2, &ja3);
            return OK;
        }
    } while (1);
}
