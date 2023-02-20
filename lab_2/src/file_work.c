#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "print_info.h"
#include "file_work.h"

int check_clear(FILE *f)
{
    if (fseek(f, 0, SEEK_END) != 0)
    {
        return ERR_FILE_CLEAR;
    }

    size_t current_size = ftell(f);

    if (current_size <= 0)
    {
        return ERR_FILE_CLEAR;
    }

    return fseek(f, 0, SEEK_SET);
}

int read_file(FILE *f, flat_t *flats_arr, int *size, keys_t *keys)
{
    int num_flat = *size;
    int rc = 0;
    if (check_clear(f) != 0)
    {
        puts("Ошибка: файл пустой");
        return ERR_FILE_CLEAR;
    }

    while (!feof(f))
    {
        // Порядок
        // адрес площадь количество_комнат стоимость первичное : отделка или без неё
        //                                           вторичное :  время_постройки кол_совственников кол_жильцов животные
        rc = fscanf(f, "%100s %d %d %d %d", flats_arr[num_flat].address, &flats_arr[num_flat].square, &flats_arr[num_flat].rooms, &flats_arr[num_flat].one_m_cost, &flats_arr[num_flat].is_primary);

        keys[num_flat].square = flats_arr[num_flat].square;
        keys[num_flat].id = num_flat;

        if (rc != 5)
        {
            puts("Ошибка: ошибочная запись в файле");
            return ERR_ELEMENTS;
        }

        if (flats_arr[num_flat].is_primary == 1)
        {
            primary_t type;
            rc = fscanf(f, "%d", &type.decorated);

            if (rc != 1)
            {
                puts("Ошибка: ошибочная запись в файле");
                return ERR_ELEMENTS;
            }

            flats_arr[num_flat].flat.primary = type;
        }
        else if (flats_arr[num_flat].is_primary == 2)
        {
            secondaray_t type;

            rc = fscanf(f, "%d %d %d %d", &type.build_year, &type.previous_owners, &type.previous_rezidents, &type.animals);

            if (rc != 4)
            {
                printf("Ошибка: ошибочная запись в файле");
                return ERR_ELEMENTS;
            }

            flats_arr[num_flat].flat.secondary = type;
        }
        num_flat++;

        if (num_flat > MAX_SIZE)
        {
            puts("Ошибка: количество записей слишком большое");
            return ERR_TOO_MUCH_FLATS;
        }
    }

    fseek(f, 0, SEEK_SET);

    *size = num_flat;

    return OK_READ;
}

