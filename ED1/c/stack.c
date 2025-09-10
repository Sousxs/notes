#include "stack.h"

void init(Stack *p) {
    p->top = -1;
}

int push(Stack *p, int valor) {
    if (full(p)) {
        return 0;
    }
    p->itens[++(p->top)] = valor;
    return 1;
}

int pop(Stack *p, int *valor) {
    if (empty(p)) {
        return 0;
    }
    *valor = p->itens[(p->top)--];
    return 1;
}

int empty(Stack *p) {
    return p->top == -1;
}

int full(Stack *p) {
    return p->top == MAX_STACK - 1;
}

int top(Stack *p, int *valor) {
    if (empty(p)) {
        return 0;
    }
    *valor = p->itens[p->top];
    return 1;
}
