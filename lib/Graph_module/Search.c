#include "Search.h"
#include "graph.h"
#include "Stacks.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int* BFS(List** graph, int size, int start_node){
    // Vetores auxiliares
    bool *discovered = (bool*)malloc(size*sizeof(bool));
    int *parent = (int*)malloc(size*sizeof(int));

    // Inicializar os vetores
    for (int i = 0; i < size; i++) {
        discovered[i] = false;
        parent[i] = -1;
    }

    Stack *FIFO = create_element(start_node);
    int i = 0;
    discovered[start_node] = 0;
    while (FIFO != NULL){
        List *aux = graph[FIFO->node];
        while (List* aux != NULL) {

        }
    }

}