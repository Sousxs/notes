//
//  listaCircular.c - Lista ordenada em vetor circular com busca binária
//
//  1) Lista circular usando aritmética modular (%) para contornar índices
//  2) Busca binária para consulta/posição de inserção
//  3) Diferenciação vazia/cheia resolvida com contador n
//

#include <stdio.h>

#define TAM 10

typedef struct Lista {
    int elem[TAM];
    int inicio;  
    int n;       
} Lista;

static inline int idx(const Lista *lista, int k) {
    return (lista->inicio + k) % TAM;
}

void criaLista(Lista *lista) {
    lista->inicio = 0;
    lista->n = 0;
}

int listaVazia(const Lista *lista) {
    return lista->n == 0;
}

int listaCheia(const Lista *lista) {
    return lista->n == TAM;
}

int tamanhoLista(const Lista *lista) {
    return lista->n;
}

int buscaBinaria(const Lista *lista, int valor) {
    int l = 0, r = lista->n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        int vm = lista->elem[idx(lista, m)];
        if (vm == valor) return m;
        if (vm < valor) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

int posicaoInsercao(const Lista *lista, int valor) {
    int l = 0, r = lista->n; // intervalo [l, r)
    while (l < r) {
        int m = l + (r - l) / 2;
        int vm = lista->elem[idx(lista, m)];
        if (vm < valor) l = m + 1;
        else r = m;
    }
    return l;
}

int consulta(const Lista *lista, int valor) {
    int k = buscaBinaria(lista, valor);
    return (k >= 0) ? (k + 1) : 0;
}

void listar(const Lista *lista) {
    if (listaVazia(lista)) {
        printf("Lista vazia!\n");
        return;
    }
    for (int k = 0; k < lista->n; k++) {
        printf("%d  ", lista->elem[idx(lista, k)]);
    }
    printf("\n");
}

void inserir(Lista *lista, int valor) {
    if (listaCheia(lista)) return;

    int i = posicaoInsercao(lista, valor);

    if (i < lista->n - i) {
        lista->inicio = (lista->inicio - 1 + TAM) % TAM;
        for (int k = 0; k < i; k++) {
            lista->elem[idx(lista, k)] = lista->elem[idx(lista, k + 1)];
        }
        lista->elem[idx(lista, i)] = valor;
    } else {
        for (int k = lista->n; k > i; k--) {
            lista->elem[idx(lista, k)] = lista->elem[idx(lista, k - 1)];
        }
        lista->elem[idx(lista, i)] = valor;
    }
    lista->n++;
}

int remover(Lista *lista, int pos) {
    if (pos <= 0 || pos > lista->n) return 0;

    int i = pos - 1;
    int valor = lista->elem[idx(lista, i)];

    if (i < (lista->n - 1 - i)) {
        for (int k = i; k > 0; k--) {
            lista->elem[idx(lista, k)] = lista->elem[idx(lista, k - 1)];
        }
        lista->inicio = (lista->inicio + 1) % TAM;
    } else {
        for (int k = i; k < lista->n - 1; k++) {
            lista->elem[idx(lista, k)] = lista->elem[idx(lista, k + 1)];
        }
    }
    lista->n--;
    return valor;
}

int main(void) {
    Lista l1;
    int dado;
    int i, opc;

    criaLista(&l1);

    do {
        printf("1 - Inserir\n2 - Remover\n3 - Consultar\n4 - Listar\n5 - Terminar\n\nOpção [ ]\b\b");
        if (scanf("%d", &opc) != 1) return 0;

        switch (opc) {
            case 1:
                if (listaCheia(&l1))
                    printf("Lista cheia!\nNão é possível inserir.\a\a\a\n");
                else {
                    printf("Valor a ser inserido: ");
                    if (scanf("%d", &dado) != 1) return 0;
                    inserir(&l1, dado);
                    printf("Feito!\n");
                }
                break;
            case 2:
                if (listaVazia(&l1)) {
                    printf("Lista vazia!\n");
                    break;
                }
                printf("Valor a ser removido: ");
                if (scanf("%d", &dado) != 1) return 0;
                i = consulta(&l1, dado);
                if (i == 0)
                    printf("%d não consta na lista.\a\a\a\n", dado);
                else {
                    dado = remover(&l1, i);
                    printf("%d foi removido.\n", dado);
                }
                break;
            case 3:
                printf("Valor a ser consultado: ");
                if (scanf("%d", &dado) != 1) return 0;
                i = consulta(&l1, dado);
                if (i == 0)
                    printf("%d não consta na lista.\a\a\a\n", dado);
                else
                    printf("%d está na posição %d da lista.\n", dado, i);
                break;
            case 4:
                listar(&l1);
                break;
            default:
                break;
        }
    } while (opc != 5);

    printf("\n\nF I M\n\n");
    return 0;
}