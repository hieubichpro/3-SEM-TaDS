#include "func.h"

int read_float(float_number *number)
{
    int c;
    // Read mantissa sign
    if ((c = getchar()) != '\n')
    {
        if ((c == EOF) || strchr("+-", c) == NULL)
        {   
            puts("MISSING_MANTISS_SIGN");
            return ERR_UNRIGHT_MANTISS_SIGN;
        }

        number->mantis_sign = c;
    }
    else
    {
        puts("ERR_NO_NUMBER");
        return ERR_NO_NUMBER;
    }
    // Read mantissa
    int i = 0;
    number->point_place = NO_POINT;

    while ((c = getchar()) != 'E')
    {
        if ((c == EOF) || (c == '\n'))
        {   
            puts("MISSING_EPSILON");
            return ERR_NO_EPSILON;
        }
        if ((c == '.') && (number->point_place == NO_POINT))
        {
            number->point_place = i;
        }
        else if ((c == '.') && (number->point_place != NO_POINT))
        {
            puts("TOO_MUCH_POINTS");
            return ERR_TOO_MUCH_POINTS;            
        }

        if ((c != '.') && (strchr("0123456789", c) == NULL))
        {
            puts("ERR_MANTISS_NUMBER");
            return ERR_UNRIGHT_MANTISS_NUM;
        }
        number->mantissa[i++] = c;

        if (i > MANTISSA_MAX_LEN)
        {
            puts("ERR_MANTISSA_TOO_LONG");
            return ERR_MANTISSA_TOO_LONG;
        }
    }

    number->num_of_digits = i - 1;
    number->mantissa[i] = '\0';

    if (number->point_place == NO_POINT)
    {
        puts("ERR_NUMBER_MUST_BE_FLOAT");
        return ERR_NUMBER_MUST_BE_FLOAT;        
    }

    if (number->num_of_digits == 0)
    {
        puts("ERR_ONLY_POINT");
        return ERR_ONLY_POINT;
    }

    // Read Power Sign
    if ((c = getchar()) != '\n')
    {
        if ((c == EOF) || (strchr("+-", c) == NULL))
        {   
            puts("MISSING_POWER_SIGN");
            return ERR_UNRIGHT_POWER_SIGN;
        }

        number->eps_sign = c;
    }

    // Read Power Sign
    int num;
    if (scanf("%d", &num) != 1)
    {
        puts("ERR_UNRIGHT_POWER");
        return ERR_UNRIGHT_POWER;
    }
    else if (num / 100000 >= 1)
    {
        puts("ERR_POWER_TOO_LONG");
        return ERR_POWER_TOO_LONG;
    }

    c = getchar();
    if ((c != EOF) && (c != '\n'))
    {
        puts("ERR_UNRIGHT_POWER");
        return ERR_UNRIGHT_POWER;
    }
    else
    {
        number->eps_num = num;
    }
    
    return OK_READ_NUMBER;
}

int read_int(int_number *number)
{
    int c;

    if ((c = getchar()) != '\n')
    {
        if ((c == EOF) || strchr("+-", c) == NULL)
        {   
            puts("MISSING_INT_SIGN");
            return ERR_UNRIGHT_MANTISS_SIGN;
        }

        number->int_sign = c;
    }
    else
    {
        puts("ERR_NO_NUMBER");
        return ERR_NO_NUMBER;
    }

    int i = 0;
    while ((c = getchar()) != '\n')
    {
        if ((c == EOF) || strchr("0123456789", c) == NULL)
        {
            puts("ERR_INPUT_INT");
            return ERR_NO_NUMBER;
        }
        if (i == 30)
            return ERR_NO_NUMBER;
        number->digits[i++] = c;
    }
    number->num_of_digits = i;
    return OK_READ_NUMBER;
}


void swap(char *mantissa, int j)
{
    char tmp = mantissa[j];
    mantissa[j] = mantissa[j + 1];
    mantissa[j + 1] = tmp;
}


void move_dot(float_number *number)
{
    int i = number->point_place;
    int n = number->num_of_digits;
    for (int j = i; j < n; j++)
        swap(number->mantissa, j);
    if (number->eps_sign == '+')
        if (number->eps_num - (n - i) >= 0)
            number->eps_num -= (n - i);
        else
        {
            number->eps_sign = '-';
            number->eps_num = (n - i) - number->eps_num;
        }
    else
        number->eps_num += (n - i); 
    number->point_place += (n - i);
}


void round_num(int *arr, int start)
{
    int end1 = start + 31;
    while (end1 <= 59)
        arr[end1++] = 0;
    int end = start + 30;
    if (arr[end] < 5)
        arr[end] = 0;
    else
    {
        int num = 10 - arr[end];
        int sum;
        int memo = 0;

        sum = arr[end] + num;
        arr[end] = sum % 10;
        memo = sum / 10;
        end--;
        while (memo)
        {
            sum = arr[end] + memo;
            arr[end] = sum % 10;
            memo = sum / 10;
            end --;
        }
    }
}


int multiply(float_number *num1, int_number *num2, int *result, int *res_power, int *start, int *end)
{
    int n1 = num1->point_place;
    int n2 = num2->num_of_digits;
    
    int index = 59, q;
    
    int num, write, rem = 0;
    
    for (int i = n1 - 1; i >= 0; i--)
    {
        q = index;
        rem = 0;
        
        for (int j = n2 - 1; j >= 0; j--)
        {
            num = (num1->mantissa[i] - '0') * (num2->digits[j] - '0') + rem + result[q];
            
            write = num % 10;
            rem = num / 10;
            
            result[q] = write;
            q--;
        }
        
        index--;
        result[q] = rem;
    }

    int i = 0;
    while (result[i] == 0)
        i++;
    // *start = i;

    int j = 59;

    if (j - i + 1 > 30)
        round_num(result, i);
    
    if (num1->eps_sign == '+')
        *res_power = num1->eps_num + (j - i + 1);
    else
        if (num1->eps_num > (j - i + 1))
            *res_power = num1->eps_num - (j - i + 1);
        else
        {
            num1->eps_sign = '+';
            *res_power = (j - i + 1) - num1->eps_num;
        }

    while (result[j] == 0)
        j--;

    *start = i;
    *end = j;
    if (*res_power > 99999)
    {
        puts("ERR_POWER_OVERFLOW");
        return ERR_POWER_OVERFLOW;
    }

    return 0;
}

void print_result(float_number num1, int_number num2, int *result, int res_power, int start, int end)
{
    if (num1.mantis_sign != num2.int_sign)
    {
        printf("-0.");
    }
    else
    {
        printf("+0.");
    }
    if (start > end)
    {
        res_power = 0;
        printf("0");
    }
    for (int i = start; i <= end; i++)
    {
        printf("%d", result[i]);
    }
    if (num1.eps_sign == '+')
        printf("E+%d", res_power);
    else
        printf("E-%d", res_power);
}