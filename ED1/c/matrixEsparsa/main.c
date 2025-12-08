#include <stdio.h>
#include <stdlib.h>

/* ---------- Estruturas ---------- */

typedef struct Node {
    int row;
    int col;
    double value;
    struct Node *next;
} Node;

typedef struct {
    int rows;
    int cols;
    Node *head;
} SparseMatrix;

/* ---------- Funções auxiliares ---------- */

static Node *create_node(int row, int col, double value) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Erro de alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }
    n->row = row;
    n->col = col;
    n->value = value;
    n->next = NULL;
    return n;
}

/* ---------- Interface da matriz esparsa ---------- */

SparseMatrix *sm_create(int rows, int cols) {
    SparseMatrix *m = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    if (!m) {
        fprintf(stderr, "Erro de alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }
    m->rows = rows;
    m->cols = cols;
    m->head = NULL;
    return m;
}

void sm_destroy(SparseMatrix *m) {
    if (!m) return;
    Node *curr = m->head;
    while (curr) {
        Node *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(m);
}

void sm_set(SparseMatrix *m, int row, int col, double value) {
    if (!m) return;
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
        fprintf(stderr, "Indice fora dos limites: (%d, %d)\n", row, col);
        return;
    }

    Node *prev = NULL;
    Node *curr = m->head;

    while (curr && (curr->row < row || (curr->row == row && curr->col < col))) {
        prev = curr;
        curr = curr->next;
    }

    if (curr && curr->row == row && curr->col == col) {
        if (value == 0.0) {
            if (prev) prev->next = curr->next;
            else m->head = curr->next;
            free(curr);
        } else {
            curr->value = value;
        }
        return;
    }

    if (value == 0.0) return;

    Node *new_node = create_node(row, col, value);
    if (!prev) {
        new_node->next = m->head;
        m->head = new_node;
    } else {
        new_node->next = prev->next;
        prev->next = new_node;
    }
}

double sm_get(const SparseMatrix *m, int row, int col) {
    if (!m) return 0.0;
    if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
        fprintf(stderr, "Indice fora dos limites em sm_get: (%d, %d)\n", row, col);
        return 0.0;
    }

    Node *curr = m->head;
    while (curr && (curr->row < row || (curr->row == row && curr->col < col))) {
        curr = curr->next;
    }

    if (curr && curr->row == row && curr->col == col) {
        return curr->value;
    }
    return 0.0;
}

void sm_print_sparse(const SparseMatrix *m) {
    if (!m) return;
    printf("Elementos nao nulos (linha, coluna, valor):\n");
    Node *curr = m->head;
    if (!curr) {
        printf("(nenhum elemento nao nulo)\n");
    }
    while (curr) {
        printf("(%d, %d) = %.2f\n", curr->row, curr->col, curr->value);
        curr = curr->next;
    }
}

/* ---------- Funções de menu / entrada de dados ---------- */

void menu() {
    printf("\n==== MENU MATRIZ ESPARSA ====\n");
    printf("1 - Inserir/alterar valor\n");
    printf("2 - Imprimir matriz (esparsa)\n");
    printf("3 - Buscar valor em (linha, coluna)\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

void inserir_valor(SparseMatrix *m) {
    int lin, col;
    double val;

    printf("Informe a linha (0 a %d): ", m->rows - 1);
    scanf("%d", &lin);
    printf("Informe a coluna (0 a %d): ", m->cols - 1);
    scanf("%d", &col);
    printf("Informe o valor (0 para remover): ");
    scanf("%lf", &val);

    sm_set(m, lin, col, val);
}

void buscar_valor(SparseMatrix *m) {
    int lin, col;
    printf("Informe a linha (0 a %d): ", m->rows - 1);
    scanf("%d", &lin);
    printf("Informe a coluna (0 a %d): ", m->cols - 1);
    scanf("%d", &col);

    double valor = sm_get(m, lin, col);
    printf("Valor em (%d, %d) = %.2f\n", lin, col, valor);
}

/* ---------- main ---------- */

int main(void) {
    int rows, cols;
    printf("Informe o numero de linhas da matriz: ");
    scanf("%d", &rows);
    printf("Informe o numero de colunas da matriz: ");
    scanf("%d", &cols);

    SparseMatrix *A = sm_create(rows, cols);

    int opcao;
    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Encerrando.\n");
            break;
        }

        switch (opcao) {
            case 1:
                inserir_valor(A);
                break;
            case 2:
                printf("Matriz (esparsa):\n");
                sm_print_sparse(A);
                break;
            case 3:
                buscar_valor(A);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    sm_destroy(A);
    return 0;
}