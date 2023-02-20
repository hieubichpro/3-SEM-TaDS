#include"../inc/list_queue.h"


void init_list_queue(list_t *queue)
{
    queue->head = malloc(sizeof(node_t));
    queue->tail = malloc(sizeof(node_t));

    queue->head->elem = 0;
    queue->head->next = queue->tail;

    queue->tail->elem = 0;
    queue->tail->next = NULL;

    queue->size = 0;
}


int clear_check_list(list_t queue)
{
    return queue.size == 0 ? 1 : 0;
}

int owerflow_list(list_t queue)
{
    return (queue.size > MAX_ELEMS) ? 1 : 0;
}


void push_list_queue(list_t *queue, int elem)
{
    node_t *node = queue->tail;

    node->elem = elem;

    queue->tail = malloc(sizeof(node_t));
    queue->tail->next = NULL;
    queue->tail->elem = 0;

    node->next = queue->tail;

    queue->size += 1;
}


int pop_list_queue(list_t *queue)
{
    node_t *node = queue->head->next;
    int num = node->elem;

    queue->head->next = node->next;
    queue->size -= 1;

    free(node);
    
    return num; 
}


void print_list_queue(list_t queue)
{
    if (clear_check_list(queue))
    {
        printf("Очередь пуста\n");
        return;
    }

    for (node_t *ind = queue.head->next; ind != queue.tail; ind = ind->next)
        printf("%p = %d\n", (void*)ind, ind->elem);
}


void free_list(list_t *queue)
{
    while (!clear_check_list(*queue))
    {
        pop_list_queue(queue);
    }

    free(queue->head);
    free(queue->tail);
}


//Cleared adreses

void add_adress(arr_clear_t *arr, list_t *list)
{
    if (clear_check_list(*list))
    {
        return;
    }

    int ind = arr->len;
    arr->arr_clear[ind] = list->head->next;
    arr->len += 1;
}


void adress_clear(arr_clear_t *arr, int ind)
{
    for (int i = ind; i < arr->len - 1; i++)
    {
        node_t *tmp = arr->arr_clear[i];
        arr->arr_clear[i] = arr->arr_clear[i + 1];
        arr->arr_clear[i + 1] = tmp;
    }
}

// Удаляем из массива адресса, если адрес был занят
void del_adress(arr_clear_t *arr, list_t *list)
{
    if (clear_check_list(*list))
        return;

    node_t *tmp = list->head->next;

    for (int i = 0; i < arr->len; i++)
    {
        tmp = list->head->next;

        for (int j = 0; j < list->size; j++)
        {
            if (arr->arr_clear[i] == tmp)
            {
                adress_clear(arr, i);
                arr->len -= 1;
                i--;
            }

            tmp = tmp->next;
        }
    }
}


void print_arr_adress(arr_clear_t arr)
{
    if (arr.len == 0)
    {
        puts("Массив освободившихся адрессов пуст");
        return;
    }

    int len = arr.len;

    puts("Массив освободившихся адрессов");

    for (int i = 0; i < len; i++)
        printf("%d. %p\n", i + 1, (void*)arr.arr_clear[i]);
}

double min_of_three_list(double a, double b, double c)
{
    double min = a;

    if (min > b)
        min = b;

    if (min > c)
        min = c;

    return min;
}


