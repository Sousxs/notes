#include <stdio.h>

typedef struct cell{
    int key;
    struct cell *next;
} cell;

void listCreate(cell **head);
int emptyList(cell *head);
void toInsert(cell **head, cell *z);
cell *toRemove(cell **head, int info);
cell *search(cell *head, int info);
void printList(cell *head);

int main(){
    // Lista l1 e ponteiro auxiliar z
    cell *l1, *z;

    int info;
    int i, opc;
    listCreate(&l1);
    do{
        printf("1-Inserir\n2-Remover\n3-Consultar\n4-Listar\n5-Terminar \n\nOpcao:[ ]\b\b");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            z = (cell *) malloc(sizeof(cell));
            if(z == NULL){
                printf("Erro de alocacao\n");
            }
            printf("Valor a inserir: ");
            scanf("%d", &info);
            z->key = info;
            toInsert(&l1, z);
            printf("Valor inserido\n\n");
            break;
        case 2:
            printf("Valor a remover: ");
            scanf("%d", &info);
            z = toRemove(&l1, info);
            if(z == NULL){
                printf("Valor nao encontrado\n\n");
            } else {
                printf("Valor removido: %d\n\n", z->key);
                free(z);
            }
            break;
        case 3:
            printf("Valor a consultar: ");
            scanf("%d", &info);
            z = search(l1, info);
            if(z == NULL){
                printf("Valor nao encontrado\n\n");
            } else {
                printf("Valor encontrado: %d\n\n", z->key);
            }
            break;
        case 4:
            printList(l1);
            break;  
        }
    } while (opc != 5);
    printf("Programa encerrado\n\n");
    return 0;
}
