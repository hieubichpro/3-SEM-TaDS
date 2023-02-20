#include "../inc/array.h"

int read_arr(arr_stack_t *st)
{
    init_arr(st);
    int item, rc = EXIT_SUCCESS;
    char ch = 'i';
    while (ch != '\n')
    {
        if ((rc = get_item(&item)))
            return rc;
        if ((rc = push_arr(st, item)))
        {
            // printf("rc = %d", rc);
            printf("Невозможно добавить элемент в стек: Переполнение.\n\n");
            return rc;
        }
        ch = getchar();
    }
    printf("\nЭлементы успешно введены.\n");
    return EXIT_SUCCESS;
}

int push_arr(arr_stack_t *st, int item)
{
    if ((st->ptr + 1) >= st->a + MAX_SIZE)
        return ERR_FULL_ARR_STACK;
    //printf("%ld ", st->ptr - st->a + 1);
    st->ptr++;
    *(st->ptr) = item;
    return EXIT_SUCCESS;
}

int pop_arr(arr_stack_t *st, int *item)
{
    if ((st->a - 1) == st->ptr)
        return ERR_EMPTY_ARR_STACK;
    *item = *st->ptr;
    st->ptr--;
    return EXIT_SUCCESS;
}

void print_arr(arr_stack_t *st)
{
    if ((st->a - 1) == st->ptr)
        printf("Стек пуст.");
    else
    {
        arr_stack_t buf;
        init_arr(&buf);
        int n = st->ptr - st->a + 1;
        int item;
        printf("\n┏━━━━━━━━━━━━━━┓\n");
        for (int i = 0; i < n; i++)
        {
            pop_arr(st, &item);
            printf("┃%14d┃\n", item);
            if (i != (n - 1))
                printf("┣━━━━━━━━━━━━━━┫\n");
            push_arr(&buf, item);
        }
        for (int i = 0; i < n; i++)
        {
            pop_arr(&buf, &item);
            push_arr(st, item);
        }
        printf("┗━━━━━━━━━━━━━━┛\n");
    }
    printf("\n");
}

void init_arr(arr_stack_t *st)
{
    st->ptr = st->a - 1;
}

int get_item(int *item)
{
    if (scanf("%d", item) != 1)
    {
        printf("\nОшибка ввода элемента стека: должно быть введено целое число.\n\n");
        return ERR_READ;
    }
    return EXIT_SUCCESS;
}
