#include "Header.h"
#include <stdlib.h>
#include <stdio.h>

// Initialize queue
void init_queue(Queue *q)
{
    q->BegQ = q->EndQ = NULL;
}

// Add element to queue
void add_element(Queue *q, int inf)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Memory allocation error\n");
        exit(1);
    }
    new_node->inf = inf;
    new_node->link = NULL;

    if (!q->EndQ)
    {
        q->BegQ = q->EndQ = new_node;
    }
    else
    {
        q->EndQ->link = new_node;
        q->EndQ = new_node;
    }
}

// Remove element from queue
int del_element(Queue *q)
{
    if (is_empty(q))
    {
        printf("Queue is empty\n");
        exit(1);
    }

    Node *temp = q->BegQ;
    int inf = temp->inf;
    q->BegQ = q->BegQ->link;

    if (!q->BegQ)
    {
        q->EndQ = NULL;
    }

    free(temp);
    return inf;
}

// Check if queue is empty
int is_empty(Queue *q)
{
    return q->BegQ == NULL;
}

// Print queue contents
void print_queue(Queue *q)
{
    Node *current = q->BegQ;
    printf("Queue: ");
    while (current)
    {
        printf("%d ", current->inf);
        current = current->link;
    }
    printf("\n");
}

// Free memory of queue
void free_queue(Queue *q)
{
    while (!is_empty(q))
    {
        del_element(q);
    }
}

