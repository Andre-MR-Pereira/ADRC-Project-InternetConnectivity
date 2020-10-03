#include "graph.h"

#include <stdlib.h>
#include <stdio.h>

List** create_graph(int max_node_value){
    List ** ISP_graph;

    ISP_graph=(List **)malloc((max_node_value-1)*sizeof(struct List*));
    if(ISP_graph==NULL){
        return EXIT_FAILURE;
    }
    for(int i=0;i<max_node_value-1;i++){
        ISP_graph[i]=initNode();
    }
    return ISP_graph;
}

List** fill_ISP(List** ISP_graph,int tail, int head,int mode){
    List* new_node;
    char node_mode;

    new_node=(List*)malloc(sizeof(struct Node));
    if(new_node==NULL){
        return EXIT_FAILURE;
    }
    new_node->vertices=head;
    switch (mode) {
        case 1:
            node_mode='A';
            break;
        case 2:
            node_mode='B';
            break;
        case 3:
            node_mode='C';
            break;
        default:
            return EXIT_FAILURE;
    }
    new_node->edges=node_mode;
    ISP_graph[tail-1]=insertHeadList(ISP_graph[tail-1],new_node);
    return ISP_graph;
}

List* initNode(void){
    return NULL;
}

List* insertHeadList(List* next, List* item) {
    List *new;

    /* Initialize new node */
    new = item;
    new->next = next;

    return new;
}

void print_graph(List** ISP_graph,int max_node_value){
    List* node;

    for(int i=0;i<max_node_value-1;i++){
        node=ISP_graph[i];
        while(node!=NULL){
            printf("Lista de %d: %d||%c\n",i+1,node->vertices,node->edges);
            node = (node->next==NULL) ? NULL : node->next;
        }
    }

    return;
}