#include "biconnected.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void link_biconnected(List** ISP_graph,int max_node_value){
    int start_node,result;

    for(int i=0;i<max_node_value;i++){
        if(ISP_graph[i]!=NULL){
            start_node=i+1;
            break;
        }
    }

    int* bridge = (int*)calloc(2,sizeof(int));
    if(bridge==NULL){
        EXIT_FAILURE;
    }
    int* discovery_time = (int*)malloc(max_node_value*sizeof(int));
    if(discovery_time==NULL){
        EXIT_FAILURE;
    }
    bool* discovered = (bool*)malloc(max_node_value*sizeof(bool));
    if(discovered==NULL){
        EXIT_FAILURE;
    }
    int* parent = (int*)malloc(max_node_value*sizeof(int));
    if(parent==NULL){
        EXIT_FAILURE;
    }
    int* ancient = (int*)malloc(max_node_value*sizeof(int));
    if(ancient==NULL){
        EXIT_FAILURE;
    }

    // Inicializar os vetores
    for (int i = 0; i < max_node_value; i++) {
        discovery_time[i] = -1;
        parent[i] = -1;
        ancient[i] = -1;
        discovered[i] = false;
    }
    discovered[start_node-1] = true;
    parent[start_node-1] = start_node;

    result=articulation_bridge(ISP_graph,discovery_time,discovered,parent,ancient,start_node,bridge);
    if(result==-1){
        printf("The graph is not link-biconnected,and one of the bridges is the edge between node %d and %d.\n",bridge[0],bridge[1]);
    }else{
        printf("The graph is link-biconnected!\n");
    }
    free(bridge);
    free(discovery_time);
    free(discovered);
    free(parent);
    free(ancient);

}

int articulation_bridge(List** ISP_graph,int* discovery_time,bool* discovered,int* parent,int* ancient,int vertice,int* bridge){
    static int discovery_count=1;
    int son_backedge;

    List* arestas = NULL;

    discovered[vertice-1]=true;
    discovery_time[vertice-1] = discovery_count;
    ancient[vertice-1] = discovery_count;
    discovery_count++;

    arestas = ISP_graph[vertice-1];

    while(arestas!=NULL){
        if(discovered[arestas->vertices-1]==false){
	        parent[arestas->vertices-1]=vertice;
            son_backedge=articulation_bridge(ISP_graph,discovery_time,discovered,parent,ancient,arestas->vertices,bridge);
            if(son_backedge==-1){
                return -1;
            } else if(son_backedge<ancient[vertice-1]){
                ancient[vertice-1]=son_backedge;
            }
        }else{
            if(ancient[vertice-1]>discovery_time[arestas->vertices-1]&&parent[vertice-1]!=arestas->vertices){
                ancient[vertice-1]=discovery_time[arestas->vertices-1];
            }
        }

        arestas=arestas->next;

    }

    arestas = ISP_graph[vertice-1];

    while(arestas!=NULL){
        if(ancient[arestas->vertices-1]>discovery_time[vertice-1]){
            bridge[0]=arestas->vertices;
            bridge[1]=vertice;
            return -1;
        }
        arestas=arestas->next;
    }

    return ancient[vertice-1];
}
