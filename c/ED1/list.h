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


#endif
