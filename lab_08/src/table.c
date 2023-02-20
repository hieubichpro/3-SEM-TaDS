#include "table.h"

struct table_t *create_table(int size, int count)
{
    struct table_t *table = malloc(sizeof(struct table_t));
    if (!table)
        return NULL;

    table->size = size;
    table->matrix = malloc(sizeof(int*) * size);
    if (!table->matrix)
    {
        free(table);
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        table->matrix[i] = calloc(size * count, sizeof(int));
        if (!table->matrix[i])
        {
            for (int j = 0; j < i; j++)
                free(table->matrix[j]);
            free(table->matrix);
            free(table);
            return NULL;
        }
    }

    return table;
}


int fill_table(struct table_t *table)
{
    int first = -1, second = -1;
    int length = 0, duty = 0;
    int rc = OK;

    while (1)
    {
        rc = check_number(&first, -1, table->size - 1);
        if (rc != OK)
            return READ_ERROR;
        if (first == -1)
            break;

        rc = check_number(&second, 0, table->size - 1);
        if (rc != OK || first == second)
            return READ_ERROR;
        if (second == -1)
            break;
        rc = check_number(&length, 1, INF);
        if (rc != OK)
            return READ_ERROR;

        rc = check_number(&duty, 1, INF);
        if (rc != OK || duty == -1)
            return READ_ERROR;

        table->matrix[first][second + second] = length;
        table->matrix[first][second + second + 1] = duty;
        table->matrix[second][first + first] = length;
        table->matrix[second][first + first + 1] = duty;
    }
    for (int i = 0; i < table->size; i++)
        for (int j = 0; j < table->size * 2; j += 2)
            if (table->matrix[i][j] == 0 && i != (j / 2))
            {
                table->matrix[i][j] = INF;
                table->matrix[i][j + 1] = INF;
            }

    return OK;
}


void free_table(struct table_t *table)
{
    for (int i = 0; i < table->size; i++)
        free(table->matrix[i]);

    free(table->matrix);
    free(table);
}


void print_table(FILE *flow, struct table_t *table, int count)
{
    for (int i = 0; i < table->size; i++)
    {
        for (int j = 0; j < table->size * count; j += count)
            if (count == 2)
                fprintf(flow, "%10d, %10d | ", table->matrix[i][j], table->matrix[i][j + 1]);
            else
                fprintf(flow, "%10d | ", table->matrix[i][j]);
        printf("\n");
    }
}


struct table_t *copy_table(struct table_t *table)
{
    struct table_t *new_table = create_table(table->size, 1);
    if (!new_table)
        return NULL;

    for (int i = 0; i < table->size; i++)
        for (int j = 0; j < table->size; j++)
            if (table->matrix[i][j * 2] != INF)
                new_table->matrix[i][j] = table->matrix[i][j * 2] + table->matrix[i][j * 2 + 1];
            else
                new_table->matrix[i][j] = INF;
    return new_table;
}


int *deicstra(struct table_t *table, int from, int to, int *m, int *amount)
{
    int *min_s = malloc(sizeof(int) * table->size);
    int *visited = malloc(sizeof(int) * table->size);
    int temp, min_ind, min;
    int begin_ind = from;
    for (int i = 0; i < table->size; i++)
    {
        min_s[i] = INF;
        visited[i] = 1;
    }
    min_s[begin_ind] = 0;
    do
    {
        min_ind = INF;
        min = INF;
        for (int i = 0; i < table->size; i++)
        {
            if ((visited[i] == 1) && (min_s[i]<min))
            {
                min = min_s[i];
                min_ind = i;
            }
        }
        if (min_ind != INF)
        {
            for (int i = 0; i < table->size; i++)
            {
                if (table->matrix[min_ind][i] > 0)
                {
                    temp = min + table->matrix[min_ind][i];
                    if (temp < min_s[i])
                    {
                        min_s[i] = temp;
                    }
                }
            }
            visited[min_ind] = 0;
        }
    } while (min_ind < INF);
    if (min_s[to] == INF)
        return NULL;
    *m = min_s[to];


    int *ver = malloc(table->size * sizeof(int));
    int end = to;
    ver[0] = end + 1;
    int k = 1;
    int weight = min_s[end];

    while (end != begin_ind)
    {
        for (int i = 0; i<table->size; i++)
            if (table->matrix[i][end] != 0)
                {
                    int temp = weight - table->matrix[i][end];
                    if (temp == min_s[i])
                    {
                        weight = temp;
                        end = i;
                        ver[k] = i + 1;
                        k++;
                    }
                }
    }

    for (int i = k - 1; i >= 0; i--)
        ver[i]--;

    *amount = k;
    free(min_s);
    free(visited);
    return ver;
}


// 4 0 1 2 1 0 3 3 1 1 2 5 2 2 3 8 9 -1 2 3
//
/*
0 1 20 4
0 3 1 2
3 2 3 4
3 6 5 1
2 6 2 2
6 4 3 3
4 5 4 1
2 5 2 1
5 1 3 1
2 1 1 2
-1
*/

