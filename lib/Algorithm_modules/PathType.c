#include "PathType.h"

int path_type(List** ISP_graph,int max_node_value,int destination,int* PD_path,int source_node){
    Stack* prio_c=NULL;
    Stack* prio_r=NULL;
    int path_type;

    int* index=(int*)malloc(max_node_value*sizeof(int));
    if(index==NULL){
        exit(EXIT_FAILURE);
    }

    // Inicializar os vetores
    for (int i = 0; i < max_node_value; i++) {
        index[i]=-1;    //inicializar todos os nos como por descobrir
    }

    path_type=BGP_dijkstra(ISP_graph,source_node,destination,index,PD_path,prio_c,prio_r); //aplicar dijkstra de um no para todos
    //libertacao da memoria alocada
    free(index);

    return path_type;
}

int BGP_dijkstra(List** ISP_graph,int source_node,int destination,int* index,int* PD_path,Stack* prio_c,Stack* prio_r){
    int node,value;
    int char_to_int;
    List* aux;
    Stack* element;
    int vertice;
    int path_type=3;

    int comparison_matrix[3][3];    //matriz de caminhos


    //criacao de matriz de ajuda a decisao do tipo de caminho(1-customer,2-peer,3-provider,4-invalid)
    comparison_matrix[0][0]=1;
    comparison_matrix[0][1]=3; //4,mas como apenas testamos para uma rede comercialmente conexa
    comparison_matrix[0][2]=3; //4,mas como apenas testamos para uma rede comercialmente conexa
    comparison_matrix[1][0]=2;
    comparison_matrix[1][1]=3; //4,mas como apenas testamos para uma rede comercialmente conexa
    comparison_matrix[1][2]=3; //4,mas como apenas testamos para uma rede comercialmente conexa
    comparison_matrix[2][0]=3;
    comparison_matrix[2][1]=3;
    comparison_matrix[2][2]=3;

    element=create_element(destination-1);
    prio_c=push_LIFO(prio_c,element);
    while(prio_c!=NULL || prio_r!=NULL){
        if(prio_c!=NULL){
            node=remove_LIFO(&prio_c);
            value=1;
        }else{
            node=remove_LIFO(&prio_r);
            if(index[node]==-2 && prio_r!=NULL){
                continue;
            }
            value=2;
        }
        if(node==source_node-1){
            path_type=value;
        }
        index[node]=-2; //marca o no como visitado
        aux=ISP_graph[node];    //prepara para analisar os nos adjacentes
        PD_path[value]++;
        while(aux!=NULL){
            vertice=aux->vertices-1;
            char_to_int=-(aux->edges-'4');  //converte o tipo de ligacao de char para int e aplica a prioridade
            if(index[vertice]==-1 && comparison_matrix[char_to_int-1][value-1]!=3){ //se o no nao foi descoberto e o tipo de caminho nao e provider
                element=create_element(vertice);
                if(char_to_int==1){
                    prio_c=push_LIFO(prio_c,element);
                    index[vertice]=1;
                }else{
                    prio_r=push_LIFO(prio_r,element);
                    index[vertice]=2;
                }
            }else if(index[vertice]==2 && comparison_matrix[char_to_int-1][value-1]==1){   //se o no nao foi descoberto (e visitado) mas ainda esta na queue e o tipo de caminho nao e provider
                element=create_element(vertice);
                prio_c=push_LIFO(prio_c,element);
                index[vertice]=1;
            }
            aux=aux->next;
        }
    }
    return path_type;
}