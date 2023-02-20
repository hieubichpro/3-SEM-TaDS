#include"../inc/arr_queue.h"


void init_arr_queue(arr_t *queue)
{
    queue->begin = -1;
    queue->end = -1;
    queue->size = 0;
}


int owerflow_arr_queue(arr_t queue)
{
    return (queue.size > MAX_ELEMS) ? 1 : 0;
}



int clear_check_arr_queue(arr_t queue)
{
    return queue.begin == -1 ? 1 : 0;
}


void push_arr_queue(arr_t *queue, int elem)
{    
    if (queue->begin == -1)
        queue->begin = 0;

    queue->end = (queue->end + 1) % MAX_ELEMS;
    queue->arr[queue->end] = elem;
    queue->size++;
}


int pop_arr_queue(arr_t *queue)
{
    if (queue->begin == queue->end)
    {
        queue->begin = -1;
        queue->end = -1;
    }
    else
    {
        queue->begin = (queue->begin + 1) % MAX_ELEMS;
        queue->size--;
    }

    return queue->arr[queue->begin + 1];
}


void print_arr_queue(arr_t queue)
{
    if (clear_check_arr_queue(queue))
    {
        printf("Очередь пустая\n");
        return;
    }

    for (int i = queue.begin; i <= queue.end; i++)
        printf("%d ", queue.arr[i]);

    puts("\n");
}

