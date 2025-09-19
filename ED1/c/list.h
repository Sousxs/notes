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
//consulta sequencial
/*
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
*/
//consulta binária
int consulta(lista l, int valor){
    int inicio = l.inicio;
    int fim = l.fim;
    int meio;
    while(inicio <= fim){
        meio = (inicio + fim) / 2;
        if(l.elem[meio] == valor){
            return meio;
        } else if (l.elem[meio] < valor){
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}
void inserir(lista *l, int valor){
   int i, j;
   i = l->inicio;
   while(i<=l->fim && l->elem[i]<valor){
       i++;
   }
   if(i - l->inicio <= l->fim -i && l->inicio > 0 || l->fim == MAX_TAM -1){
       for(j =l->inicio;j<i;j++){
           l->elem[j-1]=l->elem[j];
       }
       l->inicio--;
       l->elem[i-1]=valor;
   } else {
       for(j = l->fim; j >= i; j--){
           l->elem[j+1] = l->elem[j];
       }
       l->fim++;
       l->elem[i] = valor;
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

/*

Atividades/ Alterações
1. fazer a lista ser circular
    - evitar o uso de if, utilizando preferecialmente resto(%)
2. implementar a função de busca binária

3. contonar o problema de diferenciação de lista vazia e cheia
*/