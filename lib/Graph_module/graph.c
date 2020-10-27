#include "graph.h"

#include <stdlib.h>
#include <stdio.h>

List** create_graph(int max_node_value){    //recebe o maior no lido do ficheiro
    List ** ISP_graph;  //cria uma lista de adjacencia

    ISP_graph=(List **)malloc((max_node_value)*sizeof(struct List*));   //alocacao da memoria do vetor da lista de adjacencia
    if(ISP_graph==NULL){
        return (List **) EXIT_FAILURE;
    }
    for(int i=0;i<max_node_value;i++){  //inicializacao de cada entrada do vetor da lista de adjacencia
        ISP_graph[i]=initNode();
    }
    return ISP_graph;   //retorna a lista de adjacencia inicializada
}

List** fill_ISP(List** ISP_graph,int tail, int head,char mode){ //preenchimento da lista de adjacencia
    List* new_node; //no para ser inserido

    new_node=(List*)malloc(sizeof(struct Node));    //alocacao de memoria do no
    if(new_node==NULL){
        return (List **) EXIT_FAILURE;
    }
    new_node->vertices=head;    //guardar valor do vertice
    new_node->edges=mode;   //guardar valor da aresta
    ISP_graph[tail-1]=insertHeadList(ISP_graph[tail-1],new_node);   //inserir o no na cabeca da lista

    return ISP_graph;
}

List* initNode(void){   //inicializacao de um no
    return NULL;
}

void free_ISP(List** ISP_graph,int max_node_value){ //libertacao da memoria da lista de adjacencia
    free_node_list(ISP_graph,max_node_value);   //libertacao da memoria de cada lista
    free(ISP_graph);    //libertacao da memoria do vetor
}

List* insertHeadList(List* next, List* item) {  //insercao na cabeca de cada lista
    List *new;  //no auxiliar

    //inserir o no na cabeca
    new = item; //igualar o no auxiliar ao no a inserir
    new->next = next;   //o proximo valor do no a ser inserido sera a antiga cabeca da lista

    return new; //retornar a nova cabeca da lista
}

void free_node_list(List** ISP_graph,int max_node_value){   //libertar as lista
    //inicializacao dos vetores auxiliares
    List* next;
    List* aux;

    for(int i=0;i<max_node_value;i++){  //tratar de cada lista
        for(aux=ISP_graph[i];aux!=NULL;aux=next){   //enquanto nao forem libertos os nos todos da lista
            next=aux->next; //no auxiliar aponta para o proximo a ser liberto
            free(aux);  //libertar o no
        }
    }
}

void print_graph(List** ISP_graph,int max_node_value){  //funcao para ver a rede
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

void remove_node(List** ISP_graph,int ISP_vertice,int node_vertice){    //funcao para remover no especifico
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

List* find_node(List** ISP_graph,int ISP_vertice,int node_vertice){ //funcao para encontrar um no especifico
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