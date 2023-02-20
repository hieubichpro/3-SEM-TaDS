#include "../inc/menu.h"
#include "../inc/array.h"
#include "../inc/list.h"
#include "../inc/sort_arr.h"
#include "../inc/sort_list.h"
#include "../inc/analys.h"

int main()
{
    int act = EXIT_SUCCESS;
    int rc;
    arr_stack_t st_1;
    arr_stack_t st_2;
    arr_stack_t res;
    freed_t list;
    list.index = 0;
    init_arr(&st_1);
    init_arr(&st_2);
    init_arr(&res);
    int item;
    int cnt1 = 0, cnt2 = 0;


    list_stack_t *ptr_1 = NULL;
    list_stack_t *ptr_2 = NULL;
    list_stack_t *ptr_res = NULL;
    char mood = 'a';
    while (act != EXIT)
    {
        if ((rc = choose_action(&act)))
            return rc;
        if (act == CREATE)
        {
            if ((rc = choose_stack_type(&act)))
                return rc;
            if (act == ARR_TYPE)
            {
                mood = 'a';
                printf("\nВведите элементы первого стека: ");
                if ((rc = read_arr(&st_1)))
                    return rc;
                printf("\nВведите элементы второго стека: ");
                if ((rc = read_arr(&st_2)))
                    return rc;
                int cnt1_arr = st_1.ptr - st_1.a + 1;
                int cnt2_arr = st_2.ptr - st_2.a + 1;
                if (cnt1_arr + cnt2_arr > MAX_SIZE)
                {
                    printf("Невозможно добавить элемент в стек: Переполнение");
                    return ERR_FULL_ARR_STACK;
                }
                init_arr(&res);
            }
            else
            {
                mood = 'l';
                printf("\nВведите элементы первого стека: ");
                if ((rc = read_list(&ptr_1, &cnt1)))
                    return rc;
                printf("\nВведите элементы второго стека: ");
                if ((rc = read_list(&ptr_2, &cnt2)))
                    return rc;
                if (cnt1 + cnt2 > MAX_SIZE)
                {
                    printf("Невозможно добавить элемент в стек: Переполнение");
                    return ERR_FULL_ARR_STACK;
                }
                ptr_res = NULL;
            }
        }
        if (act == PRINT)
        {
            if (mood == 'a')
            {
                printf("\nПервый стек: ");
                print_arr(&st_1);
                printf("\nВторой стек: ");
                print_arr(&st_2);
            }
            else
            {
                printf("\nПервый стек:\n");
                print_list(ptr_1, &cnt1);
                printf("\nВторой стек:\n");
                print_list(ptr_2, &cnt2);
                printf("\n\nСвободные области: ");
                if (list.index == 0)
                    printf("отсутвуют.\n\n");
                else
                {
                    printf("\n\ncount┏━━━━━━━━━━━━━━━━┓\n");
                    for (int i = 0; i < list.index; i++)
                    {
                        printf("%-5d┃%-16p┃\n", i + 1, (void*)list.a[i]);
                        if (i != (list.index - 1))
                            printf("     ┣━━━━━━━━━━━━━━━━┫\n");
                    }
                    printf("     ┗━━━━━━━━━━━━━━━━┛\n");   
                }
            }
        }
        if (act == SORT)
        {
            if (mood == 'a')
            {
                if (res.ptr >= res.a)
                    print_arr(&res);
                else if (!sort_arr(&st_1, &st_2, &res))
                {
                    printf("Отсортированные введенные данные:\n");
                    print_arr(&res);
                }
            }
            else
            {
                int cnt_res = cnt1 + cnt2;
                if (ptr_res)
                    print_list(ptr_res, &cnt_res);
                else if (!sort_list(&ptr_1, &ptr_2, &ptr_res, &cnt1, &cnt2, &cnt_res, &list))
                {
                    printf("Отсортированные введенные данные:\n");
                    print_list(ptr_res, &cnt_res);
                }
            }
        }
        if (act == POP)
        {
            if (mood == 'a')
            {
                if ((rc = choose_stack(&act)))
                    return rc;
                if (act == FIRST_ST && (rc = pop_arr(&st_1, &item)))
                {
                    printf("Невозможно произвести удаление: стек пуст.");
                    return rc;
                }
                if (act == SECOND_ST && (rc = pop_arr(&st_2, &item)))
                {
                    printf("Невозможно произвести удаление: стек пуст.");
                    return rc;
                }
            }
            else
            {
                if ((rc = choose_stack(&act)))
                    return rc;
                if (act == FIRST_ST && (rc = pop_list_with_freed(&ptr_1, &item, &list, &cnt1)))
                {
                    printf("Невозможно произвести удаление: стек пуст.");
                    return rc;
                }
                if (act == SECOND_ST && (rc = pop_list_with_freed(&ptr_2, &item, &list, &cnt2)))
                {
                    printf("Невозможно произвести удаление: стек пуст.");
                    return rc;
                }
            }
            printf("\nПоследний элемент со значением %d успешно удален из стека.\n", item);
            if (mood == 'l')
            {
                printf("\n\nСвободные области: ");
                if (list.index == 0)
                    printf("отсутвуют.\n\n");
                else
                {
                    printf("\n\ncount┏━━━━━━━━━━━━━━━━┓\n");
                    for (int i = 0; i < list.index; i++)
                    {
                        printf("%-5d┃%-16p┃\n", i + 1, (void*)list.a[i]);
                        if (i != (list.index - 1))
                            printf("     ┣━━━━━━━━━━━━━━━━┫\n");
                    }
                    printf("     ┗━━━━━━━━━━━━━━━━┛\n");   
                }
            }
        }
        if (act == PUSH)
        {
            printf("\nВведите элемент: ");
            if ((rc = get_item(&item)))
                return rc;
            if (mood == 'a')
            {
                if ((rc = choose_stack(&act)))
                    return rc;
                if (act == FIRST_ST)
                {
                    rc = push_arr(&st_1, item);
                    if (rc)
                    {
                        printf("Невозможно добавить элемент в стек: Переполнение.\n\n");
                        return rc;
                    }
                }
                else
                {
                    rc = push_arr(&st_2, item);
                    if (rc)
                    {
                        printf("Невозможно добавить элемент в стек: Переполнение.\n\n");
                        return rc;
                    }
                }
                int cnt1_arr = st_1.ptr - st_1.a + 1;
                int cnt2_arr = st_2.ptr - st_2.a + 1;
                if (cnt1_arr + cnt2_arr > MAX_SIZE)
                {
                    printf("Невозможно добавить элемент в стек: Переполнение");
                    return ERR_FULL_ARR_STACK;
                }
            }
            else
            {
                if ((rc = choose_stack(&act)))
                    return rc;
                if (act == FIRST_ST)
                {
                    rc = push_list_with_freed(&ptr_1, item, &list, &cnt1);
                    if (rc)
                    {
                        printf("Невозможно добавить элемент в стек: Переполнение.\n\n");
                        return rc;
                    }
                }
                else
                {
                    rc = push_list_with_freed(&ptr_2, item, &list, &cnt2);
                    if (rc)
                    {
                        printf("Невозможно добавить элемент в стек: Переполнение.\n\n");
                        return rc;
                    }
                }
                if (cnt1 + cnt2 > MAX_SIZE)
                {
                    printf("Невозможно добавить элемент в стек: Переполнение");
                    return ERR_FULL_ARR_STACK;
                }
            }
            printf("\nЭлемент со значением %d успешно добавлен в конец стека.\n", item);
        }
        if (act == ANALYS)
            analys();
    }
    return EXIT_SUCCESS;
}