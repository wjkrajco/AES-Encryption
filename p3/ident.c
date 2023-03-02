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

/** Lines of context to show around an identifier. */
static int context = 0;

/** True if we're printing line numbers. */
static bool numbers = false;
  
/** True if we're showing operators (for the extra credit). */
// static bool operators = false;

/** 
    This function processes the arguments that were passed into the program specifically only the optional
    arguments so whether or not to print the number of lines, if to give context and how much context to give.

    @param argc This is the number of arguments that were passed into the program.
    @param argv This is an array of pointers to the strings that were passed in to the program.
*/
static void processArgs( int argc, char *argv[] )  
{
  bool contextBool = false;
  bool isNum = false;
  bool isCurrentNum = false;

  if ( ( argc - 1 ) > REQUIRED_ARGS ) {
    for ( int i = 1; i < argc - REQUIRED_ARGS; i++ )  {
      for ( int j = 0; j < strlen( argv[i] ); j++ )  {
        if ( ( int )argv[i][j] >= DIGIT_MINIMUM && ( int )argv[i][j] <= DIGIT_MAXIMUM )  {
          if ( !contextBool )  {
            fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
            exit(1);
          }
          else  {
            isCurrentNum = true;
            isNum = true;
          }

        }
        if (isCurrentNum)  {
          fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
          exit(1);
        }
        isCurrentNum = false;
      }

      if (isNum)  {
        context = atoi(argv[i]);
      }

      else if ( strcmp(argv[i], "-n") == 0 )  {
        numbers = true;
      }
      else if ( strcmp(argv[i], "-c") == 0 )  {
        contextBool = true;
      }
      else  {
        fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
        exit(1);
      }
    }
  }
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
// int main( int argc, char *argv[] )  
// {
//   processArgs( argc, argv );

//   if ( ( argc - 1 ) < REQUIRED_ARGS )  {
//     fprintf( stderr, "usage: ident [-c <context>] [-n] <file> <identifier>\n" );
//     exit(1);
//   }
//   FILE *fp = fopen( argv[argc - REQUIRED_ARGS], "r" );
//   if ( !fp )  {
//     fprintf( stderr, "Can't open file: %s\n", argv[argc - REQUIRED_ARGS] );
//     exit(1);
//   }

//   if ( !validIdentifier( argv[argc - 1] ) )  {
//     fprintf( stderr, "Invalid identifier: %s\n", argv[argc - 1] );
//     exit( 1 );
//   }

//   int numLines = countLines( fp );

//   if ( context > 0 )  {
//     char historyArr[context][LINE_LIMIT + 1];
//     char line[LINE_LIMIT + 1];
//     int color[LINE_LIMIT];
//     int lineCounter = 0;
//     int lineNumberCounter = 0;
//     while ( readLine( fp, line ) )  {
//       lineNumberCounter++;
//       if ( markIdentifier( argv[argc - 1], line, color )) {
//         if (numbers)  {
//           for ( int i = 0; i < lineCounter; i++ )  {
//             printf( "%*d: ", (lineNumberCounter - lineCounter + i), numLines);
//             printf( "%s", historyArr[i] );
//           }
//           printf( "%*d: ", lineNumberCounter, numLines);
//           printLine( line, color );
//           for ( int i = 0; i < context; i++ )  {
//             for ( int j = 0; j < LINE_LIMIT + 1; j++ )  {
//               historyArr[i][j] = '\0';
//             }
//           }
//         }
//         else  {
//           for ( int i = 0; i < lineCounter; i++ )  {
//             printf( "%s", historyArr[i] );
//           }
//           printLine( line, color );
//           for ( int i = 0; i < context; i++ )  {
//             for ( int j = 0; j < LINE_LIMIT + 1; j++ )  {
//               historyArr[i][j] = '\0';
//               lineCounter = 0;
//             }
//           }
//         }

  
//       }
  
//       if ( lineCounter >= context )  {
//         for ( int i = 1; i < context; i++ )  {
//           strcpy( historyArr[i - 1], historyArr[i] );
//         }
//         strcpy(historyArr[context - 1], line);
//       }
//       else  {
//         strcpy(historyArr[lineCounter], line);
//         lineCounter++;
//       }
      
//     }
//   }
//   else  {
//     char line[LINE_LIMIT + 1];
//     int color[LINE_LIMIT];
//     int lineNumberCounter = 0;
//     while ( readLine( fp, line ) )  {
//       lineNumberCounter++;
//       if ( markIdentifier( argv[argc - 1], line, color )) {
//         if (numbers)  {
//           printf( "%*d: ", lineNumberCounter, numLines);
//           printLine( line, color );
//         }
//         else  {
//           printLine( line, color );
//         }
//       }
//     }
//   }
//   fclose(fp);



//   return EXIT_SUCCESS;
// }



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
  if ( context > 0 )  {
    char historyArr[context][LINE_LIMIT + 1];
    char line[LINE_LIMIT + 1];
    int color[LINE_LIMIT];
    int lineCounter = 0;
    int lineNumberCounter = 0;
    bool lastLineProcessed = false;
    while ( readLine( fp, line ) )  {
      lineNumberCounter++;
      if ( markIdentifier( argv[argc - 1], line, color )) {
        if (numbers)  {
          for ( int i = 0; i < lineCounter; i++ )  {
            printf( "%*d: ", (lineNumberCounter - lineCounter + i), numLines);
            printf( "%s", historyArr[i] );
          }
          printf( "%*d: ", lineNumberCounter, numLines);
          printLine( line, color );
          for ( int i = 0; i < context; i++ )  {
            for ( int j = 0; j < LINE_LIMIT + 1; j++ )  {
              historyArr[i][j] = '\0';
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
        lastLineProcessed = true;
  
      }
  
      if ( lineCounter >= context )  {
        for ( int i = 1; i < context; i++ )  {
          strcpy( historyArr[i - 1], historyArr[i] );
        }
        strcpy(historyArr[context - 1], line);
      }
      else  {
        strcpy(historyArr[lineCounter], line);
        lineCounter++;
      }
    }
    if (!lastLineProcessed && markIdentifier( argv[argc - 1], line, color )) {
      lineCounter++;
        if (numbers)  {
          for ( int i = 0; i < lineCounter; i++ )  {
            printf( "%*d: ", (lineNumberCounter - lineCounter + i), numLines);
            printf( "%s", historyArr[i] );
          }
          printf( "%*d: ", lineNumberCounter, numLines);
          printLine( line, color );
        }
        else  {
          for ( int i = 0; i < lineCounter; i++ )  {
            printf( "%s", historyArr[i] );
          }
          printLine( line, color );
        }
    }
  }
  else  {
    char line[LINE_LIMIT + 1];
    int color[LINE_LIMIT];
    int lineNumberCounter = 0;
    bool lastLineProcessed = false;
    while ( readLine( fp, line ) )  {
      lineNumberCounter++;
      if ( markIdentifier( argv[argc - 1], line, color )) {
        if (numbers)  {
          printf( "%*d: ", lineNumberCounter, numLines);
          printLine( line, color );
        }
        else  {
          printLine( line, color );
        }
        lastLineProcessed = true;
      }
    }
    if (!lastLineProcessed && markIdentifier( argv[argc - 1], line, color )) {
      lineNumberCounter++;
        if (numbers)  {
            printf( "%*d: ", lineNumberCounter, numLines);
            printLine( line, color );
          }
          else  {
            printLine( line, color );
          }
    }
  }
  return EXIT_SUCCESS;
}
