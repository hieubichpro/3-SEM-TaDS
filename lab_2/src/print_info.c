#include <stdio.h>
#include <stdlib.h>
#include "print_info.h"

void print_string(flat_t flat)
{
    printf("%-20s | %7d | %6d | %6d |  %5d | ", flat.address, flat.square, flat.rooms, flat.one_m_cost, flat.is_primary);

    if (flat.is_primary == 1)
    {
        if (flat.flat.primary.decorated == 1)
        {
            printf("   Да   |   --   |     --    |   --   |     --   \n");
        }
        else if (flat.flat.primary.decorated == 0)
        {
            printf("   Нет  |   --   |     --    |   --   |     --   \n");
        }
    }
    else if (flat.is_primary == 2)
    {
        printf("   --   | %6d | %9d | %6d |", flat.flat.secondary.build_year, flat.flat.secondary.previous_owners, flat.flat.secondary.previous_rezidents);

        if (flat.flat.secondary.animals == 1)
        {
            puts("    Да   ");
        }
        else if (flat.flat.secondary.animals == 0)
        {
            puts("    Нет   ");
        }
    }
}

void print_table(table_t table)
{
    system("clear");
    int size = table.size;

    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }

    flat_t *flats_arr = table.flats_arr;

    puts("    Адресс (город)   | Площадь | Комнат |  Цена  |  Класс | Отделка |  Год   | Владельцы | Жильцы | Животные");
    puts("--------------------------------------------------------------------------------------------------------------");

    for (int i = 0; i < size; i++)
    {
        print_string(flats_arr[i]);
    }
}

void print_table_keys(table_t table)
{
    system("clear");
    int size = table.size;

    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }

    keys_t *keys = table.keys;

    puts("    Таблица ключей");

    for (int i = 0; i < size; i++)
    {
        printf("Номер: %3d  | Площадь: %9d  \n", keys[i].id, keys[i].square);
    }
}

void print_table_by_keys(table_t table)
{
    system("clear");
    if (table.size == 0)
    {
        puts("Таблица пустая");
        return;
    }

    puts("    Адресс (город)   | Площадь | Комнат |  Цена  |  Класс | Отделка |  Год   | Владельцы | Жильцы | Животные");

    puts("--------------------------------------------------------------------------------------------------------------");
    for (int i = 0; i < table.size; i++)
    {
        print_string(table.flats_arr[table.keys[i].id]);
    }
}

int search(table_t table)
{
    system("clear");
    if (table.size == 0)
    {
        puts("Таблица пустая");
        return OK_SEARCH;
    }

    int st, end;

    puts("Введите левую границу цены (не меньше 1):");
    int rc = scanf("%d", &st);
    if (rc != 1)
    {
        puts("Invalid input left range");
        return ERR_START_COST;
    }
    while (st < 1)
    {
        puts("Ошибка: неверно введена левая граница");
        printf("Введите левую границу цены (не меньше 1): ");
        rc = scanf("%d", &st);
    }

    puts("\n\nВведите правая границу цены:");
    rc = scanf("%d", &end);
    if (rc != 1)
    {
        puts("Invalid value right range");
        return ERR_END_COST;
    }
    while (end < 1 || end < st)
    {
        puts("Ошибка: неверно введена конечная цена");
        printf("Введите правая границу цены: ");
        rc = scanf("%d", &end);
    }

    int check = 0;

    for (int i = 0; i < table.size; i++)
    {
        if ((table.flats_arr[i].rooms == 2) && (table.flats_arr[i].is_primary == 2) && (table.flats_arr[i].flat.secondary.animals == 0) && (table.flats_arr[i].one_m_cost >= st) && (table.flats_arr[i].one_m_cost <= end))
        {
            if (check == 0)
            {
                puts("\n\n    Адресс (город)   | Площадь | Комнат |  Цена  |  Класс | Отделка |  Год   | Владельцы | Жильцы | Животные");

                puts("--------------------------------------------------------------------------------------------------------------");
            }

            print_string(table.flats_arr[table.keys[i].id]);

            check = 1;
        }
    }

    if (check == 0)
    {
        puts("\n\nНичего не было найдено по заданным границам цены");
    }

    return OK_SEARCH;
}
