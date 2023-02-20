#include"../inc/time_count.h"

double min_of_three(const double a, const double b, const double c)
{
    double min = a;

    if (min > b)
        min = b;

    if (min > c)
        min = c;

    return min;
}

float rand_time(float min, float max)
{
    return (max - min) * (float)(rand()) / (float)RAND_MAX + min;
}

void memory_io(int n)
{
    arr_t queue_arr;
    init_arr_queue(&queue_arr);

    list_t queue_list;
    init_list_queue(&queue_list);


    struct timeval t_start, t_end;
    size_t time_arr[2] = { 0 }, time_list[2] = { 0 };

    int k = 0;

// push elem in queue-massive

    gettimeofday(&t_start, NULL);

    while (k < n)
    {
        push_arr_queue(&queue_arr, k);
        k++;
    }

    gettimeofday(&t_end, NULL);

    time_arr[0] = (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);

// push elem in queue-list
    k = 0;

    gettimeofday(&t_start, NULL);

    while (k < n)
    {
        push_list_queue(&queue_list, k);
        k++;
    }

    gettimeofday(&t_end, NULL);

    time_list[0] = (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);   

// delete elem in queue-massive
    gettimeofday(&t_start, NULL);

    while (k > 0)
    {
        pop_arr_queue(&queue_arr);
        k--;
    }

    gettimeofday(&t_end, NULL);

    time_arr[1] = (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);

// delete elem in queue-list
    k = n;

    gettimeofday(&t_start, NULL);

    while (k > 0)
    {
        pop_list_queue(&queue_list);
        k--;
    }

    gettimeofday(&t_end, NULL);

    time_list[1] = (t_end.tv_sec - t_start.tv_sec) * 1000000LL + (t_end.tv_usec - t_start.tv_usec);



    printf("┣━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    printf("┃     %5d     ┃%10ld ms┃%10ld ms┃%10ld ms┃%10ld ms┃%9ld bytes┃%9ld bytes┃\n",
            n, time_arr[1], time_list[1], time_arr[0], time_list[0], 3 * 4 + MAX_ELEMS * sizeof(int) ,sizeof(node_t) * (n + 2) + 4 );

    free_list(&queue_list);
}

void analys(void)
{
    printf("┏━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃               ┃         Исключение        ┃         Добавление        ┃        Память                 ┃\n");
    printf("┃    Кол-во     ┣━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┫\n");
    printf("┃   элементов   ┃ Очередь-arr ┃ Очередь-lst ┃ Очередь-arr ┃ Очередь-lst ┃  Очередь-arr  ┃  Очередь-lst  ┃\n");
    memory_io(150);
    memory_io(300);
    memory_io(400);
    memory_io(500);
    memory_io(750);
    memory_io(900);
    memory_io(1000);
    printf("┗━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┛\n");
}