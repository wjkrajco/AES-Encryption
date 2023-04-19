/**
   @file types.c
   @author William Krajcovic
   Implementation of linked list nodes for int values, real values
   (doubles) and string values.
*/

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "types.h"
#include "queue.h"


/** Holds the base for the ints being used which will be based 10*/
#define BASE_10 10

/** Length of 1 char and two quotation marks */
#define SMALLEST_STRING_AND_ONE 3

/** Smallest allowed string */
#define SMALLEST_STRING 2

/** The difference in double to allow for comparison*/
#define DOUBLE_DIFFERENCE 0.0001


/** 
    This function makes sure that the string has the quotation marks around
    the input if it is a string.

    @param str The string that is being checked
    @return True if the input has surrounding quotes and false if not
*/
/** 
    This function makes sure that the string has the quotation marks around
    the input if it is a string.

    @param str The string that is being checked
    @return True if the input has surrounding quotes and false if not
*/
static bool doesStringHaveQuotes(const char *str)
{
  if (str == NULL)  {
    return false;
  }

  const char *start = str;
  while (isspace(*start))  {
    ++start;
  }

  if (*start != '"')  {
    return false;
  }

  const char *end = str + strlen(str) - 1;
  while (isspace(*end) && end > start)  {
    --end;
  }

  if (*end != '"')  {
    return false;
  }

  return true; 
}

/** 
    This function takes in a Node and prints out the int value in it

    @param fp The node thats value will be printed
*/
static void printIntNode( Node const *n )
{
  printf( "%d", * (int *) ( n->data ) );
}

/** 
    This function takes in two nodes and compares their int values.

    @param a The first node that will be compared
    @param b The second node that will be compared
    @return True if the two nodes has the same value, and false if not.
*/
static bool equalsIntNode( Node const *a, Node const *b )
{
  return b->print == printIntNode &&
    * ( (int *) a->data ) == * ( (int *) b->data );
}

/** 
    This function takes in a Node and prints out the real value in it

    @param fp The node thats value will be printed
*/
static void printRealNode( Node const *n )
{
  printf("%.3lf", *(double *)(n->data));
}

/** 
    This function takes in two nodes and compares their Real values.

    @param a The first node that will be compared
    @param b The second node that will be compared
    @return True if the two nodes has the same value, and false if not.
*/
static bool equalsRealNode(Node const *a, Node const *b) {
    double epsilon = DOUBLE_DIFFERENCE;
    double diff = *((double *)a->data) - *((double *)b->data);
    return b->print == printRealNode && (diff < epsilon && diff > -epsilon);
}

/** 
    This function takes in a Node and prints out the String value in it

    @param fp The node thats value will be printed
*/
static void printStringNode(Node const *n) 
{
  char const *str = n->data;
  int len = strlen(str);

  if (len >= SMALLEST_STRING_AND_ONE) {
    char *tempBuffer = malloc(len - 1);

    strncpy(tempBuffer, str + 1, len - SMALLEST_STRING);

    tempBuffer[len - SMALLEST_STRING] = '\0';
    printf("%s", tempBuffer);
    free(tempBuffer);
  }
}

/** 
    This function takes in two nodes and compares their String values.

    @param a The first node that will be compared
    @param b The second node that will be compared
    @return True if the two nodes has the same value, and false if not.
*/
static bool equalsStringNode( Node const *a, Node const *b )
{
  return strcmp(a->data, b->data) == 0;
}



/** 
    This functions goes through a given string making sure that when parsed all of its
    data has been parsed and if not returns false to show the parsing was not valid.

    @param ptr The character pointer that will be parsed.
    @return True if the pointer has been fully parsed and false if not.
*/
static bool isValid(char *ptr)
{
  while (isspace(*ptr)) {
    ++ptr;
  }
  return *ptr == '\0';
}


Node *makeIntNode( char const *init )
{

  int result;
  char *ptr;
  result = strtol(init, &ptr, BASE_10);

  if (!isValid(ptr))  {
    return NULL;
  }
  // Allocate space for the node plus a little more for its value.
  Node *n = (Node *) malloc( sizeof( Node ) + sizeof( int ) );

  // Fill in the node's int (just 5 for now)
  * (int *) n->data = result;

  // Fill in pointers for its methods defined above.
  n->print = printIntNode;
  n->equals = equalsIntNode;
  return n;
}

Node *makeRealNode( char const *init )
{

  double result;
  char *ptr;
  result = strtod(init, &ptr);

  if (!isValid(ptr))  {
    return NULL;
  }
  // Allocate space for the node plus a little more for its value.
  Node *n = (Node *) malloc( sizeof( Node ) + sizeof( double ) );

  // Fill in the node's int (just 5 for now)
  * (double *) n->data = result;

  // Fill in pointers for its methods defined above.
  n->print = printRealNode;
  n->equals = equalsRealNode;
  return n;

}

Node *makeStringNode( char const *init )
{

  if (!doesStringHaveQuotes(init))  {
    return NULL;
  }
  Node *n = (Node *)malloc(sizeof(Node) + (strlen(init) + 1) * sizeof(char));
  strcpy(n->data, init);
  n->print = printStringNode;
  n->equals = equalsStringNode;
  return n;
}
