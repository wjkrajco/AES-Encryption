

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"


// char *readLine (FILE *fp)
// {
//     int capacity = INITIAL_CAPACITY;
//     int len = 0;
//     char ch;
//     char *str = (char *)malloc(capacity * sizeof(char));

//     while((ch = fgetc(fp)) != '\n' && ch != EOF) {
//         if (len >= capacity - 1) {
//             capacity *= STRING_MULTIPLICATION;
//             char *newStr = (char *)realloc(str, capacity * sizeof(char));
//         }
//         str[len++] = ch;
//     }
//     if (ch == EOF && len == 0)  {
//         free(str);
//         return NULL;
//     }
//     str[len] = '\0';
//     ch = fgetc(fp);
//     if (ch != EOF)  {
//         ungetc(ch, fp);
//     }
//     return str;

// }

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