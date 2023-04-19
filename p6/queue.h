/** 
    @file queue.h
    @author William Krajcovic (wjkrajco)
    Header file for queue, a generic implementation of a linked list.
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/** Node containing an arbitrary value. */
typedef struct NodeStruct {
  /** Pointer to a function that prints the value in this node.
      @param n Pointer to the node containing the value to print. */
  void (*print)( struct NodeStruct const *n );

  /** Compare the value in the two given nodes, returning true
      if it's considered equivalent.
      @param a Pointer to the left-hand node to compare (the one
      containing this compare function)
      @param b Poitner to the right-hand node to compare.
      @return pointer to a new queue. */
  bool (*equals)( struct NodeStruct const *a,
                  struct NodeStruct const *b );

  /** Pointer to the next node on the queue. */
  struct NodeStruct *next;
  
  /** Contents of the node.  Whenever we allocate a node, we reserve some
      extra space at the end for holding the contents.  This field evaluates
      to a pointer to the start of that extra space. */
  char data[];
} Node;

/** Representation of a queue of generic values. */
typedef struct {
  /** Pointer to the first node in the queue. */
  Node *head;
  
  /** Address of the null pointer at the end of this queue, either
      pointing to the head pointer or pointing to the next pointer
      inside the last node. */
  Node **tail;
} Queue; 

/** 
    This function makes an empty, dynamically allocated queue, 
    initializing its fields.

    @return A pointer to the newly created queue
*/
Queue *makeQueue();

/** 
    This function adds the given node to the back of the given queue

    @param q The queue that will be used to add to the end of.
    @param n Node that will be added to the end of the queue
*/
void enqueue( Queue *q, Node *n );

/** 
    This function removes the node at the front of the given queue, returning it to the caller.
    If the queue is empty, it should return NULL.

    @param q The queue that will be manipulated to be dequeued.
    @return The first node of q that will be dequeued or null if the queue is empty
*/
Node *dequeue( Queue *q );

/** 
    This function finds the first node in the queue with a value that matches example.
    It moves the node to the front of the queue and returns true. If there’s no matching node, it returns false.

    @param q The queue that will be manipulated to promote the node.
    @param example The node example that should be promoted if in the queue.
    @return True if there was a matching node and false if there was no matching node.
*/
bool promote( Queue *q, Node const *example );

/** 
    This function frees all the memory used to store the given queue, including the memory for each of the nodes.

    @param q The queue where the memory will be freed.
*/
void freeQueue( Queue *q );

#endif
