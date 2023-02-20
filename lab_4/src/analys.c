#include "../inc/analys.h"

void print_cycle(int n);

void analys(void)
{
    printf("\nСравнительный анализ в количественном соотношении:\n\n");
    printf("┏━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃               ┃         Удаление          ┃         Добавление        ┃    Сортировка всех данных     ┃          Память               ┃\n");
    printf("┃    Кол-во     ┣━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┫━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━╋\n");
    printf("┃   элементов   ┃ Стек-массив ┃ Стек-список ┃ Стек-массив ┃ Стек-список ┃  Стек-массив  ┃  Стек-список  ┃  Стек-массив  ┃  Стек-список  ┃\n");
    print_cycle(250);
    print_cycle(500);
    print_cycle(750);
    print_cycle(1000);
    print_cycle(1500);
    printf("┗━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void print_cycle(int n)
{
    struct timeval t_start, t_end;
    size_t time_arr[3] = { 0 }, time_list[3] = { 0 };
    int item;
    arr_stack_t st_1;
    arr_stack_t st_2;
    arr_stack_t temp_st_1;
    arr_stack_t temp_st_2;
    arr_stack_t res;

    init_arr(&st_1);
    init_arr(&st_2);
    init_arr(&temp_st_1);
    init_arr(&temp_st_2);
    init_arr(&res);

    int cnt1 = 0, cnt2 = 0;
    list_stack_t *ptr_1 = NULL;
    list_stack_t *ptr_2 = NULL;
    list_stack_t *temp_ptr_1 = NULL;
    list_stack_t *temp_ptr_2 = NULL;
    list_stack_t *ptr_res = NULL;

    int a[MAX_SIZE];
    int k = 0;

    for (int i = 0; i < n; i++)
    {
        item = rand() % 100;
        push_arr(&st_1, item);
        push_list(&ptr_1, item, &cnt1);
        a[k++] = item;
    }
    
    for (int i = 0; i < n; i++)
    {
        item = rand() % 100;
        push_arr(&st_2, item);
        push_list(&ptr_2, item, &cnt2);
    }

    copy_arr(&st_1, &temp_st_1);

    gettimeofday(&t_start, NULL);
    
    while (temp_st_1.ptr >= temp_st_1.a)
        pop_arr(&temp_st_1, &item);

    gettimeofday(&t_end, NULL);

    time_arr[0] = (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);

    int cnt_tmp = cnt1;
    temp_ptr_1 = copy_list(&ptr_1, cnt1);
    gettimeofday(&t_start, NULL);
    
    while (temp_ptr_1)
        pop_list(&temp_ptr_1, &item, &cnt_tmp);

    gettimeofday(&t_end, NULL);

    time_list[0] =(t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);

    init_arr(&temp_st_1);
    k = 0;
    gettimeofday(&t_start, NULL);
        
    while (k < n)
        push_arr(&temp_st_1, a[k++]);

    gettimeofday(&t_end, NULL);

    time_arr[1] = (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);

    temp_ptr_1 = NULL;
    k = 0;

    gettimeofday(&t_start, NULL);

    while (k < n)
        push_list(&temp_ptr_1, a[k++], &cnt_tmp);

    gettimeofday(&t_end, NULL);

    time_list[1] = (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);


    copy_arr(&st_1, &temp_st_1);
    copy_arr(&st_2, &temp_st_2);

    gettimeofday(&t_start, NULL);

    {
        init_arr(&res);
        sort_arr(&temp_st_1, &temp_st_2, &res);
    }

    gettimeofday(&t_end, NULL);

    size_t tm = (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    time_arr[2] = tm > 100000 ? tm / 10 : tm;

    int cnt_tmp1 = cnt1;
    int cnt_tmp2 = cnt2;
    int cnt_res = 0;
    temp_ptr_1 = copy_list(&ptr_1, cnt1);
    temp_ptr_2 = copy_list(&ptr_2, cnt2);

    gettimeofday(&t_start, NULL);

    {
        sort_list(&temp_ptr_1, &temp_ptr_2, &ptr_res, &cnt_tmp1, &cnt_tmp2, &cnt_res, NULL);
    }

    gettimeofday(&t_end, NULL);
    tm = (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);
    time_list[2] = tm > 100000 ? tm / 10 : tm;

    printf("┣━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫━━━━━━━━━━━━━━━┫━━━━━━━━━━━━━━━┫\n");
    printf("┃%9d      ┃%10ld ms┃%10ld ms┃%10ld ms┃%10ld ms┃%12ld ms┃%12ld ms┃%12ld b ┃%12ld b ┃\n",
            n, time_arr[0], time_list[0], time_arr[1], time_list[1], time_arr[2], time_list[2], 4 * MAX_SIZE + sizeof(int *), sizeof(list_stack_t) * n);
}

list_stack_t* copy_list(list_stack_t **src, int cnt)
{
    list_stack_t *buf = NULL;
    list_stack_t *cp = NULL;
    int item;
    int x = cnt, x_buf = 0, x_cp = 0;
    while (*src)
    {
        pop_list(src, &item, &x);
        push_list(&buf, item, &x_buf);
    }
    while (buf)
    {
        pop_list(&buf, &item, &x_buf);
        push_list(src, item, &x);
        push_list(&cp, item, &x_cp);
    }
    return cp;
}

void copy_arr(arr_stack_t *src, arr_stack_t *dst)
{
    arr_stack_t buf;
    init_arr(&buf);
    init_arr(dst);
    int item;
    while (src->ptr >= src->a)
    {
        pop_arr(src, &item);
        push_arr(&buf, item);
    }
    while (buf.ptr >= buf.a)
    {
        pop_arr(&buf, &item);
        push_arr(src, item);
        push_arr(dst, item);
    }
}