/** 
    @file field.c
    @author William J Krjacovic (wjkrajco)
    This file holds the arithmetic Galois field operations of
    subtraction and multiplication.
*/

#include <stdlib.h>
#include "field.h"


byte fieldAdd(byte a, byte b)
{
    return a ^ b;
}

byte fieldSub(byte a, byte b)
{
    return a ^ b;
}

byte fieldMul(byte a, byte b)
{
    byte result = 0;
    byte reducer = HEX_FOR_REDUCTION;
    
    for (int i = 0; i < BBITS; i++) {
        if (b & 1) {
            result ^= a;
        }
        byte high_bit_set = a & HEX_FOR_HIGH_BIT;
        a <<= 1;

        if (high_bit_set) {
            a ^= reducer;
        }

        b >>= 1;
    }

    return result;
}
