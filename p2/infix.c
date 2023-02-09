/** 
    @file infix.c 
    @author William J Krjacovic (wjkrajco)
    This is the part of the program that houses the main function and is what scans
    through the mathmatical equations to come up with a solution. This program parses through the 
    exponenets and the mutiliplication and division of the equaiton.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "number.h"
#include "operation.h"

/** This is the exit result that is given if no input was able to be printed due to improper formatting.*/
#define EXIT_WITH_NO_INPUT 102


/** 
    Parses through an equation looking for exponential values. This function adds up all the value
    individually returning them to be totaled and eventually added or subtracted by the main function.

    @return The value currently being parsed.
*/
static long parse_exp()    
{
    char ch = getchar();

    long total = 0;

    //Temporary
    long temp = 0;

    bool isNegative = false;

    bool wasNumber = false;

    bool isExponent = false;

    bool canBeExponent = false;

    int whiteSpaceValue = 0;

    while (ch != '*' && ch != '/' && ch != '+')    {

        if (ch == '^' && canBeExponent)    {
            isExponent = true;
        }

        if (ch == '-')    {
            ch = getchar();
            if (ch == ' ' || ch == '\t' || ch == '\v' || ch == '\f' || ch == '\r' || ch == '\n' )    {
                ungetc(ch, stdin);
                if (!wasNumber || isExponent)    {
                    exit(EXIT_WITH_NO_INPUT);
                }
                return total;
            }
            isNegative = true;
        }
        if ((ch >= '0' && ch <= '9') || ch == 'X' || ch == 'E' )    {
            wasNumber = true;
            canBeExponent = true;
            if (isNegative)    {
                isNegative = false;
                ungetc(ch, stdin);
                temp = parse_value();
                if (temp != LONG_MIN)    {
                    total = times(-1, temp);
                }
                else {
                    total = temp;
                }
            } else if (isExponent)    {
                isExponent = false;
                ungetc(ch, stdin);
                temp = parse_value();
                total = exponential(total, temp);

            }
            else    {
                ungetc(ch, stdin);
                total = parse_value();
            }
            
        }

        else if (ch == ' ' || ch == '\t' || ch == '\v' || ch == '\f' || ch == '\r' || ch == '\n')    {
            ungetc(ch, stdin);
            whiteSpaceValue = skip_space();
            if (whiteSpaceValue == -1)    {
                if (!wasNumber || isExponent)    {
                    exit(EXIT_WITH_NO_INPUT);
                }
                return total;
            }

            if (whiteSpaceValue != '*' && whiteSpaceValue != '+' && whiteSpaceValue != '-' && whiteSpaceValue != '^' && whiteSpaceValue != '/' && (whiteSpaceValue < '0' ||
                whiteSpaceValue > '9') && whiteSpaceValue != 'X' && whiteSpaceValue != 'E')    {
                    exit(EXIT_WITH_NO_INPUT);
            }
        }

        ch = getchar();
    }

    ungetc(ch, stdin);
    if (!wasNumber || isExponent)    {
        exit(EXIT_WITH_NO_INPUT);
    }
    return total;
}

/** 
    This function reads through the input and collects the blocks of equations that are
    being added or subtract. It utilizes the parse_exp function to gather the values of the all the
    numbers inbetween the blocks of pluses and minuses, taking in those values to send back block totals
    back to main to be subtracted or added.

    @return The value of the block of the equation
*/
static long parse_mul_div()    
{
    char ch;
    
    bool firstPass = true;

    long total = 0;

    ch = getchar();

    long temp = 0;

    while (ch != '+' && ch != '\n' && ch != EOF)    {

        if (ch == '*')    {
            firstPass = false;
            temp = parse_exp();
            total = times(total, temp);
        }

        else if (ch == '/')    {
            firstPass = false;
            temp = parse_exp();
            total = divide(total, temp);
        }

        else if ((ch == ' ' || ch == '\t' || ch == '\v' || ch == '\f' || ch == '\r') && !firstPass)    {
            ungetc(ch, stdin);
            return total;
        }

        else if (((ch != ' ' && ch != '\t' && ch != '\v' && ch != '\f' && ch != '\r' && ch != '*' && ch != '/') && !(ch >= '0' && ch <= '9') &&
         ch != 'X' && ch != 'E'  && ch != '-'))    {
            exit(102);
         }

        else {
            firstPass = false;
            ungetc(ch, stdin);
            total = plus(total, parse_exp());
        }



        ch = getchar();

    }

    ungetc(ch, stdin);
    return total;

}

/** 
    This is the main function of the program. This function reads in the first parts of the
    input and begins to call parse_mul_div through either addition or subtraction whether the input
    asks for the next block of equation to be subtracted or added to the total. The function then calls for the
    result to be printed.

    @return EXIT_SUCESS if the program completes
*/
int main()    
{
    char ch = getchar();
    //To show that we have passed through once
    bool passedThrough = false;

    long total = 0;


    while ( ch != EOF && ch != '\n')    {

        //This is for the minus operation
        if (((ch == ' ' || ch == '\t' || ch == '\v' || ch == '\f' || ch == '\r') && passedThrough) || ((ch == '-') && (passedThrough)) )    {
            ungetc(ch, stdin);
            total = minus(total, parse_mul_div());
            
        }
        else if (ch == '+')   {
            total = plus(total, parse_mul_div());
        }

        else if ((ch >= '0' && ch <= '9') || ch == 'X' || ch == 'E'  || ch == '-')   {
            passedThrough = true;
            ungetc(ch, stdin);
            total = plus(total, parse_mul_div());
        }

        else if ((ch == ' ' || ch == '\t' || ch == '\v' || ch == '\f' || ch == '\r'))    {
            skip_space();
        }
        
        ch = getchar();
    }

    print_value(total);
    putchar('\n');

    return EXIT_SUCCESS;





}