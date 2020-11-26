#include "PathType.h"

int path_type(List** ISP_graph,int max_node_value,int destination,int* PD_path,int source_node){
    Stack* prio_c=NULL;
    Stack* prio_r=NULL;
    int path_type;

    int* index=(int*)malloc(max_node_value*sizeof(int));    //vetor que guarda o estado de cada no | -2:retirado; -1:por descobrir; 1,2 ou 3: tipo de caminho associado para chegar a esse no
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

    //adiciona o no inicial para ser analisado
    element=create_element(destination-1);
    prio_c=push_LIFO(prio_c,element);
    while(prio_c!=NULL || prio_r!=NULL){    //enquanto as stacks associadas a possiveis nos com caminho do tipo C ou R ainda estao com elementos
        if(prio_c!=NULL){   //se a stack tiver potenciais nos com caminho de tipo C retirar esses primeiro
            node=remove_LIFO(&prio_c);  //guardar o no retirado
            value=1;    //guardar o caminho ate esse no como sendo do tipo C
        }else{  //senao remover da stack com nos potencialmente do tipo R
            node=remove_LIFO(&prio_r);  //retirar o no
            if(index[node]==-2 && prio_r!=NULL){    //caso o no ja tenha sido retirado ou a lista ainda tenha mais nos por analisar
                continue;   //voltar ao inicio do ciclo while
            }
            value=2;    //guardar o caminho ate esse no como sendo do tipo R
        }
        if(node==source_node-1){    //caso seja o no de source
            path_type=value;    //guardar o valor para apresentar
        }
        index[node]=-2; //marca o no como visitado
        aux=ISP_graph[node];    //prepara para analisar os nos adjacentes
        PD_path[value]++;   //incrementa a contagem desse tipo de caminho
        while(aux!=NULL){   //enquanto existirem nos por visitar
            vertice=aux->vertices-1;    //guarda o no a analisar
            char_to_int=-(aux->edges-'4');  //converte o tipo de ligacao de char para int e aplica a prioridade
            if(index[vertice]==-1 && comparison_matrix[char_to_int-1][value-1]!=3){ //se o no nao foi descoberto e o tipo de caminho nao e provider
                element=create_element(vertice);    //guardar o tipo de caminho
                if(char_to_int==1){ //caso seja do tipo C
                    prio_c=push_LIFO(prio_c,element);   //colocar na stack
                    index[vertice]=1;   //indicar o tipo de caminho possivelmente associado
                }else{ //caso seja do tipo R
                    prio_r=push_LIFO(prio_r,element);   //colocar na stack
                    index[vertice]=2;   //indicar o tipo de caminho possivelmente associado
                }
            }else if(index[vertice]==2 && comparison_matrix[char_to_int-1][value-1]==1){   //se o no se encontra na stack de cainhos tipo R e foi descoberto um caminho para si do tipo C
                element=create_element(vertice);    //guardar o tipo de caminho
                prio_c=push_LIFO(prio_c,element);   //colocar na stack
                index[vertice]=1;   //indicar o tipo de caminho possivelmente associado
            }
            aux=aux->next;  //iterar sobre os nos a visitar
        }
    }
    return path_type;   //retorna o tipo de caminho do no pretendido
}