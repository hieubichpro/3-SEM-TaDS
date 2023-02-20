#include "../inc/sort_arr.h"

int sort_arr(arr_stack_t *st_a, arr_stack_t *st_b, arr_stack_t *res)
{
    if ((st_a->ptr - st_a->a + 1) + (st_b->ptr - st_b->a + 1) >= MAX_SIZE)
    {
        printf("\nОшибка: объединение двух стеков приведет к переполнению результирующего стека.\n");
        return ERR_FULL_ARR_STACK;
    }
    init_arr(res);
    append_in_sorted_stack(st_a, res);
    append_in_sorted_stack(st_b, res);
    return EXIT_SUCCESS;
}

void append_in_sorted_stack(arr_stack_t *src, arr_stack_t *dst)
{
    arr_stack_t buf;
    init_arr(&buf);
    int item, buf_item;
    while (src->ptr >= src->a)
    {
        pop_arr(src, &item);
        while (dst->ptr >= dst->a)
        {
            pop_arr(dst, &buf_item);
            push_arr(&buf, buf_item);
            if (buf_item < item)
            {
                pop_arr(&buf, &buf_item);
                push_arr(dst, buf_item);
                break;
            }
        }
        push_arr(dst, item);
        while (buf.ptr >= buf.a)
        {
            pop_arr(&buf, &buf_item);
            push_arr(dst, buf_item);
        }
    }
}
