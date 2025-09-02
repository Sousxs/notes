#ifndef STACK_H
#define STACK_H

#define MAX_STACK 100

typedef struct {
    int itens[MAX_STACK];
    int top;
} Stack;

void init(Stack *p);

int push(Stack *p, int valor);

int pop(Stack *p, int *valor);

int empty(Stack *p);

int full(Stack *p);

int top(Stack *p, int *valor);

#endif