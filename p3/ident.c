/** 
    @file ident.c
    @author William J Krjacovic (wjkrajco)
    This is where the main function and a function to process the given arguments are held
    the function processArgs reads the arguments of the program and ensures the
    correct syntax was given so the program knows how many lines of conext to prove
    and if we need to print the number of lines. The mainfunction opens and closes
    the file and makes sure there are the two required arguments
    the main function also calls to all of the other functions to parse the file returning the given line needed.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "io.h"
#include "syntax.h"

/** Number of arguments required on the command line. */
#define REQUIRED_ARGS 2

/** The ASCII value for the smallest digit */
#define DIGIT_MINIMUM 48

/** The ASCII value for the largest digit */
#define DIGIT_MAXIMUM 57

/** A ten used to divide by number to take away the first digit in the int*/
#define BASE_10 10

/** Lines of context to show around an identifier. */
static int context = 0;

/** True if we're printing line numbers. */
static bool numbers = false;
  
/** True if we're showing operators (for the extra credit). */
static bool operators = false;

/** 
    Takes in a string from the argv[] array and check if all of the characters of the string at a given
    index are all integers and dif it can be converted to a number.

    @param index This is the index of the argument that is going to be check if it is a number
    @param argv This is an array of pointers to the strings that were passed in to the program.
    @return true if the string can be a number, and false if the string contains things other than digits and
      cannot be created as a number.
*/
static bool isNum(int index, char *argv[])  {
  bool isNum = true;
  for (int i = 0; i < strlen(argv[index]); i++)  {
    if (!((argv[index][i] >= DIGIT_MINIMUM) && (argv[index][i] <= DIGIT_MAXIMUM)))  {
      isNum = false;
    }
  }
  return isNum;
}

/** 
    This function processes the arguments that were passed into the program specifically only the optional
    arguments so whether or not to print the number of lines, if to give context and how much context to give.

    @param argc This is the number of arguments that were passed into the program.
    @param argv This is an array of pointers to the strings that were passed in to the program.
*/
static void processArgs( int argc, char *argv[] )  
{
  bool contextBool = false;

  if ((argc - 1) < REQUIRED_ARGS) { 
    fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
    exit(1);
  }
  for (int i = 1; i < argc - REQUIRED_ARGS; i++)  {
    if (strcmp("-n", argv[i]) == 0)  {
      numbers = true;
    }
    else if (strcmp("-o", argv[i]) == 0)  {
      operators = true;
    }
    else if (strcmp("-c", argv[i]) == 0)  {
      contextBool = true;
    }
    else if (isNum(i, argv) && contextBool)  {
      context = atoi(argv[i]);
    }
    else {
      fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
      exit(1);
    }


  }
}

/** 
    This is the countDigits function which takes in an int and returns the length of the int
    int terms of digits, so if 1000 is given in 4 is returned since ther are four digits.

    @param numLines the int that is taken in to count how many digits in the in.
    @return the number of digits in the int given
*/
static int countDigits(int numLines)  
{
  int digits = 0;
  while (numLines != 0)  {
    numLines = numLines / BASE_10;
    ++digits;
  }
  return digits;
}

