/** 
    @file input.c
    @author William J Krjacovic (wjkrajco)
    This is the header file for Input which has the job of reading a line from a file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

char *readLine(FILE *fp) {
    int capacity = INITIAL_CAPACITY;
    int len = 0;
    char *str = (char *)malloc(capacity * sizeof(char));
    char ch;
    if (!str) {
        return NULL; // allocation failed
    }
    
    while (1) {
        ch = fgetc(fp);
        if (ch == EOF || ch == '\n') {
            break;
        }
        if (len >= capacity - 1) {
            capacity *= STRING_MULTIPLICATION;
            char *newStr = (char *)realloc(str, capacity * sizeof(char));
            if (!newStr) {
                free(str);
                return NULL; // reallocation failed
            }
            str = newStr;
        }
        str[len++] = ch;
    }
    
    if (len == 0 && ch == EOF) {
        free(str);
        return NULL; // no input read
    }
    
    str[len] = '\0';
    return str;
}


// /** 
//     @file input.c
//     @author William J Krjacovic (wjkrajco)
//     This is the header file for Input which has the job of reading a line from a file.
// */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "input.h"

// char *readLine(FILE *fp) {
//     int capacity = INITIAL_CAPACITY;
//     int len = 0;
//     char *str = (char *)malloc(capacity * sizeof(char));
//     char ch;
//     if (!str) {
//         return NULL; // allocation failed
//     }
    
//     while (1) {
//         ch = fgetc(fp);
//         if (ch == EOF || ch == '\n') {
//             break;
//         }
//         if (len >= capacity - 1) {
//             capacity *= STRING_MULTIPLICATION;
//             char *newStr = (char *)realloc(str, capacity * sizeof(char));
//             if (!newStr) {
//                 free(str);
//                 return NULL; // reallocation failed
//             }
//             str = newStr;
//         }
//         str[len++] = ch;
//     }
    
//     if (len == 0 && ch == EOF) {
//         free(str);
//         return NULL; // no input read
//     }
    
//     str[len] = '\0';
//     return str;
// }