void task_arr(void)
{
    arr_t queue1;
    init_arr_queue(&queue1);

    int q1_req_in = 0;  // заявок вошло
    int q1_req_out = 0; // заявок вышло
    int q1_req_all = 0; // количество раз работы с очередью
    int q1_len_all = 0; // вся длина очереди (для среднего значения)
    double q1_time_all = 0; // общее время для всей первой очереди
    int q1_len_cur = 0; // текущая длина очереди

    arr_t queue2;
    init_arr_queue(&queue2);

    int q2_req_in = 0; 
    int q2_req_out = 0;
    int q2_req_all = 0;
    int q2_len_all = 0;
    double q2_time_all = 0; // общее время для всей второй очереди
    int q2_len_cur = 0;
    int q2_back_in_end = 0;

    // дополнительные переменные подсчета

    double q1_cur_time_in = 0;
    double q2_cur_time_in = 0;
 

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
            // если время работы аппарата = 0, 
            // то загрузить его работой с первой очередью, иначе - со второй
            if (!clear_check_arr_queue(queue1))
            {
                oa_time = rand_time(T1_OUT_B, T1_OUT_E);
                queue_type = 1;
                pop_arr_queue(&queue1);

                in_pop++;

                q1_len_cur--;
                q1_req_all++;
                q1_len_all += q1_len_cur;

                q1_time_all += oa_time;
            }
            else if (!clear_check_arr_queue(queue2))
            {
                oa_time = rand_time(T2_OUT_B, T2_OUT_E);
                queue_type = 2;
                pop_arr_queue(&queue2);

                q2_len_cur--;
                q2_req_all++;
                q2_len_all += q2_len_cur;

                q2_time_all += oa_time;
            }            
        }
        // если аппарат в работе, но с заявкой второго типа и появилась заявка первого типа, 
        // то нужно удалить из работы вторую заявку и подать первую
        else if ((queue_type == 2) && (!clear_check_arr_queue(queue1)))
        {
            push_arr_queue(&queue2, 2);
            q2_time_all -= oa_time;
            oa_time = 0;
            q2_back_in_end++;

            q2_len_cur++;
            q2_req_all++;
            q2_len_all += q2_len_cur;
            continue;
        }

        double min_time = 0;

        // если обработки нет, то ищем тот элемент, что будет добавлен быстрее (в 1 или во 2 очередь)
        if (fabs(oa_time) < EPS)
            min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, q1_cur_time_in);
        // если есть обработки, то решаем, какой процесс быстрее - произвести 
        // обработку или добавить элемент из какой-то из очередей
        else
            min_time = min_of_three(q1_cur_time_in, q2_cur_time_in, oa_time);

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
            if (owerflow_arr_queue(queue1))
            {
                printf("\nВсе, ока не выходило 1000 заявок 1-ого типа первая очередь переполнена\n\n");
                break;
            }
            push_arr_queue(&queue1, 1);

            in_push++;

            q1_req_in++;
            q1_len_cur++;
            q1_req_all++;
            q1_len_all += q1_len_cur;
        }
        // если добавлене элемента в 2ую очередь быстрее
        if (fabs(q2_cur_time_in - min_time) < EPS)
        {
            if (owerflow_arr_queue(queue2))
            {
                printf("\nВсе, пока не выходило 1000 заявок 1-ого типа но вторая очередь переполнена\n\n");
                break;
            }
            push_arr_queue(&queue2, 2);

            q2_req_in++;
            q2_len_cur++;
            q2_req_all++;
            q2_len_all += q2_len_cur;
        }

        // Оставшееся время для добавления заявки
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
            printf("Средняя длина очереди 1го типа = %lf\n", (double)(q1_len_all) / q1_req_all);

            printf("Текущая длина очереди 2го типа = %d\n", q2_len_cur);
            printf("Средняя длина очереди 2го типа = %lf\n\n", (double)(q2_len_all) / q2_req_all);
        }
    }

    double avg_q1_in = (double)(T1_IN_B + T1_IN_E) / (double)2;
    double all_avg_q1_in = avg_q1_in * COUNT;

    double avg_q1_out = (double)(T1_OUT_B + T1_OUT_E) / (double)2;
    double all_avg_q1_out = avg_q1_out * COUNT;

    if (owerflow_arr_queue(queue2) || owerflow_arr_queue(queue1))
    {
        all_avg_q1_in = avg_q1_in * q1_req_out;
        all_avg_q1_out = avg_q1_out * q1_req_out;
    }

    double avg_q2_in = (double)(T2_IN_B + T2_IN_E) / (double)2;

    double estimate_model_time;

    if (all_avg_q1_in > all_avg_q1_out)
        estimate_model_time = all_avg_q1_in;
    else
        estimate_model_time = all_avg_q1_out;

    double percent_oa = fabs((time_all - estimate_model_time) * 100 / estimate_model_time);

    printf("Общее время моделировния = %lf \
    \nПогрешность моделирования = %lf %%\n", time_all, percent_oa);

    printf("\nЗаявок 1ой очереди вошло = %d \
    \nЗаявок 1ой очереди вышло = %d \
    \nСреднее время обработки заявки в 1ой очереди (ожидаемое) = %lf\n", q1_req_in, q1_req_out, avg_q1_in);

    printf("\nЗаявок 2ой очереди вошло = %d \
    \nЗаявок 2ой очереди вышло = %d \
    \nСреднее время обработки заявки в 2ой очереди (ожидаемое) = %lf\
    \nЗаявок 2го типа вернулось обратно в конец очереди = %d\n", q2_req_in, q2_req_out, avg_q2_in, q2_back_in_end);

    double t_max = avg_q1_in;

    if (avg_q1_out > avg_q1_in)
        t_max = avg_q1_out;

    double percent_time_in1 = fabs(time_all - avg_q1_in * q1_req_out) * 100 / (avg_q1_in * q1_req_out);

    double percent_time_out1 = fabs((t_max * q1_req_out - time_all) * 100 / (t_max * q1_req_out));


    printf("\nПогрешность ввода заявок в 1ую очередь %lf %% , а выхода  %lf %% \
    \n", percent_time_in1, percent_time_out1);

    double all_estimate_work = q1_time_all + q2_time_all;
    double time_wait = time_all - all_estimate_work;

    printf("\nВремя простоя = %lf\n", fabs(time_wait));
}