void task_list(void)
{
    list_t queue1;
    init_list_queue(&queue1);

    int q1_req_in = 0;  // заявок вошло
    int q1_req_out = 0; // заявок вышло
    int q1_req_all = 0; // количество раз работы с очередью
    int q1_len_all = 0; // вся длина очереди (для среднего значения)
    double q1_time_all = 0; // общее время для всей первой очереди
    int q1_len_cur = 0; // текущая длина очереди

    list_t queue2;
    init_list_queue(&queue2);

    int q2_req_in = 0; 
    int q2_req_out = 0;
    int q2_req_all = 0;
    int q2_len_all = 0;
    double q2_time_all = 0; // общее время для всей второй очереди
    int q2_len_cur = 0;
    int q2_back_in_end = 0;

    // дополнительные переменные подсчета

    double q1_cur_time_in = 0;
    //double q1_cur_time_work = 0;
    double q2_cur_time_in = 0;
    //double q2_cur_time_work = 0;

    //int q1_req_out_all = 0;

    int queue_type = 0;
    double oa_time = 0;


    double time_all = 0; // общее время

    int to_show = 0;

    int in_push = 0, in_pop = 0;

    while (q1_req_out < 1000)
    {
        if (fabs(q1_cur_time_in) < EPS)
            q1_cur_time_in = rand_time(T1_IN_B, T1_IN_E);

        if (fabs(q2_cur_time_in) < EPS)
            q2_cur_time_in = rand_time(T2_IN_B, T2_IN_E);

        if (fabs(oa_time) < EPS)
        {
            // если время работы аппарата = 0, то загрузить его работой с первой очередью, иначе - со второй
            if (!clear_check_list(queue1))
            {
                oa_time = rand_time(T1_OUT_B, T1_OUT_E);
                queue_type = 1;
                pop_list_queue(&queue1);

                in_pop++;

                q1_len_cur--;
                q1_req_all++;
                q1_len_all += q1_len_cur;

                q1_time_all += oa_time;
            }
            else if (!clear_check_list(queue2))
            {
                oa_time = rand_time(T2_OUT_B, T2_OUT_E);
                queue_type = 2;
                pop_list_queue(&queue2);

                q2_len_cur--;
                q2_req_all++;
                q2_len_all += q2_len_cur;

                q2_time_all += oa_time;
            }            
        }
        // если аппарат в работе, но с заявкой второго типа и появилась заявка первого типа, то нужно удалить из работы вторую заявку и подать первую
        else if ((queue_type == 2) && (!clear_check_list(queue1)))
        {
            push_list_queue(&queue2, 2);
            q2_time_all -= oa_time;
            oa_time = 0;
            q2_back_in_end++;

            //q2_req_in++;
            q2_len_cur++;
            q2_req_all++;
            q2_len_all += q2_len_cur;
            continue;
        }

        double min_time = 0;

        // если обработки нет, то ищем тот элемент, что будет добавлен быстрее (в 1 или во 2 очередь)
        if (fabs(oa_time) < EPS)
            min_time = min_of_three_list(q1_cur_time_in, q2_cur_time_in, q1_cur_time_in);
        // если есть обработки, то решаем, 
        // какой процесс быстрее - произвести обработку или добавить элемент из какой-то из очередей
        else
            min_time = min_of_three_list(q1_cur_time_in, q2_cur_time_in, oa_time);

        // если обработка быстрее
        if (fabs(oa_time - min_time) < EPS)
        {
            oa_time = 0;

            if (queue_type == 1)
                q1_req_out++;
            else if (queue_type == 2)
                q2_req_out++;
        }

        // если добавлене элемента в 1ую очередь быстрее
        if (fabs(q1_cur_time_in - min_time) < EPS)
        {
            push_list_queue(&queue1, 1);

            in_push++;

            q1_req_in++;
            q1_len_cur++;
            q1_req_all++;
            q1_len_all += q1_len_cur;
        }
        // если добавлене элемента в 2ую очередь быстрее
        if (fabs(q2_cur_time_in - min_time) < EPS && !owerflow_list(queue2))
        {
            push_list_queue(&queue2, 2);

            q2_req_in++;
            q2_len_cur++;
            q2_req_all++;
            q2_len_all += q2_len_cur;
        }

        q1_cur_time_in -= min_time;
        q2_cur_time_in -= min_time;

        if (oa_time >= min_time)
            oa_time -= min_time;

        time_all += min_time;

        // info every 100
        if ((q1_req_out % 100 == 0) && (q1_req_out != to_show))
        {
            to_show = q1_req_out;
            printf("Заявок 1го типа обработано = %d\n", q1_req_out);

            printf("Текущая длина очереди 1го типа = %d\n", q1_len_cur);
            printf("Средняя длина очереди 1го типа = %f\n", (double)(q1_len_all) / q1_req_all);

            printf("Текущая длина очереди 2го типа = %d\n", q2_len_cur);
            printf("Средняя длина очереди 2го типа = %f\n\n", (double)(q2_len_all) / q2_req_all);
        }

    }

    double avg_q1_in = (T1_IN_B + T1_IN_E) / 2;
    double all_avg_q1_in = avg_q1_in * COUNT;

    double avg_q1_out = (T1_OUT_B + T1_OUT_E) / 2;
    double all_avg_q1_out = avg_q1_out * COUNT;

    double avg_q2_in = (double)(T2_IN_B + T2_IN_E) / (double)2;

    
    double estimate_model_time; // берем большее время

    if (all_avg_q1_in > all_avg_q1_out)
        estimate_model_time = all_avg_q1_in;
    else
        estimate_model_time = all_avg_q1_out;

    double percent_oa = fabs((time_all - estimate_model_time) * 100 / estimate_model_time);

    printf("\n\nОбщее время моделировния = %f \
    \nПогрешность моделирования = %f\n\n", time_all, percent_oa);

    printf("\nЗаявок вошло в 1ую очередь = %d \
    \nЗаявок 1ой очереди вышло = %d \
    \nСреднее время обработки заявки в 1ой очереди (ожидаемое) = %f\n\n", q1_req_in, q1_req_out, avg_q1_in);

    printf("\nЗаявок вошло во 2ую очередь = %d \
    \nЗаявок 2ой очереди вышло = %d \
    \nСреднее время обработки заявки в 2ой очереди (ожидаемое) = %f\
    \nЗаявок 2го типа вернулось обратно в конец очереди = %d\n\n", q2_req_in, q2_req_out, avg_q2_in, q2_back_in_end);

    double t_max = avg_q1_in;

    if (avg_q1_out > avg_q1_in)
        t_max = avg_q1_out;

    double percent_time_in1 = fabs(time_all - avg_q1_in * COUNT) * 100 / (avg_q1_in * COUNT);

    double percent_time_out1 = fabs((t_max * COUNT - time_all) * 100 / (t_max * COUNT));

    printf("\nПогрешность ввода заявок в 1ую очередь %lf %% , а выхода  %lf %%" \
, percent_time_in1, percent_time_out1);

    double all_estimate_work = q1_time_all + q2_time_all;
    double time_wait = time_all - all_estimate_work;

    printf("\nВремя простоя = %f\n\n", fabs(time_wait));
}

