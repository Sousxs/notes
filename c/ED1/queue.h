#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE 100

typedef struct {
    int itens[MAX_QUEUE];
    int front;
    int rear;
} Queue;

void init(Queue *q);

int enqueue(Queue *q, int valor);

int dequeue(Queue *q, int *valor);

int empty(Queue *q);

int full(Queue *q);

int front(Queue *q, int *valor);

#endif