/** 
    This is the main function of the program. This function calls to programs syntax and io to
    read through a file and retunt lines that have matches to a given identifier by a user and prints
    out those lines. It will print out the number of lines with matches as well as context around
    the lines if specified by the users arguments to the program.

    @param argc This is the number of arguments that were passed into the program.
    @param argv This is an array of pointers to the strings that were passed in to the program.
    @return EXIT_SUCESS if the program completes
*/
int main( int argc, char *argv[] )  
{
  processArgs( argc, argv );

  if ( ( argc - 1 ) < REQUIRED_ARGS )  {
    fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
    exit(1);
  }
  FILE *fp = fopen( argv[argc - REQUIRED_ARGS], "r" );
  if ( !fp )  {
    fprintf( stderr, "Can't open file: %s\n", argv[argc - REQUIRED_ARGS] );
    exit(1);
  }

  if ( !validIdentifier( argv[argc - 1] ) )  {
    fprintf( stderr, "Invalid identifier: %s\n", argv[argc - 1] );
    exit( 1 );
  }

  int numLines = countLines( fp );
  int digits = countDigits(numLines);

    char historyArr[context][LINE_LIMIT + 1];
    char line[LINE_LIMIT + 1];
    int nums[context];
    int color[LINE_LIMIT] = {0};
    int lineCounter = 0;
    int lineNumberCounter = 0;
    bool justPrinted = false;
    int counter = 0;



  if ( context > 0 )  {
    while ( readLine( fp, line ) )  {
      lineNumberCounter++;

      if (justPrinted)  {
        counter++;
        if (counter == context) {
          justPrinted = false;
        }
        if (markIdentifier( argv[argc - 1], line, color)) {
          justPrinted = false;
        }
        else {
          if (numbers) {
            printf( "%*d: ", digits, lineNumberCounter);
            printLine( line, color );
            continue;
          }
          else {
            printLine( line, color );
            continue;
          }
        }
        if (justPrinted) {
          continue;
        }
      }

      
      if ( markIdentifier( argv[argc - 1], line, color )) {
        counter = 0;
        justPrinted = true;
        if (numbers)  {
          for ( int i = 0; i < lineCounter; i++ )  {
            printf( "%*d: ", digits, nums[i]);
            printf( "%s", historyArr[i] );
          }
          printf( "%*d: ", digits, lineNumberCounter);
          printLine( line, color );
          for ( int i = 0; i < context; i++ )  {
            nums[i] = 0;
            for ( int j = 0; j < LINE_LIMIT + 1; j++ )  {
              historyArr[i][j] = '\0';
              lineCounter = 0;
            }
          }
        }
        else  {
          for ( int i = 0; i < lineCounter; i++ )  {
            printf( "%s", historyArr[i] );
          }
          printLine( line, color );
          for ( int i = 0; i < context; i++ )  {
            for ( int j = 0; j < LINE_LIMIT + 1; j++ )  {
              historyArr[i][j] = '\0';
              lineCounter = 0;
            }
          }
        }
  
      }

      else if ( lineCounter >= context )  {
        for ( int i = 1; i < context; i++ )  {
          strcpy( historyArr[i - 1], historyArr[i] );
          nums[i - 1] = nums[i] ;
        }
        strcpy(historyArr[context - 1], line);
        nums[context - 1] = lineNumberCounter;
      }
      else  {
        strcpy(historyArr[lineCounter], line);
        nums[lineCounter] = lineNumberCounter;
        lineCounter++;
      }
      
    }



    if ( markIdentifier( argv[argc - 1], line, color )) {
      lineNumberCounter++;
      if (numbers)  {
        for ( int i = 0; i < lineCounter; i++ )  {
          printf( "%*d: ", digits, nums[i]);
          printf( "%s", historyArr[i] );
        }
        printf( "%*d: ", digits, lineNumberCounter);
        printLine( line, color );
        for ( int i = 0; i < context; i++ )  {
          nums[i] = 0;
            for ( int j = 0; j < LINE_LIMIT + 1; j++ )  {
              historyArr[i][j] = '\0';
              lineCounter = 0;
            }
        }
      }
      else  {
        for ( int i = 0; i < lineCounter; i++ )  {
          printf( "%s", historyArr[i] );
        }
        printLine( line, color );
        for ( int i = 0; i < context; i++ )  {
          for ( int j = 0; j < LINE_LIMIT + 1; j++ )  {
            historyArr[i][j] = '\0';
            lineCounter = 0;
          }
        }
      }
    }
    else if (justPrinted)  {
      if (numbers) {
        printf( "%*d: ", digits, lineNumberCounter + 1);
        printLine( line, color );
      }
      else {
        printLine( line, color );
      }
    }


  }

  else {
    while ( readLine( fp, line ) )  {
      lineNumberCounter++;
      if ( markIdentifier( argv[argc - 1], line, color )) {
        if (numbers)  {
          printf( "%*d: ", digits, lineNumberCounter);
          printLine( line, color );
        }
        else  {
          printLine( line, color );
        }
      }
    }
    if (markIdentifier( argv[argc - 1], line, color )) {
      lineNumberCounter++;
      if (numbers)  {
        printf( "%*d: ", digits, lineNumberCounter);
        printLine( line, color );
      }
      else  {
        printLine( line, color );
      }
    }
    return EXIT_SUCCESS;
  }
}