int add_flat(flat_t *flats_arr, int *size, keys_t *keys)
{
    flat_t new_flat;

    system("clear");

    puts("\nВведите город (не более 100 символов, разделитель _):");
    int rc = scanf("%s", new_flat.address);
    while (rc != 1)
    {
        puts("Ошибка: неверно введён город");
        rc = scanf("%s", new_flat.address);
    }

    puts("\nВведите площадь квартиры (от 1 до 100000):");
    rc = scanf("%d", &new_flat.square);
    if (rc != 1)
    {
        puts("Square must be number");
        return ERR_SQUARE_INPUT;
    }
    while ((new_flat.square < 1) || (new_flat.square > 100000))
    {
        puts("Ошибка: неверно введена площадь квартиры");
        printf("Введите еще раз: ");
        rc = scanf("%d", &new_flat.square);
    }

    puts("\nВведите количество комнат (от 1 до 100):");
    rc = scanf("%d", &new_flat.rooms);
    if (rc != 1)
    {
        puts("Room must be number");
        return ERR_ROOMS_INPUT;
    }
    while ((new_flat.rooms < 1) || (new_flat.rooms > 100))
    {
        puts("Ошибка: неверно введено количество комнат");
        rc = scanf("%d", &new_flat.rooms);
    }

    puts("\nВведите цену за один квадратный метр квартиры (от 1 до 1000000):");
    rc = scanf("%d", &new_flat.one_m_cost);
    if (rc != 1)
    {
        puts("One_m_cost must be number");
        return ERR_COST_INPUT;
    }
    while ((new_flat.one_m_cost < 1) || (new_flat.one_m_cost > 1000000))
    {
        puts("Ошибка: неверно введена цена за 1 квадртатный метр");
        rc = scanf("%d", &new_flat.one_m_cost);
    }

    puts("\nВведите тип квартиры: 1 - первичная, 2 - вторичная:");
    rc = scanf("%d", &new_flat.is_primary);
    if (rc != 1)
    {
        puts("Type of flat must be number");
        return ERR_TYPE_INPUT;
    }
    while ((new_flat.is_primary < 1) || (new_flat.is_primary > 2))
    {
        puts("Ошибка: неверно введен класс квартиры");
        rc = scanf("%d", &new_flat.is_primary);
    }

    if (new_flat.is_primary == 1)
    {
        puts("\nЕсть ли украшение? (1 - да, 0 - нет):");
        rc = scanf("%d", &new_flat.flat.primary.decorated);
        if (rc != 1)
        {
            puts("Decor must be number");
            return ERR_DECOR_INPUT;
        }
        while ((new_flat.flat.primary.decorated < 0) || (new_flat.flat.primary.decorated > 1))
        {
            puts("Ошибка: неверно введена информация о украшении");
            rc = scanf("%d", &new_flat.flat.primary.decorated);
        }
    }
    else if (new_flat.is_primary == 2)
    {
        puts("\nВведите год постройки (от 1900 до 2022):");
        rc = scanf("%d", &new_flat.flat.secondary.build_year);
        if (rc != 1)
        {
            puts("Year must be number");
            return ERR_YEAR_INPUT;
        }
        while ((new_flat.flat.secondary.build_year < 1900) || (new_flat.flat.secondary.build_year > 2022))
        {
            puts("Ошибка: неверно введён год постройки");
            rc = scanf("%d", &new_flat.flat.secondary.build_year);
        }

        puts("\nВведите количество прошлых совственников (от 1 до 200):");
        rc = scanf("%d", &new_flat.flat.secondary.previous_owners);
        if (rc != 1)
        {
            puts("Num of owners must be number");
            return ERR_OWNER_INPUT;
        }
        while ((new_flat.flat.secondary.previous_owners < 1) || (new_flat.flat.secondary.previous_owners > 200))
        {
            puts("Ошибка: неверно введено количество прошлых совственников");
            rc = scanf("%d", &new_flat.flat.secondary.previous_owners);
        }

        puts("\nВведите количество прошлых жильцов (от 1 до 1000):");
        rc = scanf("%d", &new_flat.flat.secondary.previous_rezidents);
        if (rc != 1)
        {
            puts("Residents must be number");
            return ERR_RESIDENT_INPUT;
        }
        while ((new_flat.flat.secondary.previous_rezidents < 1) || (new_flat.flat.secondary.previous_rezidents > 1000))
        {
            puts("Ошибка: неверно введено количество прошлых жильцов");
            rc = scanf("%d", &new_flat.flat.secondary.previous_rezidents);
        }

        puts("\nЖивотные были в квартире? (1 - да, 0 - нет):");
        rc = scanf("%d", &new_flat.flat.secondary.animals);
        if (rc != 1)
        {
            puts("Yes/no animal must be number");
            return ERR_ANIMAL_INPUT;
        }
        while ((new_flat.flat.secondary.animals < 0) || (new_flat.flat.secondary.animals > 1))
        {
            puts("Ошибка: неверно введено наличие животного");
            rc = scanf("%d", &new_flat.flat.secondary.animals);
        }
    }

    *size += 1;

    if (*size > MAX_SIZE)
    {
        puts("Ошибка: количество записей переполнено");
        return ERR_TOO_MUCH_FLATS;
    }

    keys[*size - 1].square = new_flat.square;
    keys[*size - 1].id = *size - 1;

    flats_arr[*size - 1] = new_flat;

    puts("\nДатасет была успешно добавлена\n");
    return OK_ADDING;
}

void swap_flats(flat_t *flats_arr, int i, int j)
{
    flat_t tmp;

    tmp = flats_arr[i];
    flats_arr[i] = flats_arr[j];
    flats_arr[j] = tmp;
}

void swap_keys(keys_t *keys, int i, int j)
{
    keys_t tmp;

    tmp = keys[i];
    keys[i] = keys[j];
    keys[j] = tmp;
}

void del_by_pos(flat_t *flats_arr, keys_t *keys, int size, int pos)
{
    for (int i = pos; i < size; i++)
    {
        swap_flats(flats_arr, i, i + 1);
    }

    for (int i = pos; i < size; i++)
    {
        swap_keys(keys, i, i + 1);
        keys[i].id -= 1;
    }
}

int delete_by_square(flat_t *flats_arr, int *size, keys_t *keys)
{
    system("clear");
    if (*size == 0)
    {
        puts("\nТаблица пустая\n");
        return OK_DEL;
    }
    puts("Введите значение площади, по которому будут удалены квартиры с такой площадью:");

    int val_square;
    int rc = scanf("%d", &val_square);
    int size_arr = *size;

    if ((rc != 1) || (val_square < 1) || (val_square > 100000))
    {
        puts("Ошибка: неверно введена площадь");
        return ERR_SQUARE_INPUT;
    }

    for (int i = 0; i < size_arr; i++)
    {
        if (flats_arr[i].square == val_square)
        {
            del_by_pos(flats_arr, keys, *size, i);
            *size -= 1;
        }
    }

    if (*size == size_arr)
    {
        puts("\nНе найдены квартиры с такой площадью\n");
    }
    else
    {
        puts("\nУспешно удалены квартиры из таблицы\n");
    }

    return OK_DEL;
}
