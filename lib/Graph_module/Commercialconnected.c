//
// Created by joped on 14/10/2020.
//

#include "Commercialconnected.h"
bool provider_network(List** graph,int* top_p, int size,int* list_top,int count_p){
    List* arestas = NULL;
    int count_aux;
    for(int i = 0; i<count_p;i++){
        count_aux = 0;
        arestas = graph[list_top[i]-1];
        while (arestas!=NULL){
            if(top_p[arestas->vertices-1]) count_aux++;
            arestas=arestas->next;
        }
        if(count_aux!=count_p-1) return false;
    }
    return true;
}

bool connected(List** graph,int* top_p, int size,int* list_top,int count_p,int true_size){
    if (!provider_network(graph,top_p,size,list_top,count_p)) return false;
    int start_node = list_top[0];
    bool *discovered = (bool*)malloc(size*sizeof(bool));

    // Inicializar os vetores
    for (int i = 0; i < size; i++) {
        discovered[i] = false;
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
            if(discovered[arestas->vertices-1] == false && ((arestas->edges=='1')||(top_p[arestas->vertices-1] && arestas->edges=='2'))){
                    count++;
                    discovered[arestas->vertices - 1] = true;
                    FIFO = push_FIFO(FIFO, create_element(arestas->vertices));
            }
            arestas = arestas->next;
        }
        if(count == true_size){
            erase_FIFO(FIFO);
            free(discovered);
            return true;
        }

        remove_FIFO(FIFO);
    }

    erase_FIFO(FIFO);
    free(discovered);
    return false;
}
