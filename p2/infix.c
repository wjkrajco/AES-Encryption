#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "number.h"
#include "operation.h"


// static long parse_exp()    
// {
//     char ch = getchar();

//     long total = 0;

//     //Temporary
//     long temp = 0;

//     bool isNegative = false;

//     bool wasNumber = false;

//     int whiteSpaceValue = 0;

//     while (ch != '*' && ch != '/' && ch != '+')    {

//         if (ch == '-')    {
//             ch = getchar();
//             if (ch == ' ' || ch == '\t' || ch == '\v' || ch == '\f' || ch == '\r' || ch == '\n' )    {
//                 ungetc(ch, stdin);
//                 if (!wasNumber)    {
//                     exit(100);
//                 }
//                 return total;
//             }
//             isNegative = true;
//         }
//         if (ch >= '0' && ch <= '9' )    {
//             wasNumber = true;
//             if (isNegative)    {
//                 ungetc(ch, stdin);
//                 temp = parse_value();
//                 if (temp != LONG_MIN)    {
//                     total = times(-1, temp);
//                 }
//                 else {
//                     total = temp;
//                 }
//             }
//             else    {
//                 ungetc(ch, stdin);
//                 total = parse_value();
//             }
            
//         }

//         else if (ch == ' ' || ch == '\t' || ch == '\v' || ch == '\f' || ch == '\r' || ch == '\n')    {
//             ungetc(ch, stdin);
//             whiteSpaceValue = skip_space();
//             if (whiteSpaceValue == -1)    {
//                 if (!wasNumber)    {
//                     exit(100);
//                 }
//                 return total;
//             }
//         }

//         ch = getchar();
//     }

//     ungetc(ch, stdin);
//     if (!wasNumber)    {
//         exit(100);
//     }
//     return total;
// }

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
                    exit(100);
                }
                return total;
            }
            isNegative = true;
        }
        if (ch >= '0' && ch <= '9' )    {
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
                    exit(100);
                }
                return total;
            }
        }

        ch = getchar();
    }

    ungetc(ch, stdin);
    if (!wasNumber || isExponent)    {
        exit(100);
    }
    return total;
}


static long parse_mul_div()    
{
    char ch;
    
    bool firstPass = true;

    long total = 0;

    ch = getchar();

    long temp = 0;

    while (ch != '+' && ch != '\n' && ch != EOF)    {

        if (ch == '+')    {
            return total;
        }

        else if (ch == '*')    {
            firstPass = false;
            temp = parse_exp();
            total = times(total, temp);
        }

        else if (ch == '/')    {
            firstPass = false;
            temp = parse_exp();
            total = divide(total, temp);
        }

        else if ((ch == ' ' || ch == '\t' || ch == '\v' || ch == '\f' || ch == '\r' || ch == '\n') && !firstPass)    {
            ungetc(ch, stdin);
            return total;
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

        else if ((ch >= '0' && ch <= '9') || ch == '-')   {
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