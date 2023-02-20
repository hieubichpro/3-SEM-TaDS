#include "func.h"

int main(void)
{
    int rc = 0;
    float_number number_1;
    printf("                  ----5----5----5----5----5----5\n");
    printf("Input number 1:  ");

    rc = read_float(&number_1);
    if (rc != 0)
    {
        return rc;
    }

    move_dot(&number_1);

    int_number number_2;
    printf("                  ----5----5----5----5----5----5\n");
    printf("Input number 2:  ");

    rc = read_int(&number_2);

    if (rc != 0)
    {
        return rc;
    }

    int result[60] = {0}, res_power, start, end;

    rc = multiply(&number_1, &number_2, result, &res_power, &start, &end);

    if (rc != 0)
    {
        return rc;
    }

    print_result(number_1, number_2, result, res_power, start, end);
    return rc;
}
