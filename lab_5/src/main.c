#include"../inc/structs.h"
#include"../inc/arr_queue.h"
#include"../inc/list_queue.h"
#include"../inc/print_info.h"
#include"../inc/time_count.h"

#define ERR_UNRIGHT_op -1


int get_random_num(void)
{
    srand(time(NULL));
    return rand() % 100 + 1;
}


int main(void)
{
    int op = -1;
    int rc = 0;

    arr_t queue_arr;
    init_arr_queue(&queue_arr);

    list_t queue_list;
    init_list_queue(&queue_list);

    arr_clear_t clear_arr = {.len = 0};

    while (op != 0)
    {
        print_menu();

        rc = scanf("%d", &op);

        if ((rc != 1) || (op < 0) || (op > 10))
        {
            puts("Ошибка: Неверно введен пункт");
            return ERR_UNRIGHT_op;
        }

        if (op == 1)
        {
            int num = get_random_num();

            if (!owerflow_arr_queue(queue_arr))
            {
                printf("Добавлено \"%d\"\n", num);
                push_arr_queue(&queue_arr, num);
            }
            else
                printf("Ошибка: Очередь переполнена\n\n");
        }
        
        if (op == 2)
        {
            if (!clear_check_arr_queue(queue_arr))
            {
                int num = pop_arr_queue(&queue_arr);
                printf("Удалено \"%d\"\n", num);
            }
            else
                printf("Очередь пуста\n");
        }

        if (op == 3)
            print_arr_queue(queue_arr);

        if (op == 4)
        {
            int num = get_random_num();
            push_list_queue(&queue_list, num);
            del_adress(&clear_arr, &queue_list);
            printf("Добавлен \"%d\"\n", num);
        }
        
        if (op == 5)
        {
            if (!clear_check_list(queue_list))
            {
                add_adress(&clear_arr, &queue_list);
                int num = pop_list_queue(&queue_list);
                printf("Удален элемент \"%d\" \n", num);
            }
            else
                printf("Очередь пуста\n");
        }

        if (op == 6)
            print_list_queue(queue_list);

        if (op == 7)
            print_arr_adress(clear_arr);

        if (op == 8)
            task_arr();

        if (op == 9)
            task_list();

        if (op == 10)
            analys();
    }

    return EXIT_SUCCESS;
}