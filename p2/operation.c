/** 
    @file operation.c
    @author William J Krjacovic (wjkrajco)
    This program has arithmetic operation functions for addition, subtraction, multiplication
    division and exponentials. And uses a header filed operation.h for the block comments.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "operation.h"



extern long plus ( long a, long b )    
{
    long value = a + b;

    if ( a > 0 && b > 0 && value < 0 )    {
        exit(OVERFLOW_EXIT);
    }

    if ( a < 0 && b < 0 && value > 0 )    {
        exit(OVERFLOW_EXIT);
    }

    return value;
}

long minus ( long a, long b )    
{
    return plus( a, -b );
}

long times ( long a, long b )    
{
    long value = 0;
    long x = 0;

    if ( a > 0 && b > 0)    {
        x = LONG_MAX / b;
        if ( a > x )    {
            exit(OVERFLOW_EXIT);
        }
        else {
            return a * b;
        }
    }

    if ( a < 0 && b < 0)    {
        x = LONG_MAX / b;
        if ( a < x )    {
            exit(OVERFLOW_EXIT);
        }
        else {
            return a * b;
        }
    }

    if ( a > 0 && b < 0)    {
        if (b == -1 && a == LONG_MIN)    {
            exit(OVERFLOW_EXIT);
        }
        x = LONG_MIN / b;
        if (a > x)    {
            exit(OVERFLOW_EXIT);
        }
        else {
            return a * b;
        }
    }

    if ( a < 0 && b > 0)    {
        if ( a == LONG_MIN && b == -1 )    {
            exit(OVERFLOW_EXIT);
        }
        x = LONG_MIN / b;
        if (a < x)    {
            exit(OVERFLOW_EXIT);
        }
        else {
            return a * b;
        }
    }

    return value;

}

long exponential ( long a, long b )    
{
    long value = 1;
    bool negativeExponent = false;

    if (b < 0)  {
        negativeExponent = true;
        b = times(b, -1);
    }

    for ( int i = 0; i < b; ++i )    {
        value = times(a, value);
    }

    if ( negativeExponent )    {
        return divide(1, b);
    }
    return value; 
}

long divide ( long a, long b )    
{

    if ( b == 0 )    {
        exit(DIVIDE_BY_ZERO_EXIT);
    }

    if (a == LONG_MIN && b == -1)    {
        exit(OVERFLOW_EXIT);
    }

    return a / b;

}