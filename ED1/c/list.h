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

int consulta(Lista lista, int valor){
    int i;
    i = lista.inicio;
    while(i<=lista.fim && lista.elem[i]<valor)
        i++;
    if(i>lista.fim || lista.elem[i]!=valor)
        return 0;
    // else
    return i-lista.inicio+1;
}

void listar(Lista lista){
    int i;
    if(listaVazia(lista))
        printf("Lista vazia!");
    else
        for(i=lista.inicio; i<=lista.fim; i++)
            printf("%d  ",lista.elem[i]);
    printf("\n");
}
void inserir(Lista *lista, int valor){ 
    int i, j;
    i = (*lista).inicio;
    while(i<=(*lista).fim && (*lista).elem[i]<valor)
        i++;
    if(i-(*lista).inicio <= (*lista).fim-i && (*lista).inicio>0 || (*lista).fim==tam-1){
        for(j=(*lista).inicio; j<i; j++)
            (*lista).elem[j-1] = (*lista).elem[j];
        (*lista).inicio--;
        (*lista).elem[i-1] = valor;
    }
    else{
        for(j=(*lista).fim; j>=i; j--)
            (*lista).elem[j+1] = (*lista).elem[j];
        (*lista).fim++;
        (*lista).elem[i] = valor;
    }
}

int remover(lista *lista, int pos){ /* A posição na lista (e não no vetor) a ser removida deve ser encontrada pela busca */
    int i, j;
    int valor;
    i = (*lista).inicio+pos-1; // transforma a posição da lista em posição do vetor
    valor = (*lista).elem[i];
    if(i-(*lista).inicio < (*lista).fim-i){
        for(j=i; j>(*lista).inicio; j--)
            (*lista).elem[j] = (*lista).elem[j-1];
        (*lista).inicio++;
    }
    else{
        (*lista).fim--;
        for(j=i; j<(*lista).fim; j++)
            (*lista).elem[j] = (*lista).elem[j+1];
    }
    return valor;
}

#endif
