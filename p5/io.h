/** 
    @file io.h
    @author William J Krjacovic (wjkrajco)
    This is the header file for io.c which will be dealing with the reading
    of writing of the file for encryption and decryption.
*/

#include "field.h"

/** The expected size for the binary files*/
#define USUAL_BINARY_SIZE 16


/** 
    This function takes in a filename and a size and reads a binary
    file and puts the values in a dynamically allocated array and returns a
    pointer to that array.

    @param filename The file that will be read and its contents be put into that array.
    @param size The size of the file being read
    @return A pointer to the array of information
*/
byte *readBinaryFile(char const *filename, int *size);

/** 
    This function takes in a file name, a pointer to an array of data and the size which tells
    how many bytes are in the data array. The function writes the array to the file give

    @param filename The file that will be written to.
    @param data An array of bytes that will be use to written.
    @param size The number of bytes in the data array.
*/
void writeBinaryFile( char const *filename, byte *data, int size );
