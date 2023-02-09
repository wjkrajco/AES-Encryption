/** 
    @file number_10.c  
    @author William J Krjacovic (wjkrajco)
    This is the program for inputs of base 10 reading in arithmetic inputs
    and utlizing the operations class to complete the mathmatic operations inputted.
    Also using the number.h header for block comments.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "number.h"
#include "operation.h"


int skip_space()    
{

    char ch;

    while ( (ch = getchar()) != EOF )   {

        if (ch == '\n')    {
            ungetc(ch, stdin);
            return EOF;
        }

        if ( ch != ' ' && ch != '\t' && ch != '\v' && ch != '\f' && ch != '\r')    {
            ungetc(ch, stdin);
            return (int)ch;
        }

    }

    return EOF;

}

long parse_value()    
{
    long value = 0;

    char ch = getchar();

    bool isNegative = false;

    if ( ch == '-' )    {
        isNegative = true;
    }

    long digit = 0;

    while (ch >= '0' && ch <= '9')    {
        digit = minus((long)ch,'0');

        value = times(value, (long)MOVE_A_PLACE);

        if (LONG_MIN == minus(-value, digit))    {
            ch = getchar();
            ungetc(ch, stdin);
            return LONG_MIN;
        }

        value = plus(value, digit);


        ch = getchar();
    }

    ungetc(ch, stdin);

    if ( isNegative )    {
        return times(value, -1);
    }

    return value;

}


void print_value ( long val )
{
    if (val < 0) {
        putchar('-');
        val = -val;
    }

    if (val == 0) {
        putchar('0');
    } else {
        long d = val % MOVE_A_PLACE;
        char ch = d + '0';
        if (val >= MOVE_A_PLACE) {
            print_value(val / MOVE_A_PLACE);
        }
        putchar(ch);
    }
}