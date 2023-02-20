#ifndef TIME_COUNT_H
#define TIME_COUNT_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "sys/time.h"
#include"../inc/arr_queue.h"
#include"../inc/list_queue.h"
#include"../inc/print_info.h"
#include"../inc/structs.h"


#define GHZ 3500000000
#define RUNS 1000

float rand_time(float min, float max);
double min_of_three(const double a, const double b, const double c);
void memory_io(int n);
void analys(void);

#endif