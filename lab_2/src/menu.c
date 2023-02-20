#include "menu.h"

void print_menu(void)
{
    puts("\n\n       МЕНЮ\n");

    puts("1. Загрузить список квартир из файла");
    puts("2. Добавить квартиру в конец списка");
    puts("3. Удалить квартиры по значению площади");
    puts("4. Найти все 2-х вторичное жильё без живтотных в указанном ценовом диапазоне");
    puts("5. Отсортировать таблицу пузырьком");
    puts("6. Отсортировать таблицу ключей пузырьком");
    puts("7. Отсортировать таблицу qsort");
    puts("8. Отсортировать таблицу ключей qsort");
    puts("9. Вывести сравнение сортировок пузырьком и qsort");
    puts("10. Вывести таблицу");
    puts("11. Вывести таблицу по таблице ключей");
    puts("12. Вывести таблицу ключей");
    puts("13. Очистить таблицу");
    puts("\n 0 - выйти из программы \n\n");

    printf("Введите пункт меню: ");
}

int option_menu(void)
{
    int option = -1;

    int rc = 0;

    flat_t flats_arr[MAX_FLATS];

    table_t table = {.maxsize = MAX_FLATS, .size = 0};

    keys_t keys[MAX_FLATS];

    while (option != 0)
    {
        print_menu();

        rc = scanf("%d", &option);
        if (rc != 1)
        {
            puts("ERR OPTION TYPE");
            return ERR_OPTION_TYPE;
        }
        while ((option < 0) || (option > 13))
        {
            puts("Ошибка: пункт меню должно быть в интервале [0, 13]");
            printf("Введите пункт меню еще раз: ");
            rc = scanf("%d", &option);
        }

        // чтенте даты из файла
        if (option == 1)
        {
            char file[MAX_SIZE];

            printf("Введите имя файла: ");
            if (scanf("%s", file) != 1)
            {
                puts("Ошибка: нет такого файла");
                return ERR_NO_SUCH_FILE;
            }

            FILE *f = fopen(file, "r");

            if (f == NULL)
            {
                puts("Ошибка: нет такого файла");
                return ERR_OPEN_FILE;
            }

            int size = table.size;

            rc = read_file(f, flats_arr, &size, keys);

            if (rc != 0)
            {
                return rc;
            }

            table.size = size;
            table.keys = keys;
            table.flats_arr = flats_arr;

            fclose(f);

            puts("Чтение успешно");
        }

        // Добавить квартиру в конец списка
        else if (option == 2)
        {
            int size = table.size;

            rc = add_flat(flats_arr, &size, keys);

            if (rc != 0)
            {
                return rc;
            }

            table.size = size;
            table.keys = keys;
            table.flats_arr = flats_arr;
        }

        // Удалить квартиру по площади
        else if (option == 3)
        {
            int size = table.size;

            rc = delete_by_square(flats_arr, &size, keys);

            if (rc != 0)
            {
                return rc;
            }

            table.size = size;
            table.keys = keys;
            table.flats_arr = flats_arr;
        }

        // Найти квартиру по указанному условию
        else if (option == 4)
        {
            rc = search(table);

            if (rc != 0)
            {
                return rc;
            }
        }

        // Сортировать методом пузырька
        else if (option == 5)
        {
            bubble_table(table);
        }

        // Сортировать ключей методом пузырька
        else if (option == 6)
        {
            bubble_table_keys(table);
        }

        // Сортировать методом быстрой сортировки
        else if (option == 7)
        {
            qsort_table(table);
        }

        // Сортировать ключей методом быстрой сортировки
        else if (option == 8)
        {
            qsort_table_keys(table);
        }

        // Сравнение методов сортировки
        else if (option == 9)
        {
            char file[MAX_SIZE];

            printf("Введите имя файла: ");
            if (scanf("%s", file) != 1)
            {
                puts("Ошибка: Нет такого файла");
                return ERR_NO_SUCH_FILE;
            }

            FILE *f = fopen(file, "r");

            if (f == NULL)
            {
                puts("Ошибка: Нет такого файла");
                return ERR_OPEN_FILE;
            }

            rc = compare_sorts(f);

            if (rc != 0)
            {
                puts("Ошибка: неверные записи в файле");
                return ERR_OPEN_FILE;
            }

            fclose(f);
        }

        // Вывести таблицу
        else if (option == 10)
        {
            print_table(table);
        }

        // Вывести таблицу по таблице ключей
        else if (option == 11)
        {
            print_table_by_keys(table);
        }

        // Вывести таблицу ключей
        else if (option == 12)
        {
            print_table_keys(table);
        }

        // Очистить таблицу
        else if (option == 13)
        {
            system("clear");
            table.size = 0;
            puts("Таблица успешно очищена\n");
        }
    }
    system("clear");
    return OK;
}
