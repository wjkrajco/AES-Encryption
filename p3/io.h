/** 
    @file io.h
    @author William J Krjacovic (wjkrajco)
    This is the header file for the io.c program and will provide the
    block comments and functions headers for the program.
*/

#include <stdio.h>
#include <stdbool.h>

/** Maximum length of an input line. */
#define LINE_LIMIT 100

/** Used for element of the output line in the default color. */
#define DEFAULT_COLOR 0

/** Used for element of the output line colored like that target identifier. */
#define IDENT_COLOR 1

/** For the extra credit, this is the color value for operators  */
#define OP_COLOR 2

/** The first Hexcadeciaml code to print a color*/
#define FIRST_HEXADECIMAL_COLOR 0x1b

/** The second Hexcadeciaml code to print a color*/
#define SECOND_HEXADECIMAL_COLOR 0x5b

/** The third Hexcadeciaml code to print a color red or blue*/
#define THIRD_HEXADECIMAL_COLOR 0x33

/** The third Hexcadeciaml code to print normally*/
#define THIRD_HEXADECIMAL_NORMAL 0x30

/** The fourth Hexcadeciaml code to print red*/
#define FOURTH_HEXADECIMAL_RED 0x31

/** The fourth Hexcadeciaml code to print blue*/
#define FOURTH_HEXADECIMAL_BLUE 0x34

/** The final Hexcadeciaml code to print a color*/
#define FINAL_HEXADECIMAL_COLOR 0x6d

/** 
    This is the countLines function that takes in a FILE pointer and counts the
    number of lines in the file. It also counts the length of all the lines to see if they
    are longer than 100 then print "Input line too long" and exit with status 1.

    @param fp a pointer to a file that is going to be read.
    @return the number of lines that were counted in file.
*/
int countLines( FILE *fp );

/** 
    This function takes in a file and will read the next line and stores the line in the string.

    @param fp a pointer to a file that has the line going to be read.
    @param line a string that will store the line that is read.
    @return true if the line being read is valid, and false if the line is not valid.
*/
bool readLine( FILE *fp, char line[ LINE_LIMIT + 1 ]);

/** 
    Takes in a string of a line and prints the line in a color contained in the color array.

    @param line the string that will be printed.
    @param color the color array that holds the color of the string that will be printed.
*/
void printLine( char line[ LINE_LIMIT + 1], int color[ LINE_LIMIT ]);
