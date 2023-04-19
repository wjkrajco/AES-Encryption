/** 
    @file queue.c
    @author William J Krjacovic (wjkrajco)
    This is the queue class. This class has the repsonsibility of creating, working with
    and free the queue of the program. This class will deal with enqueue, dequeue and promote funcitons.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "queue.h"

Queue *makeQueue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = &(queue->head);
    return queue;
}

void enqueue( Queue *q, Node *n )
{
    n->next = NULL;

    if (!q->head)  {
        q->head = n;
        q->tail = &n->next;
    }
    else {
        *q->tail = n;
        q->tail = &n->next;
    }
}

Node *dequeue( Queue *q )
{
    if (!q->head)  {
        return NULL;
    }
    
    Node *n = q->head;
    q->head = q->head->next;
    if (q->head == NULL)  {
        q->tail = NULL;
    }

    n->next = NULL;
    return n;
}

bool promote(Queue *q, Node const *example)
{
    if (!example || !q || !q->head) {
        return false;
    }

    if (q->head->equals(q->head, example)) {
        return true;
    }

    Node *current = q->head;
    Node *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;

        // current->print(current);
        // printf("%c", '\n');
        // example->print(example);

        if (current->equals(current, example)) {
            prev->next = current->next;
            current->next = q->head;
            q->head = current;

            if (q->tail == &(current->next)) {
                q->tail = &(prev->next);
            }

            return true;
        }
    }
    return false;
}

void freeQueue( Queue *q )
{
    if (q)  {
        Node *current = q->head;
        while (current)  {
            Node *nextNode = current->next;
            free(current);
            current = nextNode;
        }
        free(q);
    }
}
