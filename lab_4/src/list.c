#include "../inc/list.h"

int read_list(list_stack_t **ptr, int *cnt)
{
    free_list(ptr, cnt);
    *ptr = NULL;
    char ch = 'i';
    int item, rc;
    while (ch != '\n')
    {
        if ((rc = get_item(&item)))
            return rc;
        rc = push_list(ptr, item, cnt);
        if (rc == ERR_MALLOC)
        {
            printf("\nНевозможно добавить элемент в стек: ошибка выделения памяти.\n\n");
            return rc;
        }
        if (rc == MAX_SIZE)
        {
            printf("\nНевозможно добавить элемент в стек: Переполнение.\n\n");
            return rc;
        }
        ch = getchar();
    }
    printf("\nЭлементы успешно введены.\n");
    return EXIT_SUCCESS;
}

void free_list(list_stack_t **ptr, int *cnt)
{
    *cnt = 0;
    while (*ptr)
    {
        list_stack_t *buf = *ptr;
        *ptr = (*ptr)->prev;
        free(buf);
    }
}
// printf
int push_list(list_stack_t **ptr, int item, int *cnt)
{
    if (*cnt >= MAX_SIZE)
        return MAX_SIZE;
    list_stack_t *new = malloc(sizeof(list_stack_t));
    if (!new)
        return ERR_MALLOC;
    (*cnt)++;
    new->prev = *ptr;
    new->data = item;
    *ptr = new;
    return EXIT_SUCCESS;
}

int pop_list(list_stack_t **ptr, int *item, int *cnt)
{
    if (!(*ptr))
        return ERR_EMPTY_STACK;
    (*cnt)--;
    list_stack_t *temp = *ptr;
    *item = (*ptr)->data;
    *ptr = (*ptr)->prev;
    free(temp);
    return EXIT_SUCCESS;
}

void init_list(list_stack_t **ptr)
{
    *ptr = NULL;
}

int pop_list_with_freed(list_stack_t **ptr, int *item, freed_t *list, int *cnt)
{
    if (!(*ptr))
        return ERR_EMPTY_STACK;
    *item = (*ptr)->data;
    if (list)
        list->a[list->index++] = *ptr;
    *ptr = (*ptr)->prev;
    (*cnt)--;
    return EXIT_SUCCESS;
}

int push_list_with_freed(list_stack_t **ptr, int item, freed_t *list, int *cnt)
{
    if (*cnt >= MAX_SIZE)
        return MAX_SIZE;
    list_stack_t *new = malloc(sizeof(list_stack_t));
    if (!new)
        return ERR_MALLOC;
    (*cnt)++;
    new->prev = *ptr;
    new->data = item;
    *ptr = new;
    int i = 0;
    while (i < list->index && (void*)new != (void*)list->a[i])
        i++;
    if (i != list->index)
    {
        for (int j = list->index - 1; j > i; j--)
            list->a[j - 1] = list->a[j];
        list->index--;
    }
    return EXIT_SUCCESS;
}

void print_list(list_stack_t *ptr, int *cnt)
{
    int item;
    int cnt_buf = 0;
    list_stack_t *buf = NULL;
    if (!ptr)
        printf("\nСтек пуст.\n");
    else
    {   
        printf("\n┏━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┓\n");
        printf("┃%21s┃%22s┃\n", "Адрес", "Значение");
        while (ptr)
        {
            printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━┫\n");
            printf("┃     %p", (void*)ptr);
            pop_list(&ptr, &item, cnt);
            printf("┃%14d┃\n", item);
            push_list(&buf, item, &cnt_buf);
        }
        printf("┗━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━┛\n");
        while (buf)
        {
            pop_list(&buf, &item, &cnt_buf);
            push_list(&ptr, item, cnt);
        }
    }
}