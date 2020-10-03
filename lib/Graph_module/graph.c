#include "graph.h"

#include <stdlib.h>
#include <stdio.h>

List** create_graph(int max_node_value){
    List ** ISP_graph;

    ISP_graph=(List **)malloc((max_node_value)*sizeof(struct List*));
    if(ISP_graph==NULL){
        return (List **) EXIT_FAILURE;
    }
    for(int i=0;i<max_node_value;i++){
        ISP_graph[i]=initNode();
    }
    return ISP_graph;
}

List** fill_ISP(List** ISP_graph,int tail, int head,char mode){
    List* new_node;

    new_node=(List*)malloc(sizeof(struct Node));
    if(new_node==NULL){
        return (List **) EXIT_FAILURE;
    }
    new_node->vertices=head;
    new_node->edges=mode;
    ISP_graph[tail-1]=insertHeadList(ISP_graph[tail-1],new_node);

    return ISP_graph;
}

List* initNode(void){
    return NULL;
}

void free_ISP(List** ISP_graph,int max_node_value){
    free_node_list(ISP_graph,max_node_value);
    free(ISP_graph);
}

List* insertHeadList(List* next, List* item) {
    List *new;

    /* Initialize new node */
    new = item;
    new->next = next;

    return new;
}

void free_node_list(List** ISP_graph,int max_node_value){
    List* next;
    List* aux;

    for(int i=0;i<max_node_value;i++){
        for(aux=ISP_graph[i];aux!=NULL;aux=next){
            next=aux->next;
            free(aux);
        }
    }
}

void print_graph(List** ISP_graph,int max_node_value){
    List* node;

    for(int i=0;i<max_node_value;i++){
        node=ISP_graph[i];
        if(node!=NULL){
            printf("Lista de %d:",i+1);
            while(node!=NULL){
                printf(" %d||%c ;",node->vertices,node->edges);
                node = (node->next==NULL) ? NULL : node->next;
            }
            printf("\n");
        }
    }
}

void remove_node(List** ISP_graph,int ISP_vertice,int node_vertice){
    List* aux=ISP_graph[ISP_vertice-1];
    if(aux==NULL){
        return;
    }
    List* next=aux->next;

    if(next!=NULL){
        for(aux=ISP_graph[ISP_vertice-1];aux!=NULL;aux=next){
            if(next->vertices==node_vertice){
                aux->next=next->next;
                free(next);
                break;
            }
            next=aux->next;
        }
    } else{
        if(aux->vertices==node_vertice){
            ISP_graph[ISP_vertice-1]=NULL;
            free(aux);
        }
    }


    aux=ISP_graph[node_vertice-1];
    if(aux==NULL){
        return;
    }
    next=aux->next;

    if(next!=NULL){
        for(aux=ISP_graph[node_vertice-1];aux!=NULL;aux=next){
            if(next->vertices==ISP_vertice){
                aux->next=next->next;
                free(next);
                break;
            }
            next=aux->next;
        }
    } else{
        if(aux->vertices==ISP_vertice){
            ISP_graph[node_vertice-1]=NULL;
            free(aux);
        }
    }
}

List* find_node(List** ISP_graph,int ISP_vertice,int node_vertice){
    List* aux=ISP_graph[ISP_vertice-1];
    if(aux==NULL){
        return NULL;
    }
    List* next=aux->next;

    if(next!=NULL){
        for(aux=ISP_graph[ISP_vertice-1];aux!=NULL;aux=next){
            if(next->vertices==node_vertice){
                return next;
            }
            next=aux->next;
        }
    } else{
        if(aux->vertices==node_vertice){
            return aux;
        }
    }
}