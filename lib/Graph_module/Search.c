#include "Search.h"

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

    Stack **FIFO = create_FIFO(create_element(start_node));
    Stack *auxS = NULL;
    List *arestas = NULL;
    int count = 1;
    discovered[start_node-1] = true;
    while (FIFO[0] != NULL){
        auxS = FIFO[0];
        arestas = graph[get_node(auxS)-1];
        while (arestas != NULL) {
            if(discovered[arestas->vertices-1] == false){
                count++;
                discovered[arestas->vertices-1] = true;
                parent[arestas->vertices-1] = get_node(auxS);
                FIFO = push_FIFO(FIFO, create_element(arestas->vertices));
            }
            arestas = arestas->next;
        }
        if(count == size) break; //duvidoso
        remove_FIFO(FIFO);
    }

    erase_FIFO(FIFO);
    free(discovered);

    return parent;
}

int* DFS(List** graph, int size, int start_node){
    // Vetores auxiliares
    bool *discovered = (bool*)malloc(size*sizeof(bool));
    int *parent = (int*)malloc(size*sizeof(int));

    // Inicializar os vetores
    for (int i = 0; i < size; i++) {
        discovered[i] = false;
        parent[i] = -1;
    }

    Stack *LIFO = create_element(start_node);
    Stack *auxS = NULL;
    List *arestas = NULL;
    int count = 1;
    discovered[start_node-1] = true;
    while (LIFO != NULL){
        auxS = LIFO;
        arestas = graph[get_node(auxS)-1];
        while (arestas != NULL) {
            if(discovered[arestas->vertices-1] == false){
                count++;
                discovered[arestas->vertices-1] = true;
                parent[arestas->vertices-1] = get_node(auxS);
                LIFO = push_LIFO(LIFO, create_element(arestas->vertices));
            }
            arestas = arestas->next;
        }
        if(count == size) break; //duvidoso
        remove_LIFO(&LIFO);
    }

    erase_LIFO(LIFO);
    free(discovered);

    return parent;
}