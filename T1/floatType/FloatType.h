#ifndef FLOATTYPE_H
#define FLOATTYPE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef union
{
    __int64_t i;
    double f;
    struct
    {                             // Bitfields for exploration (32 bits = sign|exponent|mantissa)
        __uint64_t mantissa : 52; // primeiros 23 bits (da direita para a esquerda)
        __uint64_t exponent : 11; // próximos 8 bits
        __uint64_t sign : 1;      // proximo bit (ou seja, o bit mais a esquerda)
    } parts;
} Float_t;

#endif // FLOATTYPE_H