#include "list.h"

void init(Lista *l) {
    l->inicio = 0;
    l->fim = 0;
}

int insert(Lista *l, int valor) {
    Node *novo = (Node *)malloc(sizeof(Node));
    if (novo == 0) {
        return 0;
    }
    novo->valor = valor;
    novo->proximo = 0;
    if (l->inicio == 0) {
        l->inicio = novo;
    } else {
        l->fim->proximo = novo;
    }
    l->fim = novo;
    return 1;
}

// Evite usar "remove" como nome de função
int remove_node(Lista *l, int valor) {
    Node *atual = l->inicio;
    Node *anterior = 0;
    while (atual != 0) {
        if (atual->valor == valor) {
            if (anterior == 0) {
                l->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            if (atual == l->fim) {
                l->fim = anterior;
            }
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0;
}

int search(Lista *l, int valor) {
    Node *atual = l->inicio;
    while (atual != 0) {
        if (atual->valor == valor) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void free_list(Lista *l) {
    Node *atual = l->inicio;
    while (atual != 0) {
        Node *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    l->inicio = 0;
    l->fim = 0;
}