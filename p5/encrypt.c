/** 
    @file encrypt.c
    @author William J Krjacovic (wjkrajco)
    This file holds the main functions. This is where the arguments are error checked.
    The read function are called on the file names and the encrypt function is called.
*/

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "field.h"
#include "aes.h"

/**The number of arguments to expected*/
#define NUM_ARGUMENTS 3

/**The multiples of 16 bytes that every file size should be*/
#define SIXTEEN_BYTES 16

/** 
    This function gets the size of the file, which would be the number of bytes that will be taken up in the array.
    This is designed for the extra credit to help with when to know to add padding.
    @param filename the name of the file being checked with size.
    @return the number of bytes in the file.
*/
static int getFileSize(char const *filename)  
{
    int fileSize = 0;
    FILE *fp = fopen(filename, "rb");
    if (!fp)  {
        fprintf(stderr, "Can't open file: %s\n", filename);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);
    fclose(fp);

    return fileSize;
}

int main(int argc, char *argv[])
{
    int numberOfBlocks = 0;

    if ((argc - 1) != NUM_ARGUMENTS)  {
        fprintf(stderr, "usage: encrypt <key-file> <input-file> <output-file>\n");
        exit(1);
    }

    int keySize = 0;
    keySize = getFileSize(argv[1]);
    if (keySize != SIXTEEN_BYTES)  {
        fprintf(stderr, "Bad key file: %s\n", argv[1]);
        exit(1);
    }
    byte *keyArr = readBinaryFile(argv[1], &keySize);
    if (keySize != SIXTEEN_BYTES)  {
        fprintf(stderr, "Bad key file: %s\n", argv[1]);
        exit(1);
    }

    int plainTextSize = 0;
    byte *plainArr = readBinaryFile(argv[NUM_ARGUMENTS - 1], &plainTextSize);
    if ((plainTextSize % SIXTEEN_BYTES) != 0)  {
        fprintf(stderr, "Bad plaintext file length: %s\n", argv[NUM_ARGUMENTS - 1]);
        exit(1);
    }

    numberOfBlocks = plainTextSize / SIXTEEN_BYTES;

    for (int i = 0; i < numberOfBlocks; i++) {
        encryptBlock(plainArr + i * SIXTEEN_BYTES, keyArr);
    }


    writeBinaryFile(argv[NUM_ARGUMENTS], plainArr, plainTextSize);

    free(keyArr);
    free(plainArr);

    return EXIT_SUCCESS;
}
