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

/** This allows us to add to the current index of the word to get the 
 *  letter after the word to ensure they are matching and have valid before and after characters.
*/
#define GET_LETTER_AFTER_WORD 2

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

/** 
    This function takes in a character and checks if the character would be able to be at the
    end of an identifier and still allow the identifier to be to be valid.

    @param ch the character to be checked if it would change the identifier.
    @return true if the character is would change the identifier if it was at the end and false if not.
*/
static bool isAllowedEndCharacter(char ch)  
{
  if (!((ch >= SMALLEST_LETTER_LOWER && ch <= LARGEST_LETTER_LOWER) ||
  (ch >= SMALLEST_LETTER_UPPER && ch <= LARGEST_LETTER_UPPER) || (ch == UNDERSCORE) ||
    (ch >= DIGIT_MINIMUM && ch <= DIGIT_MAXIMUM))) {
      return true;
  }
  return false;
}

/** 
    This function takes in a character and checks if the character would be able to be at the
    start of an identifier and still allow the identifier to be to be valid.

    @param ch the character to be checked if it would change the identifier.
    @return true if the character is would change the identifier if it was at the start and false if not.
*/
static bool isAllowedStartCharacter(char ch)  
{
    if (!((ch >= SMALLEST_LETTER_LOWER && ch <= LARGEST_LETTER_LOWER) ||
   (ch >= SMALLEST_LETTER_UPPER && ch <= LARGEST_LETTER_UPPER ) || (ch == UNDERSCORE ))) {
    return true;
  }
  return false;
}

bool markIdentifier(char word[], char line[], int color[]) 
{
  int lineLength = strlen( line );
  int wordLength = strlen( word );
  int characterCounter = 0;
  char characterAfter;
  char characterBefore;
  bool wordFound = true;
  bool result = false;
  for (int i = 0; i < LINE_LIMIT; i++)  {
    color[i] = 0;
  }

  while (characterCounter < lineLength)  {
    if ((characterCounter == 0) && (lineLength - characterCounter) > wordLength)  {
      wordFound = true;
      characterCounter++;
      for (int i = 0; i < wordLength; i++)  {
        if (word[i] != line[i])  {
          wordFound = false;
        }
      }
      if (wordFound)  {
        characterAfter = line[wordLength];
        if (isAllowedEndCharacter(characterAfter))  {
          for (int i = 0; i < wordLength; i++)  {
            color[i] = IDENT_COLOR;
          }
          result = true;
        }
      }
  
    }
    else if (characterCounter > 0 && (lineLength - characterCounter) > wordLength)  {
      wordFound = true;
      characterCounter++;
      for (int i = (characterCounter - 1); i < (characterCounter + wordLength - 1); i++)  {
        if (word[i - characterCounter + 1] != line[i])  {
          wordFound = false;
        }
      }
      if (wordFound)  {
        characterAfter = line[characterCounter + wordLength - 1];
        characterBefore = line[characterCounter - GET_LETTER_AFTER_WORD]; 
        if (isAllowedEndCharacter(characterAfter) && isAllowedStartCharacter(characterBefore))  {
          for (int i = (characterCounter - 1); i < (characterCounter + wordLength - 1); i++)  {
            color[i] = IDENT_COLOR;
          }
          result = true;
        }
  
      }
  
    }
    else  {
      return result;
    }
  }
  return result;
}
