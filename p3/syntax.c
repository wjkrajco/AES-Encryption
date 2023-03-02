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

bool validIdentifier( char ident[] )  
{
  if (!((( int )ident[0] >= 65 && ( int )ident[0] <= 90) || (( int )ident[0] >= 97 && ( int )ident[0] <= 122 ) || (( int )ident[0] == 95 ))) {
    return false;
  }
  for (int i = 1; i < strlen( ident ); i++)  {
    if (!((ident[i] >= 65 && ident[i] <= 90) || (ident[i] >= 97 && ident[i] <= 122) || (ident[i] == 95) || (ident[i] >= 48 && ident[i] <= 57))) {
      return false;
    }

  }
  return true;
}

bool markIdentifier( char word[], char line[], int color[] )  
{
  int innerCounter = 0;
  int wordLength = strlen( word );
  int lineLength = strlen( line );
  bool foundWord = false;
  bool result = false;

  for ( int i = 0; i < lineLength; i++ )  {

    if ( foundWord && ( innerCounter > 0 ) )  {
      color[i] = IDENT_COLOR;
      innerCounter--;
      result = true;
    }
    else  {

      if ( ( wordLength == 1 ) && (word[0] == line[i]) )  {
        color[i] = IDENT_COLOR;
        result = true;
      }
      else {
        if (( word[0] == line[i] ) && (( lineLength - i - 1 ) >= wordLength ) )  {

          for ( int j = 1; j < wordLength; j++)  {
  
            if ( word[j] != line[i + j] )  {

              foundWord = false;
              break;
            }
            innerCounter = wordLength - 1;
            color[i] = IDENT_COLOR;
            foundWord = true;
          }
        }
        else  {
          color[i] = DEFAULT_COLOR;
        }
      }
    }
  }

  return result;
}
