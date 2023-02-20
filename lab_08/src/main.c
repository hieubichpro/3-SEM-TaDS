#include "main.h"

int main(void)
{
    int rc;
    int size;
    int from, to;
    int *way;
    struct table_t *union_table;
    struct table_t *table;
    uint64_t start, end;

    greeting();

    printf("Введите количество городов: ");
    rc = check_number(&size, 1, INT_MAX);
    if (rc != OK)
    {
        printf("Введено неверно\n");
        return rc;
    }
    table = create_table(size, 2);

    printf("Введите информацию на графе (типа \"откуда куда длина пошлина\"). ");
    printf("Введите \"-1\" для завершения  (индекс с нуля):\n");
    rc = fill_table(table);
    if (rc != OK)
    {
        printf("Введено неверно\n");
        free_table(table);
        return rc;
    }
    printf("Введите два города (откуда - куда): ");
    if (check_number(&from, 0, table->size) || check_number(&to, 0, table->size))
    {
        printf("Введено неверно\n");
        free_table(table);
        return READ_ERROR;
    }
    int m = 0;
    int amount = 0;
    union_table = copy_table(table);
    start = tick();
    way = deicstra(union_table, from, to, &m, &amount);
    end = tick();
    if (way)
    {
        printf("Минимальная (сумма длин пути + сумма пошлин) = %d\n", m);
        for (int i = amount - 1; i > 0; i--)
            printf("%d -> ", way[i]);
        printf("%d\n", way[0]);
        // free(way);
    }
    else
        printf("Нет дорог с %d в %d\n", from, to);

    // printf("Time of working algorithm: %ju\n", end - start);
    // printf("Memory for table: %ld\n\n\n",
    //        table->size * table->size * 3 * sizeof(int) + sizeof(struct table_t) * 2);
    export_to_dot(*table, way);
    free_table(table);
    free_table(union_table);
    free(way);
    return OK;
}
/*
0 1 1 1
1 2 2 1
2 3 11 10
3 5 8 2
3 4 4 1
4 0 3 1
0 2 4 1
4 2 10 1
-1
*/
