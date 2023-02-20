#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_ELEMS 2000

// Массив 
typedef struct arr_s
{ 
    int arr[MAX_ELEMS];  // массив для хранения даты
    int begin;           // индекс - удаление 
    int end;             // индекс - добаление
    int size;            // размер очереди
} arr_t;

// Нода
typedef struct node_s
{
    int elem;            // информационная часть
    struct node_s *next; // указатель на следующий узел
} node_t;

// Cписок
typedef struct list_s
{
    node_t *head;  // узел головы
    node_t *tail;  // узел хвоста
    int size;      // размер очереди
} list_t;

// Массив освобожденных элементов
typedef struct
{
    node_t *arr_clear[1000]; 
    int len;
} arr_clear_t;

typedef struct times
{
    float min;  // нижная граница времени
    float max;  // верхняя граница времени
} time_r;


#endif