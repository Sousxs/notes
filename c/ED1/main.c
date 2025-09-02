#include <stdio.h>
#include "list.h"

int main() {
    List lista;
    init(&lista);
    insert(&lista, 10);
    insert(&lista, 20);
    insert(&lista, 30);
    remove_node(&lista, 20);
    search(&lista, 10);
    free_list(&lista);
    return 0;
}