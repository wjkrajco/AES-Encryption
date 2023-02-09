/** 
    @file number.h
    @author William J Krjacovic (wjkrajco)
    This is the header file for number_10 and number_12 and will provide
    the block comments for the two .c files 
*/

/** Exit status indicating that the program was given invalid input. */
#define FAIL_INPUT 102

/** Allows digits to move from one place to another, which allows for the parsing of a value.*/
#define MOVE_A_PLACE 10

/** A twelve for the the based twelve system*/
#define BASE_TWELEVE 12

/** Value for the letter X in the base 12 system*/
#define X_BASE_TWELVE_VALUE 10

/** Value for the letter E in the base 12 system*/
#define E_BASE_TWELVE_VALUE 11

/** 
    This is the skip_space function that reads in inputs of white spaces so the program
    can easily skip past any white space. If the input is not white space it reutrns what 
    was read in and if it is a new line or EOF then EOF is returned.

    @return The non-whitespace character inputed, or EOF if an EOF or new line is read.
*/
int skip_space();


/** 
    This is the parse_value function, which has the job of parsing the input as numbers and returning them as a long
    number, this is able parse in both base 10 and base 12 given on which class is called to parse the input

    @return The long value that was parsed and exit with 102 if there was an invalid input.
*/
long parse_value();

/** 
    This is the print_value function which takes in a long val and will print it out digit by digit in either base 10
    or base 12 depending on the class calling the function. It accomplishes this through a recursive call the its own function.

    @param val The long value that is being printed out.
*/
void print_value ( long val );
