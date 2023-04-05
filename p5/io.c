/** 
    @file io.c
    @author William J Krjacovic (wjkrajco)
    This is the io file and deals with reading in the binary files and
    writting the binary results to output files.
*/

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "field.h"

byte *readBinaryFile( char const *filename, int *size )
{ 
    FILE *fp = fopen(filename, "rb");
    if (!fp)  {
        fprintf(stderr, "Can't open file: %s\n", filename);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    rewind(fp);

    byte *values = (byte *)malloc((*size) * sizeof(byte));

    int numberOfValues = 0;
    while (numberOfValues < *size)  {
        int numbersRead = fread(&values[numberOfValues], sizeof(byte), *size - numberOfValues, fp);
        if (numbersRead <= 0)  {
            break;
        }
        numberOfValues += numbersRead;
    }
    fclose(fp);

    return values;
}

void writeBinaryFile(const char *filename, byte *data, int size) {
  FILE *fp = fopen(filename, "wb");

  if (fp != NULL) {
    fwrite(data, sizeof(byte), size, fp);
    fclose(fp);
  } else {
    fprintf(stderr, "Can't open file: %s\n", filename);
    exit(1);
  }
}
