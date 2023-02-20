#include "graph.h"

int find(int *way, int k, int i, int j)
{
    for (int z = 0; z < k - 1; z++)
    {
        if ((way[z]  == i && way[z + 1] == j) || (way[z] == j && way[z + 1] == i))
            return 1;
    }
    return 0;
}


void export_to_dot(struct table_t table, int *way)
{
    FILE *f = fopen("graph.txt", "w");
    fprintf(f, "graph {\n");
    for (int i = 0; i < table.size; i++)
        for (int j = i * 2; j < table.size * 2; j += 2)
            if (table.matrix[i][j] != INF && table.matrix[i][j] != 0)
            {
                if (way && find(way, table.size, i, j / 2))
                    fprintf(f, "%d -- %d  [ label = \"%d, %d\",color=red ];\n", i, j / 2, table.matrix[i][j], table.matrix[i][j + 1]);

                else
                    fprintf(f, "%d -- %d  [ label = \"%d, %d\" ];\n", i, j / 2, table.matrix[i][j], table.matrix[i][j + 1]);
            }
    for (int i = 0; i < table.size; i++)
        if (!find(table.matrix[i], table.size, 1, 1))
            fprintf(f, "%d;\n", i);
    fprintf(f, "}\n");
    fclose(f);

    system("dot -Tpng graph.txt -o graph.png");
    system("start graph.png");
}
