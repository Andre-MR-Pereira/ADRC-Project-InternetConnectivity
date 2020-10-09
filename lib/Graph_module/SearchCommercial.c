//
// Created by joped on 09/10/2020.
//
#include "SearchCommercial.h"

#include <stdlib.h>
#include <stdio.h>

int* BFS_C(List** graph, int size, int start_node){
    // Vetores auxiliares
    char *discovered = (char*)malloc(size*sizeof(char));
    int *parent = NULL;
    int edge, vertice,node,count=1;
    char edgec;
    // Inicializar os vetores
    parent = (int*)malloc(size*sizeof(int));
    for (int i = 0; i < size; i++) {
        discovered[i] = '0';
        parent[i] = -1;
    }

    Stack *auxS = NULL;
    List *arestas = NULL;


    discovered[start_node-1] = '3';

    Stack*** FIFO=(Stack ***) malloc(sizeof(Stack**)*3);
    for (int i = 0; i<3;i++){
        FIFO[i] = create_FIFO(create_element(start_node));
    }


    for (int i = 2; i>=0;i--){
        while (FIFO[i][0] != NULL){

            auxS = FIFO[i][0];
            node = get_node(auxS)-1;
            arestas = graph[node];

            if (discovered[node]>'1'+i){
                remove_FIFO(FIFO[i]);
                continue;
            }
            while (arestas != NULL) {
                vertice = arestas->vertices - 1;

                edgec = arestas->edges;
                if(discovered[vertice]>=edgec||((start_node-1)==node && edgec=='2')){
                    arestas = arestas->next;
                    continue;

                }
                edge = edgec - '0';

                if (edge<i+1 || (edge==i+1 && i!=1)){
                    count++;
                    discovered[vertice] = edgec;
                    FIFO[edge-1] = push_FIFO(FIFO[edge-1], create_element(arestas->vertices));
                    if(edge!=2) {
                        parent[vertice] = get_node(auxS);
                    }
                }


                arestas = arestas->next;
                print_FIFO(FIFO[2]);
                print_FIFO(FIFO[1]);
                print_FIFO(FIFO[0]);


                printf("\n");
            }
            if(count == size) break; //duvidoso

            remove_FIFO(FIFO[i]);
        }
        FIFO[i]=erase_FIFO(FIFO[i]);
    }
    free(FIFO);
    free(discovered);
    return parent;
}

int* DFS_C(List** graph, int size, int start_node){
    // Vetores auxiliares
    char *discovered = (char*)malloc(size*sizeof(char));
    int *parent = NULL;
    int edge, vertice,node,count=1;
    char edgec;
    // Inicializar os vetores
    parent = (int*)malloc(size*sizeof(int));
    for (int i = 0; i < size; i++) {
        discovered[i] = '0';
        parent[i] = -1;
    }

    Stack *auxS = NULL;
    List *arestas = NULL;


    discovered[start_node-1] = '3';

    Stack** LIFO=(Stack **) malloc(sizeof(Stack*)*3);
    for (int i = 0; i<3;i++){
        LIFO[i] = create_element(start_node);
    }


    for (int i = 2; i>=0;i--){
        while (LIFO[i] != NULL){

            auxS = pull_LIFO(&LIFO[i]);
            node = get_node(auxS)-1;

            arestas = graph[node];

            if (discovered[node]>'1'+i){
                remove_LIFO(&LIFO[i]);
                continue;
            }

            while (arestas != NULL) {
                vertice = arestas->vertices - 1;

                edgec = arestas->edges;
                if(discovered[vertice]>=edgec||((start_node-1)==node && edgec=='2')){
                    arestas = arestas->next;
                    continue;

                }
                edge = edgec - '0';

                if (edge<i+1 || (edge==i+1 && i!=1)){
                    count++;
                    discovered[vertice] = edgec;
                    LIFO[edge-1] = push_LIFO(LIFO[edge-1], create_element(arestas->vertices));
                    if(edge!=2) {
                        parent[vertice] = get_node(auxS);
                    }
                }


                arestas = arestas->next;

                printf("\n");
            }
            if(count == size) break; //duvidoso
            free(auxS);


        }
        LIFO[i]=erase_LIFO(LIFO[i]);
    }
    free(LIFO);
    free(discovered);
    return parent;
}