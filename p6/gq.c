/** 
    @file gq.c
    @author William J Krjacovic (wjkrajco)
    This class holds the main function and calls to other classes to control
    the functionality of the program.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "types.h"
#include "queue.h"
#include "input.h"



/** Holds the size for the char array for the first command*/
#define SIZE_FOR_FIRST_COMMAND 10

/** The number of commands given at a time that are allowed*/
#define MAX_INPUTS_ALLOWED 2

/** Value for numbers of base 10*/
#define BASE_10 10

/** Int value used to represent a string*/
#define INT_STRING_REPRESENTATION 3

/** Int value used to represent a realValue*/
#define INT_REALVALUE_REPRESENTATION 2


/** List of all the node creation functions.  This is a chain of
    responsibility; we can keep trying these functions until we find
    one that knows how to parse the init string. */
static Node *(*nodeMakers[])( char const *init ) = {
  makeIntNode,
  makeRealNode,
  makeStringNode
};


/** 
    This function takes in a queue and returns the length of the queue as an int.

    @param q The queue that will have its length taken.
    @return The length of the queue as an int.
*/
static int length(Queue *q)
{
  if(!q->head)  {
    return 0;
  }

  Node *current = q->head;
  int counter = 0;
  while(current)  {
    current = current->next;
    counter++;
  }
  free(current);
  return counter;

}

/** 
    This function takes off the white space at the beginning and end of the input.

    @param str The string that will have its white space take away.
*/
static void takeOffWhiteSpace (char *str)
{
  if (str == NULL) {
    return;
  }

  char *start = str;
  while (isspace((unsigned char)*start)) {
    ++start;
  }

  if (*start == '\0') {
    *str = '\0';
    return;
  }

  if (start != str) {
    memmove(str, start, strlen(start) + 1);
  }

  char *end = str + strlen(str) - 1;
  while (isspace((unsigned char)*end) && end > str) {
    --end;
  }
  end[1] = '\0';
}


/** 
    This is the main function. It runs a while loop that takes in input and only
    ends when given quit and calls to other classes queue, input and types
    to handle the functionality of promote dequeue queue and length for a created queue.

    @param argc The number of arguments provided
    @param argv The array of arguments given
    @return 0 if exit was successful and 1 if not
*/
int main(int argc, char *argv[])
{
  Queue *queue = makeQueue();

  char *line;
  while (1)  {
    printf("cmd> ");
    if ((line = readLine(stdin)) == NULL)  {
      freeQueue(queue);
      exit(0);
    }


    char first[SIZE_FOR_FIRST_COMMAND];
    memset(first, '\0', sizeof(first));
    char second[SIZE_FOR_FIRST_COMMAND];
    memset(second, '\0', sizeof(second));
    char third[SIZE_FOR_FIRST_COMMAND];
    memset(second, '\0', sizeof(second));
  
    if (line == NULL) {
      freeQueue(queue);
      exit(1);
    }

    printf("%s\n", line);
    if (sscanf(line, "%s %s %s", first, second, third) == 0)  {
      printf("%s\n\n", "Invalid command");
      free(line);
      continue;
    }
    else if (sscanf(line, "%s %s %s", first, second, third) == 1)  {
      if (strcmp(first, "quit") == 0)  {
        free(line);
        freeQueue(queue);
        exit(0);
      }
      else if (strcmp(first, "length") == 0)  {
        printf("%d\n\n", length(queue));
        free(line);
        continue;
      }
      else if (strcmp(first, "dequeue") == 0)  {
        Node *dequeuedNode = dequeue(queue);
        if (dequeuedNode != NULL) {
          dequeuedNode->print(dequeuedNode);
          free(dequeuedNode);
          printf("%c", '\n');
          printf("%c", '\n');

        }
        else {
          printf("%s\n\n", "Invalid command");
        }
        free(line);
        continue;
      }
      else {
        printf("%s\n\n", "Invalid command");
        free(line);
        continue;
      }
    }
    else if (sscanf(line, "%s %[^\n]", first, second) >= MAX_INPUTS_ALLOWED)  {
      takeOffWhiteSpace(second);
      if (strcmp(first, "enqueue") == 0) {
        Node *node = NULL;
      for (int i = 0; i < sizeof(nodeMakers) / sizeof(nodeMakers[0]); ++i) {
        node = nodeMakers[i](second);
        if (node) {
          break;
        }
      }

      if (node) {
        enqueue(queue, node);
        printf("%c", '\n');
      } else {
        printf("%s\n\n", "Invalid command");
      }
      free(line);
      continue;
      }
      else if (strcmp(first, "promote") == 0) {
        Node *node = NULL;
        for (int i = 0; i < sizeof(nodeMakers) / sizeof(nodeMakers[0]); ++i) {
          node = nodeMakers[i](second);
          if (node) {
            break;
          }
        }

        if (node) {
          if (promote(queue, node)) {
            printf("%c", '\n');
          } else {
            printf("%s\n\n", "Invalid command");
          }
          free(node);
        }  else {
          printf("%s\n\n", "Invalid command");
        }
        free(line);
        continue;
      }
      else {
        printf("%s\n\n", "Invalid command");
        free(line);
        continue;
      }
    }
    // else {
    //   printf("%s\n\n", "Invalid commandssss");
    //   free(line);
    //   continue; 
    // }

  }
  freeQueue(queue);
  return EXIT_SUCCESS;

}
