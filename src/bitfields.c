#include "thw/bitfields.h"
#include <stdint.h>
#include <stdio.h>

struct Printb Printb = { 0x1, 0x2, 0x4 };

static void m_printb(unsigned int number)
{
    if (number >> 1)
        m_printb(number >> 1);
    putchar(number & 1 ? '1' : '0');
}

int printb(unsigned int number, uint8_t opts)
{
    /* opts = 2fill_zero | 1prefix | 0nl
     */
    if (opts >> 3) // Unkown option
        return -1;

    GET_BIT(opts, 1) ? printf("0b") : 0;

    if (GET_BIT(opts, 2))
        for (unsigned int i = sizeof(int) * 8 - 1;
             GET_BIT(number, i) == 0 && i >= 0;
             i--)
            putchar('0');

    m_printb(number);

    GET_BIT(opts, 0) ? putchar('\n') : 0;

    return 0;
}
