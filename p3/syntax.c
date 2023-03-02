/** 
    @file syntax.c
    @author William J Krjacovic (wjkrajco)
    This is the sytax file that ensures the identifier provided for the file
    is valid and also reads through lines of the file. The function markIdentifier
    reads the next line in the file and returns a int array of where the color of characters
    should be either default or red the words that match the wanted identifier.
*/
#include "syntax.h"
#include <string.h>

#include "io.h"

/** The smallest ASCII value for a lower case letter.*/
#define SMALLEST_LETTER_LOWER 65

/** The largest ASCII value for a lower case letter.*/
#define LARGEST_LETTER_LOWER 90

/** The smallest ASCII value for a upper case letter.*/
#define SMALLEST_LETTER_UPPER 97

/** The largest ASCII value for a upper case letter.*/
#define LARGEST_LETTER_UPPER 122

/** ASCII value for underscore.*/
#define UNDERSCORE 95

/** The ASCII value for the smallest digit */
#define DIGIT_MINIMUM 48

/** The ASCII value for the largest digit */
#define DIGIT_MAXIMUM 57



bool validIdentifier( char ident[] )  
{
  if (!((( int )ident[0] >= SMALLEST_LETTER_LOWER && ( int )ident[0] <= LARGEST_LETTER_LOWER) ||
   (( int )ident[0] >= SMALLEST_LETTER_UPPER && ( int )ident[0] <= LARGEST_LETTER_UPPER ) || (( int )ident[0] == UNDERSCORE ))) {
    return false;
  }
  for (int i = 1; i < strlen( ident ); i++)  {
    if (!((ident[i] >= SMALLEST_LETTER_LOWER && ident[i] <= LARGEST_LETTER_LOWER) ||
     (ident[i] >= SMALLEST_LETTER_UPPER && ident[i] <= LARGEST_LETTER_UPPER) || (ident[i] == UNDERSCORE) ||
      (ident[i] >= DIGIT_MINIMUM && ident[i] <= DIGIT_MAXIMUM))) {
      return false;
    }

  }
  return true;
}

bool markIdentifier(char word[], char line[], int color[]) {
    int innerCounter = 0;
    int wordLength = strlen(word);
    int lineLength = strlen(line);
    bool foundWord = false;
    bool result = false;

    for (int i = 0; i < lineLength; i++) {
        if (foundWord && (innerCounter > 0)) {
            color[i] = IDENT_COLOR;
            innerCounter--;
            result = true;
        } else {
            if ((wordLength == 1) && (word[0] == line[i])) {
                color[i] = IDENT_COLOR;
                result = true;
            } else {
                if ((word[0] == line[i]) && ((lineLength - i - 1) >= wordLength)) {
                    bool matched = true;
                    for (int j = 1; j < wordLength; j++) {
                        if (!((line[i + j] >= 'a' && line[i + j] <= 'z') ||
                              (line[i + j] >= 'A' && line[i + j] <= 'Z') ||
                              (line[i + j] >= '0' && line[i + j] <= '9') ||
                              (line[i + j] == '_'))) {
                            matched = false;
                            break;
                        }
                        if (word[j] != line[i + j]) {
                            matched = false;
                            break;
                        }
                        innerCounter = j;
                        if (innerCounter == wordLength - 1) {
                            foundWord = true;
                        }
                    }
                    if (foundWord && matched) {
                        for (int j = i; j < i + wordLength; j++) {
                            color[j] = IDENT_COLOR;
                        }
                        result = true;
                    } else {
                        color[i] = DEFAULT_COLOR;
                    }
                } else {
                    color[i] = DEFAULT_COLOR;
                }
            }
        }
    }
    return result;
}
