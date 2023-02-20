#include "../inc/free.h"

void free_all(int **matrix1, int **matrix2, int **matrix3, int **a1, \
int **a2, int **a3, int **ai1, int **ai2, int **ai3, int **ja1, int **ja2, int **ja3)
{
    if (*matrix1)
        free(*matrix1);
    if (*matrix2)
        free(*matrix2);
    if (*matrix3)
        free(*matrix3);
    if (*a1)
        free(*a1);
    if (*ai1)
        free(*ai1);
    if (*ja1)
        free(*ja1);
    if (*a2)
        free(*a2);
    if (*ai2)
        free(*ai2);
    if (*ja2)
        free(*ja2);
    if (*a3)
        free(*a3);
    if (*ai3)
        free(*ai3);
    if (*ja3)
        free(*ja3);        
}
