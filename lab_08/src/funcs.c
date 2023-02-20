#include "funcs.h"

int check_number(int *num, int left, int right)
{
    if (scanf("%d", num) != 1)
    {
        while (getchar() != '\n');
        return READ_ERROR;
    }

    if (*num < left || *num > right)
    {
        while (getchar() != '\n');
        return READ_ERROR;
    }

    return OK;
}


uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}
