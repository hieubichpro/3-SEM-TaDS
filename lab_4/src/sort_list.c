#include "../inc/sort_list.h"

int sort_list(list_stack_t **ptr_a, list_stack_t **ptr_b, list_stack_t **ptr_res, int *cnt1, int *cnt2, int *cnt_res, freed_t *list)
{
    (*ptr_res) = NULL;
    list_stack_t *buf = NULL;
    int cnt_buf = (*cnt_res) = 0;
    int item, buf_item;
    int rc;
    while ((*ptr_a))
    {
        pop_list_with_freed(ptr_a, &item, list, cnt1);
        while (*ptr_res)
        {
            pop_list(ptr_res, &buf_item, cnt_res);
            if ((rc = push_list(&buf, buf_item, &cnt_buf)))
                return rc;
            if (buf_item < item)
            {
                pop_list(&buf, &buf_item, &cnt_buf);
                if ((rc = push_list(ptr_res, buf_item, cnt_res)))
                    return rc;
                break;
            }
        }
        if ((rc = push_list(ptr_res, item, cnt_res)))
            return rc;
        while (buf)
        {
            pop_list(&buf, &buf_item, &cnt_buf);
            if ((rc = push_list(ptr_res, buf_item, cnt_res)))
                return rc;
        }
    }
    while ((*ptr_b))
    {
        pop_list_with_freed(ptr_b, &item, list, cnt2);
        while (*ptr_res)
        {
            pop_list(ptr_res, &buf_item, cnt_res);
            if ((rc = push_list(&buf, buf_item, &cnt_buf)))
                return rc;
            if (buf_item < item)
            {
                pop_list(&buf, &buf_item, &cnt_buf);
                if ((rc = push_list(ptr_res, buf_item, cnt_res)))
                    return rc;
                break;
            }
        }
        if ((rc = push_list(ptr_res, item, cnt_res)))
            return rc;
        while (buf)
        {
            pop_list(&buf, &buf_item, &cnt_buf);
            if ((rc = push_list(ptr_res, buf_item, cnt_res)))
                return rc;
        }
    }
    return EXIT_SUCCESS;
}