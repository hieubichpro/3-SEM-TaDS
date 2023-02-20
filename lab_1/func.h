#ifndef FUNC_H

#include <stdio.h>
#include <string.h>

#define MANTISSA_MAX_LEN 31
#define INT_MAX_LEN 30
#define NO_POINT -1

#define OK_READ_NUMBER 0
#define OK_READ 1

#define ERR_UNRIGHT_MANTISS_SIGN -1
#define ERR_UNRIGHT_MANTISS_NUM -2
#define ERR_NO_EPSILON -3
#define ERR_TOO_MUCH_POINTS -4
#define ERR_ONLY_POINT -5
#define ERR_MANTISSA_TOO_LONG -6
#define ERR_NUMBER_MUST_BE_FLOAT -7
#define ERR_UNRIGHT_POWER_SIGN -8
#define ERR_UNRIGHT_POWER -9
#define ERR_POWER_TOO_LONG -10
#define ERR_NO_NUMBER -11
#define ERR_POWER_OVERFLOW -12

typedef struct
{
    char mantis_sign;
    char mantissa[MANTISSA_MAX_LEN + 1];
    char eps_sign;
    int eps_num;
    int point_place;
    int num_of_digits;
} float_number;

typedef struct
{
    char int_sign;
    char digits[INT_MAX_LEN + 1];
    int num_of_digits;
} int_number;

int read_float(float_number *number);
int read_int(int_number *number);
void print_result(float_number num1, int_number num2, int *result, int res_power, int start, int end);
int multiply(float_number *num1, int_number *num2, int *result, int *res_power, int *start, int *end);
void round_num(int *arr, int start);
void move_dot(float_number *number);

#endif