#include "../inc/menu.h"

int choose_action(int *act)
{
    printf("\n        МЕНЮ     \n\n1) Ввести целые числа в 2 стека\n2) Вывести элементы стеков\n"
        "3) Отсортировать все введенные данные\n4) Удалить последний элемент стека\n"
        "5) Добавить элемент в конец стека\n6) Сравнительный анализ алгоритмов\n"
        "0) Выход\n\nКакой пункт: ");
    if (scanf("%d", act) != 1 || (*act != CREATE && *act != PRINT && *act != SORT &&
        *act != ANALYS && *act != POP && *act != PUSH && *act != EXIT)
        || getchar() != '\n')
    {
        printf("\nОшибка: номер пункта должно быть в интервале [0, 6].\n");
        return ERR_ACT;
    }
    return EXIT_SUCCESS;
}

int choose_stack(int *act)
{
    printf("\nВыберите стек для выполнения операции:\n\n1) Первый\n2) Второй\n\nВаш ответ: ");
    if (scanf("%d", act) != 1 || (*act != 1 && *act != 2) || getchar() != '\n')
    {
        printf("\nОшибка: Следуйте инструкциям на экране.\n");
        return ERR_ACT;    
    }
    *act += 10;
    return EXIT_SUCCESS;
}

int choose_stack_type(int *act)
{
    printf("\nВыберите тип организации стеков:\n\n1) В виде массива\n2) В виде списка\n\nВаш ответ: ");
    if (scanf("%d", act) != 1 || (*act != 1 && *act != 2))
    {
        printf("\nОшибка: команда должна быть одним из чисел, предложенных в меню.\n");
        return ERR_ACT;
    }
    *act += 8;
    return EXIT_SUCCESS;
}