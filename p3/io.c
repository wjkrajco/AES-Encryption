/** 
    @file io.c
    @author William J Krjacovic (wjkrajco)
    This is the io function it has three different function. One function that countlines
    and ensures each line has less 100 characters and returns
    the number of lines in a file. One function that reads the lines of a file
    and stores the lines in a string returing true if another line can be read and false if not
    and a function that prints a string out with characters is specified colors.
*/

#include "io.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int countLines( FILE *fp )
{
  char ch;
  int charCounter = 0;
  int lineCounter = 0;
  while ( ( ch = fgetc( fp ) ) != EOF )  {
    charCounter++;
    if ( ch == '\n' ) {
      lineCounter++;
      charCounter = 0;
    }
    if ( charCounter >= LINE_LIMIT )  {
      fprintf(stderr, "Input line too long\n");
      exit(1);
    }
  }
  return lineCounter;
}

bool readLine( FILE *fp, char line[ LINE_LIMIT + 1 ] )
{
  char ch;
  int indexCounter = 0;
  while ( ( ch = fgetc( fp ) ) != EOF )  {
    if ( ch == '\n')  {
      line[indexCounter] = '\0';
      if ( ( ch = fgetc( fp ) ) != EOF )  {
        ungetc(ch, fp);
        return true;
      }
      return false;
      
    }
    line[indexCounter] = ch;
    indexCounter++;
  }
  return false;
}

void printLine( char line[ LINE_LIMIT + 1 ], int color[ LINE_LIMIT ] )  
{
  for (int i = 0; i < LINE_LIMIT; ++i)  {
    if (color[i] == IDENT_COLOR)  {
      putchar(FIRST_HEXADECIMAL_COLOR);
      putchar(SECOND_HEXADECIMAL_COLOR);
      putchar(THIRD_HEXADECIMAL_COLOR);
      putchar(FOURTH_HEXADECIMAL_RED);
      putchar(FINAL_HEXADECIMAL_COLOR);
      printf("%c", line[i]);
    }
    if (color[i] == DEFAULT_COLOR)  {
      putchar(FIRST_HEXADECIMAL_COLOR);
      putchar(SECOND_HEXADECIMAL_COLOR);
      putchar(THIRD_HEXADECIMAL_NORMAL);
      putchar(FINAL_HEXADECIMAL_COLOR);
      printf("%c", line[i]);
    }
    if (color[i] == OP_COLOR)  {
      putchar(FIRST_HEXADECIMAL_COLOR);
      putchar(SECOND_HEXADECIMAL_COLOR);
      putchar(THIRD_HEXADECIMAL_COLOR);
      putchar(FOURTH_HEXADECIMAL_BLUE);
      putchar(FINAL_HEXADECIMAL_COLOR);
      printf("%c", line[i]);
    }
  }
}
