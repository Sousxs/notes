#ifndef lista_H
#define lista_H

#define MAX_TAM 10

typedef struct {
    int elem[MAX_TAM];
    int inicio;
    int fim;
} lista;

void CriarLista(lista *l){
    l->inicio = 0;
    l->fim = l->inicio - 1;
}
int listaVazia(lista l){
    return l.fim < l.inicio;
}
int listaCheia(lista l){
    return l.fim == MAX_TAM - 1 && l.inicio == 0;
}
int consulta(lista l, int valor){
    int i;
    i = l.inicio;
    while (i <= l.fim) {
        if (l.elem[i] == valor) {
            return i;
        }
        i++;
    }
    return -1;
}
int inserir(lista *l, int valor){
    int i;
    if (listaCheia(*l)) {
        return 0;
    }
    if (l->fim < MAX_TAM - 1) {
        l->fim++;
        l->elem[l->fim] = valor;
        return 1;
    }
    return 0;
}
int remover(lista *l, int valor){
    int i, posicao;
    if (listaVazia(*l)) {
        return 0;
    }
    posicao = consulta(*l, valor);
    if (posicao == -1) {
        return 0;
    }
    for (i = posicao; i < l->fim; i++) {
        l->elem[i] = l->elem[i + 1];
    }
    l->fim--;
    return 1;
}
void imprimir(lista l){
    int i;
    if (listaVazia(l)) {
        printf("Lista vazia\n");
        return;
    }
    for (i = l.inicio; i <= l.fim; i++) {
        printf("%d ", l.elem[i]);
    }
    printf("\n");
}

#endif
