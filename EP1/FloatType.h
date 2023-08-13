#ifndef FLOATTYPE_H
#define FLOATTYPE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef union
{
    int32_t i;
    float f;
    struct
    {                           // Bitfields for exploration (32 bits = sign|exponent|mantissa)
        uint32_t mantissa : 23; // primeiros 23 bits (da direita para a esquerda)
        uint32_t exponent : 8;  // próximos 8 bits
        uint32_t sign : 1;      // proximo bit (ou seja, o bit mais a esquerda)
    } parts;
} Float_t;

void printFloat(Float_t num);

Float_t CalculaEpsilonRelativo(Float_t num);

int AlmostEqualRelative(Float_t A, Float_t B);

int AlmostEqualUlps(Float_t A, Float_t B, int maxULPs);

int main();

#endif // FLOATTYPE_H