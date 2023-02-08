/** 
    @file number_12.c 
    @author William J Krjacovic (wjkrajco)
    This is the program for inputs of base 12 reading in arithmetic inputs
    and utlizing the operations class to complete the mathmatic operations inputted.
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

    while ((ch >= '0' && ch <= '9') || ch == 'X' || ch == 'E' )    {
        if ( ch >= '0' && ch <= '9' )    {
            digit = minus((long)ch, '0');
        }
        else if (ch == 'X')   {
            digit = 10;
        }
        else    {
            digit = 11;            
        }
        value = times(value, 12);


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

void print_value (long val) 
{
    if (val < 0) {
        val = -val;
        putchar('-');
    }

    if (val == 0) {
        putchar('0');
    } else {
        long d = val % 12;
        char ch;
        if (d == 10) {
            ch = 'X';
        } else if (d == 11) {
            ch = 'E';
        } else {
            ch = d + '0';
        }
        if (val >= 12) {
            print_value(val / 12);
        }
        putchar(ch);
    }
}

