/** 
    @file sytax.h
    @author William J Krjacovic (wjkrajco)
    This is the header file for the io.c program and will provide the
    block comments and functions headers for the program.
*/

#include <stdio.h>
#include <stdbool.h>

/** 
    When given a string the function will return true it it is a legal identifier which is a string starting
    with a letter or underscore, followed by zero or more letters.

    @param ident A string that is to be checked if it s a legal identifier.
    @return true if the string is a legal identifier, and false if not.
*/
bool validIdentifier( char ident[] );

/** 
    Takes in a character array for word and a string for the line, the word is what is being searched for in the line. The color
    array will hold the color values that each character in the line should be. 

    @param word a character array that holds a word that is being looked for in the line
    @param line a line that is being searched through to try and find a word
    @param color the color array that corresponds to the color that each character in the line should be printed as
    @return true if the word was found in the line and false if not.
*/
bool markIdentifier( char word[], char line[], int color[] );
