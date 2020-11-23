#include "PathType.h"

void path_type(List** ISP_graph,int max_node_value,int destination,int** all_path_types,int* PD_path){
    Heap* queue;

    int* index=(int*)malloc(max_node_value*sizeof(int));
    if(index==NULL){
        exit(EXIT_FAILURE);
    }
    int* path=(int*)calloc(max_node_value,sizeof(int));
    if(path==NULL){
        exit(EXIT_FAILURE);
    }
    queue=createHeap(max_node_value);   //criacao da queue para escolha do caminho na dijktra

    // Inicializar os vetores
    for (int i = 0; i < max_node_value; i++) {
        index[i]=-1;    //inicializar todos os nos como por descobrir
        if(ISP_graph[i]!=NULL){ //caso o no exista
            //all_path_types[destination-1][i]=3; //inicializar todos os caminhos como tipo provider
            path[i]=3;
        }  //caso nao exista ja esta marcado como invalido
    }
    path[destination-1]=1;
    //all_path_types[destination-1][destination-1]=1; //inicializar todos os caminhos como tipo provider
    //printf("Estamos no no %d\n",destination);
    BGP_dijkstra(ISP_graph,destination,queue,index,all_path_types,PD_path,path); //aplicar dijkstra de um no para todos

    //libertacao da memoria alocada
    free(index);
    free(path);
    queue=eraseHeap(queue);
}

void BGP_dijkstra(List** ISP_graph,int destination,Heap* queue,int* index,int** all_path_types,int* PD_path,int* path){
    int heap_max=0,node,value;
    int char_to_int;
    Heap* remove;
    List* aux;

    int comparison_matrix[3][3];    //matriz de caminhos

    remove=createUnit();    //no para ajudar na remoçao de pontos da queue

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

    heap_max=insertHeap(queue,heap_max,index,destination-1,1);  //insere o no inicial a ser analisado
    while(heap_max>0){
        node=get_hnode(queue,0);    //no a ser analisado
        value=get_hvalue(queue,0);  //tipo de caminho para chegar ao no
        heap_max=removeHeap(queue,remove,heap_max,index);   //remove o no a ser analisado da queue
        index[node]=-2; //marca o no como visitado
        aux=ISP_graph[node];    //prepara para analisar os nos adjacentes
        switch (path[node]) {
            case 1:
                PD_path[1]++;
                break;
            case 2:
                PD_path[2]++;
                break;
            default:
                printf("Isto nao devia acontecer\n");
                break;
        }
        while(aux!=NULL){
            char_to_int=-(aux->edges-'4');  //converte o tipo de ligacao de char para int e aplica a prioridade
            if(index[aux->vertices-1]==-1 && comparison_matrix[char_to_int-1][value-1]!=3){ //se o no nao foi descoberto e o tipo de caminho nao e provider
                heap_max=insertHeap(queue,heap_max,index,aux->vertices-1,char_to_int);
                //all_path_types[destination-1][aux->vertices-1]=comparison_matrix[char_to_int-1][value-1];  //guardar o pior caminho para chegar a esse no
                path[aux->vertices-1]=comparison_matrix[char_to_int-1][value-1];
            }else if(index[aux->vertices-1]!=-1 && index[aux->vertices-1]!=-2 && comparison_matrix[char_to_int-1][value-1]!=3){   //se o no nao foi descoberto (e visitado) mas ainda esta na queue e o tipo de caminho nao e provider
                if(char_to_int<get_hvalue(queue,index[aux->vertices-1])){
                    setValue(queue,index[aux->vertices-1],char_to_int,index);
                    //all_path_types[destination-1][aux->vertices-1]=comparison_matrix[char_to_int-1][value-1];  //guardar o pior caminho para chegar a esse no
                    path[aux->vertices-1]=comparison_matrix[char_to_int-1][value-1];
                }
            }
            aux=aux->next;
        }
    }
    remove=eraseHeap(remove);
}