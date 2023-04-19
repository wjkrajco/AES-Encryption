/** 
    @file input.h
    @author William J Krjacovic (wjkrajco)
    This is the header file for Input which will take in the input from the user given a text
    file and will dynamically allocate memory for the use of the input.
*/

/** The initial capacity of the string used to read line */
#define INITIAL_CAPACITY 5

/** The number the capacity if multiplied when changing size */
#define STRING_MULTIPLICATION 2

/** 
    This function reads a single line of input from the given input stream (stdin or a file) and returns 
    it as a string inside a block of dynamically allocated memory.

    @param fp The file that is being read
    @return The str of the first line from the file.
*/
char *readLine (FILE *fp); 

// /** 
//     @file input.h
//     @author William J Krjacovic (wjkrajco)
//     This is the header file for Input which will take in the input from the user given a text
//     file and will dynamically allocate memory for the use of the input.
// */

// /** The initial capacity of the string used to read line */
// #define INITIAL_CAPACITY 5

// /** The number the capacity if multiplied when changing size */
// #define STRING_MULTIPLICATION 2

// /** 
//     This function reads a single line of input from the given input stream (stdin or a file) and returns 
//     it as a string inside a block of dynamically allocated memory.

//     @param fp The file that is being read
//     @return The str of the first line from the file.
// */
// char *readLine (FILE *fp); 
