#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE 100

typedef struct {
    int itens[MAX_QUEUE];
    int front;
    int rear;
} Queue;

void init(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int enqueue(Queue *q, int valor) {
    if (full(q)) {
        return 0;
    }
    q->itens[q->rear++] = valor;
    return 1;
}

int dequeue(Queue *q, int *valor) {
    if (empty(q)) {
        return 0;
    }
    *valor = q->itens[q->front++];
    return 1;
}

int empty(Queue *q) {
    return q->front == q->rear;
}

int full(Queue *q) {
    return q->rear == MAX_QUEUE;
}

int front(Queue *q, int *valor) {
    if (empty(q)) {
        return 0;
    }
    *valor = q->itens[q->front];
    return 1;
}


#endif
