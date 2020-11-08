#include "PathType.h"

char path_type(List** ISP_graph,int max_node_value,int source,int destination){
    int path_type;
    Heap* queue;
    char returning_path;

    bool* discovered = (bool*)malloc(max_node_value*sizeof(bool));  //alocacao de memoria do vetor que indica se um no ja foi descoberto pela Dikjstra
    if(discovered==NULL){
        exit(EXIT_FAILURE);
    }
    int* parent = (int*)malloc(max_node_value*sizeof(int)); //alocacao de memoria do vetor que ira indicar o no pelo qual se chegou ao novo no
    if(parent==NULL){
        exit(EXIT_FAILURE);
    }
    int* tipo_caminho = (int*)malloc(max_node_value*sizeof(int)); //alocacao de memoria do vetor que ira indicar o tipo de caminho com que se chegou ao no
    if(tipo_caminho==NULL){
        exit(EXIT_FAILURE);
    }
    int* index=(int*)malloc(max_node_value*sizeof(int));
    if(index==NULL){
        exit(EXIT_FAILURE);
    }

    queue=createHeap(max_node_value);

    // Inicializar os vetores
    for (int i = 0; i < max_node_value; i++) {
        parent[i] = -1;
        discovered[i] = false;
        index[i]=-1;
        tipo_caminho[i]=4;
    }

    parent[destination-1] = destination-1;  //colocar como parente do no inicial ele mesmo
    tipo_caminho[destination-1] = 1;  //colocar como parente do no inicial ele mesmo

    path_type=BGP_dijkstra(ISP_graph,source,destination,discovered,parent,queue,index,tipo_caminho);

    switch(path_type){
        case 1:
            returning_path='C';
            break;
        case 2:
            returning_path='R';
            break;
        case 3:
            returning_path='P';
            break;
        default:
            returning_path='I';
            break;
    }

    //libertacao da memoria alocada
    free(discovered);
    free(parent);
    free(index);
    free(tipo_caminho);
    queue=eraseHeap(queue);

    return returning_path;
}

int BGP_dijkstra(List** ISP_graph,int source,int destination,bool* discovered,int* parent,Heap* queue,int* index,int* tipo_caminho){
    int worst_path_value=1;
    int heap_max=0,node,value;
    int char_to_int;
    Heap* remove;
    List* aux;

    int comparison_matrix[3][3];

    remove=createUnit();

    //criacao de matriz de ajuda a decisao do tipo de caminho(1-provider,2-peer,3-customer,4-invalid)
    comparison_matrix[0][0]=1;
    comparison_matrix[0][1]=1;
    comparison_matrix[0][2]=1;
    comparison_matrix[1][0]=4;
    comparison_matrix[1][1]=4;
    comparison_matrix[1][2]=2;
    comparison_matrix[2][0]=4;
    comparison_matrix[2][1]=4;
    comparison_matrix[2][2]=3;

    heap_max=insertHeap(queue,heap_max,index,destination-1,1);

    while(heap_max>0){
        node=get_hnode(queue,0);
        value=get_hvalue(queue,0);
        tipo_caminho[node]=value;
        if(value>worst_path_value){
            worst_path_value=value;
        }

        if(node+1==source){
            if(comparison_matrix[tipo_caminho[parent[node]]-1][value-1]>worst_path_value){
                worst_path_value=comparison_matrix[tipo_caminho[parent[node]]-1][value-1];
            }
            remove=eraseHeap(remove);
            return worst_path_value;
        }
        heap_max=removeHeap(queue,remove,heap_max,index);
        index[node]=-2;
        discovered[node]=true;
        aux=ISP_graph[node];
        while(aux!=NULL){
            if(discovered[aux->vertices-1]==false && index[aux->vertices-1]==-1 && comparison_matrix[value-1][-(aux->edges-'4')-1]!=4){
                char_to_int=-(aux->edges-'4');
                heap_max=insertHeap(queue,heap_max,index,aux->vertices-1,char_to_int);
                parent[aux->vertices-1]=node;
            }else if(discovered[aux->vertices-1]==false && index[aux->vertices-1]!=-1 && comparison_matrix[value-1][-(aux->edges-'4')-1]!=4){
                char_to_int=-(aux->edges-'4');
                if(char_to_int<get_hvalue(queue,index[aux->vertices-1])){
                    setValue(queue,index[aux->vertices-1],char_to_int,index);
                    parent[aux->vertices-1]=node;
                }
            }
            aux=aux->next;
        }
    }
    remove=eraseHeap(remove);
    return -1;
}