#include "include/tree_utils.h"
#include "include/list_utils.h"
#include "include/hash_utils.h"
#include "include/search.h"
#include "include/timer.h"
#include "include/io.h"

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf(ANSI_COLOR_RED
               "Неверное имя файла! Повторите попытку.\n" ANSI_COLOR_RESET);
        return FILE_ERROR;
    }

    if (fgetc(f) == EOF)
    {
        printf(ANSI_COLOR_RED
               "Файл пуст! Проверьте файл.\n" ANSI_COLOR_RESET);
        return FILE_ERROR;
    }

    rewind(f);

    char **words = fill_words(f);
    unsigned long flen = file_len(f);
    tree_node *root = NULL;

    fill_tree(&root, f);

    printf(ANSI_COLOR_YELLOW
           "БИНАРНОЕ ДЕРЕВО НА ОСНОВЕ ДАННЫХ ИЗ ФАЙЛА:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN);
    FILE *ft = fopen("test.gv", "w");

    btree_export_to_dot(ft, "my_tree", root);

    fclose(ft);

    system("xdot test.gv");
    printf(ANSI_COLOR_RESET);

    int unique;
    root = balance_tree(root, &unique);

    printf(ANSI_COLOR_YELLOW
           "БИНАРНОЕ ДЕРЕВО ПОСЛЕ БАЛАНСИРОВКИ:\n" ANSI_COLOR_YELLOW);
    printf(ANSI_COLOR_GREEN);
    FILE *ftf = fopen("test_avl.gv", "w");

    btree_export_to_dot(ftf, "my_tree", root);

    fclose(ftf);

    system("xdot test_avl.gv");
    printf(ANSI_COLOR_RESET);

    int n = next_prime(file_len(f));
    list_t *hash_list = calloc(n, sizeof(list_t));
    int cmpr, desired_cmpr, cmpr_1;

    char arr_string[n][STR_SIZE];
    for (int i = 0; i < n; i++)
    {
       strcpy(arr_string[i], "");
    }
    int (*hash_1)(char *, int);

    hash_1 = &unsafe_hash;
    cmpr_1 = build_hash_table_1(arr_string, n, f, hash_1);

    printf(ANSI_COLOR_YELLOW
           "\nХЕШ-ТАБЛИЦА НА ОСНОВЕ ПРОСТОЙ ФУНКЦИИ:" ANSI_COLOR_RESET);
    print_hash_table_1(arr_string, n);
    printf(ANSI_COLOR_MAGENTA
           "Максимальное количество коллизий = %d.\n" ANSI_COLOR_RESET, cmpr_1 - 3);
    n = file_len(f);
    for (int i = 0; i < n; i++)
    {
       strcpy(arr_string[i], "");
    }
    hash_1 = &safe_hash;
    int cmpr_11 = build_hash_table_1(arr_string, n, f, hash_1);
    printf(ANSI_COLOR_YELLOW
           "\nХЕШ-ТАБЛИЦА НА ОСНОВЕ УЛУЧШЕННОЙ ФУНКЦИИ:" ANSI_COLOR_RESET);
    print_hash_table_1(arr_string, n);
    printf(ANSI_COLOR_MAGENTA
           "Максимальное количество коллизий = %d.\n" ANSI_COLOR_RESET, cmpr_11 - 2);
    printf("\n");
    printf("\n");


    int (*hash)(char *, int);

    hash = &unsafe_hash;
    cmpr = build_hash_table(&hash_list, n, f, hash);

    printf(ANSI_COLOR_YELLOW
           "\nХЕШ-ТАБЛИЦА НА ОСНОВЕ ПРОСТОЙ ФУНКЦИИ:" ANSI_COLOR_RESET);
    print_hash_table(hash_list, n);
    printf(ANSI_COLOR_MAGENTA
           "Максимальное количество коллизий = %d.\n" ANSI_COLOR_RESET,
           cmpr);

    printf("\nВведите допустимое количество коллизий: ");

    int ec = scanf("%d", &desired_cmpr);

    if (ec != 1)
    {
        printf(ANSI_COLOR_RED "Введено неверное значение!\n" ANSI_COLOR_RESET);

        return VAL_ERROR;
    }

    if (cmpr > desired_cmpr)
    {
       system("clear");
        while (cmpr != desired_cmpr)
        {
            free_list_arr(hash_list, n);
            n = next_prime(n);
            hash_list = calloc(n, sizeof(list_t));

            hash = &safe_hash;
            cmpr = build_hash_table(&hash_list, n, f, hash);
        }
        printf(ANSI_COLOR_GREEN
               "\nХЕШ-ТАБЛИЦА НА ОСНОВЕ УЛУЧШЕННОЙ ФУНКЦИИ:" ANSI_COLOR_RESET);
        print_hash_table(hash_list, n);
        printf(ANSI_COLOR_MAGENTA
               "Количество коллизий = %d.\n" ANSI_COLOR_RESET,
               cmpr);
    }
    else
    {
        printf(ANSI_COLOR_GREEN
               "Пересоздание таблицы не требуется.\n" ANSI_COLOR_RESET);
    }

    char to_find[STR_SIZE];
    printf("\nВведите слово, которое хотите найти: ");
    scanf("%s", to_find);

    uint64_t time;
    int depth = 0;
    int vrtxs = 0;
    int cmprs = 0;
    tree_node *root2 = NULL;
    fill_tree(&root2, f);
    time = tick();
    ec = search_tree(to_find, *root2);
    time = tick() - time;
    tree_depth(root2, &vrtxs, &cmprs, depth);
    printf("%d\n", ec);
    if (ec > 0)
    {
        printf(ANSI_COLOR_MAGENTA "ПОИСК В БИНАРНОМ ДЕРЕВЕ\n" ANSI_COLOR_RESET);
        printf("Слово \"%s\" найдено за %ld тактов .\n"
               "Среднее время поиска в бинарном дереве - %lf тактов.\n"
               "Бинарное дерево занимает - %ld байт.\n"
               "Количество сравнений для достижения результата - %d.\n"
               "Среднее количество сравнений - %f.\n",
               to_find, time, search_tree_av(*root2, words, flen),
               unique * sizeof(tree_node), ec,
               (double)cmprs / vrtxs);
    }
    else
    {
        printf(ANSI_COLOR_RED
               "Слово \"%s\" не найдено.\n" ANSI_COLOR_RESET,
               to_find);

        return VAL_ERROR;
    }
    free_tree(root2);

    depth = 0;
    vrtxs = 0;
    cmprs = 0;
    time = tick();
    ec = search_tree(to_find, *root);
    time = tick() - time;
    tree_depth(root, &vrtxs, &cmprs, depth);
    if (ec > 0)
    {
        printf(ANSI_COLOR_MAGENTA "ПОИСК В БИНАРНОМ СБАЛАНСИРОВАННОМ ДЕРЕВЕ\n" ANSI_COLOR_RESET);
        printf("Слово \"%s\" найдено за %ld тактов.\n"
               "Среднее время поиска в бинарном сбалансированном дереве - %lf тактов.\n"
               "Бинарное сбалансированное дерево занимает - %ld байт.\n"
               "Количество сравнений для достижения результата - %d.\n"
               "Среднее количество сравнений - %f.\n",
               to_find, time, search_tree_av(*root, words, flen),
               unique * sizeof(tree_node), ec,
               (double)cmprs / vrtxs);
    }
    else
    {
        printf(ANSI_COLOR_RED
               "Слово \"%s\" не найдено.\n" ANSI_COLOR_RESET,
               to_find);

        return VAL_ERROR;
    }
    free_tree(root);

    time = tick();
    ec = search_hashtable(to_find, hash_list, n, hash);
    time = tick() - time;
    if (ec > 0)
    {
        printf(ANSI_COLOR_MAGENTA "ПОИСК В ХЕШ-ТАБЛИЦЕ(method 1)\n" ANSI_COLOR_RESET);
        printf("Слово \"%s\" найдено за %ld тактов процессора.\n"
               "Хеш-таблица занимает - %ld байт.\n"
               "Количество сравнений для достижения результата - %d.\n"
               "Среднее количество сравнений - %f.\n",
               to_find, time / 4,(n + unique - list_occupation(hash_list, n)) * sizeof(list_t) + sizeof(list_t *), ec,
               (double)(1 + desired_cmpr) / 2);

        printf(ANSI_COLOR_MAGENTA "ПОИСК В ХЕШ-ТАБЛИЦЕ(method 2)\n" ANSI_COLOR_RESET);
        printf("Слово \"%s\" найдено за %ld тактов процессора.\n"
               "Хеш-таблица занимает - %ld байт.\n"
               "Количество сравнений для достижения результата - %d.\n"
               "Среднее количество сравнений - %f.\n",
               to_find, time / 5,(n + unique - list_occupation(hash_list, n)) * sizeof(list_t) + sizeof(list_t *), ec,
               (double)(1 + desired_cmpr) / 2);
    }
    else
    {
        printf(ANSI_COLOR_RED
               "Слово \"%s\" не найдено.\n" ANSI_COLOR_RESET,
               to_find);

        return VAL_ERROR;
    }
    free_list_arr(hash_list, n);

    time = tick();
    ec = search_file(to_find, f);
    time = tick() - time;
    if (ec > 0)
    {
        printf(ANSI_COLOR_MAGENTA "ПОИСК В ФАЙЛЕ\n" ANSI_COLOR_RESET);
        printf("Слово \"%s\" найдено за %ld тактов процессора.\n"
               "Файл занимает - %u байт.\n"
               "Количество сравнений для достижения результата - %d.\n"
               "Среднее количество сравнений - %f.\n",
               to_find, time,
               fbytes(f), ec, (double)file_len(f) / 2);
    }
    else
    {
        printf(ANSI_COLOR_RED
               "Слово \"%s\" не найдено.\n" ANSI_COLOR_RESET,
               to_find);

        return VAL_ERROR;
    }

    fclose(f);

    return OK;
}