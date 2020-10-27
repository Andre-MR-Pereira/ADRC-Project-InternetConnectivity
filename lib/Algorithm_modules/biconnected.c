#include "biconnected.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//funcao para ver se a rede e link_biconnected
void link_biconnected(List** ISP_graph,int max_node_value){
    //inicializacao de variaveis
    int start_node,result;

    //procura o primeiro no onde haja uma lista para ser analizada
    for(int i=0;i<max_node_value;i++){
        if(ISP_graph[i]!=NULL){
            start_node=i+1; //guarda o no com uma lista
            break;
        }
    }

    int* bridge = (int*)calloc(2,sizeof(int));  //alocacao para memoria de uma potencial ponte
    if(bridge==NULL){
        EXIT_FAILURE;
    }
    int* discovery_time = (int*)malloc(max_node_value*sizeof(int)); //alocacao de memoria do vetor que ira guardas os tempos de descoberta de cada no
    if(discovery_time==NULL){
        EXIT_FAILURE;
    }
    bool* discovered = (bool*)malloc(max_node_value*sizeof(bool));  //alocacao de memoria do vetor que indica se um no ja foi descoberto pela DFS
    if(discovered==NULL){
        EXIT_FAILURE;
    }
    int* parent = (int*)malloc(max_node_value*sizeof(int)); //alocacao de memoria do vetor que ira indicar o parente de cada no descoberto na DFS
    if(parent==NULL){
        EXIT_FAILURE;
    }
    int* ancient = (int*)malloc(max_node_value*sizeof(int));    //alocacao de memoria do vetor que ira guardar o antecesor mais antigo que a subarvore em que o no se encontra se consegue ligar
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
    discovered[start_node-1] = true;    //indicar como descoberto o no inicial
    parent[start_node-1] = start_node;  //colocar como parente do no inicial ele mesmo

    result=articulation_bridge(ISP_graph,discovery_time,discovered,parent,ancient,start_node,bridge);   //procura de uma ponte na rede
    if(result==-1){ //caso exista uma ponte
        printf("\n Answer: The input internet is not link-biconnected,and one of the bridges is the edge between node %d and %d.\n",bridge[0],bridge[1]);
    }else{  //caso nao exista uma ponte
        printf("\n Answer: The input internet is link-biconnected!\n");
    }
    //libertacao da memoria alocada
    free(bridge);
    free(discovery_time);
    free(discovered);
    free(parent);
    free(ancient);

}

//algoritmo para descobrir pontes
int articulation_bridge(List** ISP_graph,int* discovery_time,bool* discovered,int* parent,int* ancient,int vertice,int* bridge){
    //inicializacao de variaveis
    static int discovery_count=1;   //variavel que conta o tempo de descoberta de cada vertice entre cada recursividade do algoritmo
    int son_backedge;

    List* arestas = NULL;   //inicializacao do vetor de arestas a serem analizadas

    discovered[vertice-1]=true; //colocar o novo vertice como descoberto
    discovery_time[vertice-1] = discovery_count;    //guardar o tempo de descoberta do vertice
    ancient[vertice-1] = discovery_count;   //comecar por dizer que a backedge mais antiga do vertice comeca por ser ele mesmo
    discovery_count++;  //incrementar tempo de descoberta

    arestas = ISP_graph[vertice-1]; //guardar as arestas deste no para serem analisadas posteriormente

    while(arestas!=NULL){   //enquanto ainda nao foram analisadas todas as arestas
        if(discovered[arestas->vertices-1]==false){ //caso a aresta ligue a um vertice que ainda nao foi descoberto
	        parent[arestas->vertices-1]=vertice;    //guardamos o vertice em que estamos como parente do proximo vertice a ser analisado
            son_backedge=articulation_bridge(ISP_graph,discovery_time,discovered,parent,ancient,arestas->vertices,bridge);  //calculamos a backedge da subarvore ligada ao vertice em analise e que tera raiz no novo vertice descoberto
            if(son_backedge==-1){   //caso ja tenha sido descoberta uma ponte,sair da recursividade do algoritmo
                return -1;
            } else if(son_backedge<ancient[vertice-1]){ //caso a backedge da subarvore seja mais antiga que a do vertice em analise
                ancient[vertice-1]=son_backedge;    //guardar valor backedge
            }
        }else{
            if(ancient[vertice-1]>discovery_time[arestas->vertices-1]&&parent[vertice-1]!=arestas->vertices){   //caso exista uma backedge mais antiga que se ligue ao vertice e nao seja da aresta de onde o vertice foi descoberto
                ancient[vertice-1]=discovery_time[arestas->vertices-1]; //guardar a backedge mais antiga para este vertice
            }
        }

        arestas=arestas->next;  //iterar para a proxima aresta

    }

    arestas = ISP_graph[vertice-1]; //voltar a analisar as arestas deste vertice

    while(arestas!=NULL){
        if(ancient[arestas->vertices-1]>discovery_time[vertice-1]){ //se o tempo de descoberta do vertice em analise  for menor que a backedge de uma das suas subarvores,entao descobriu-se uma ponte e pode-se parar o algoritmo
            //guardar a ponte
            bridge[0]=arestas->vertices;
            bridge[1]=vertice;
            return -1;  //quebrar o algoritmo
        }
        arestas=arestas->next;  //iterar para a proxima aresta
    }

    return ancient[vertice-1];  //retornar a backedge do vertice
}
