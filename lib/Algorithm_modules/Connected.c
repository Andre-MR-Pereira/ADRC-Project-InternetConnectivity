#include "Connected.h"
#include "SearchCommercial.h"

bool provider_network(List** graph,int* top_p, int size,int* list_top,int count_p,int* cycle){//verifca se os tier 1 estao conectados
    List* arestas = NULL;
    int aux,node;
    int count_aux;int* c=(int*)malloc(sizeof(int)*size);
    for (int i = 0; i < size; ++i) {//verifica se o no atual ja viu o no i
        c[i]=-1;
    }
    for(int i = 0; i<count_p;i++){//passa por todos os tier 1
        count_aux = 0;
        node=list_top[i]-1;
        arestas = graph[node];
        while (arestas!=NULL){
            aux=check_root(cycle,arestas->vertices-1);
            if(c[aux]!=node&&node!=aux){//verifica se ve todos os tier 1
                if(top_p[aux]){
                    count_aux++;
                    c[aux]=node;
                }
            }
            arestas=arestas->next;
        }
        if(count_aux!=count_p-1) {//se nao tiver visto a rede nao e conexa
            free(c);
            return false;
        }
    }
    free(c);
    return true;

}

bool c_connected(List** graph,int* top_p, int size,int* list_top,int count_p,int true_size,int* cycle){//verifica se a rede e conexa
    int aux;
    if(list_top[0]==0){//so para ter a certeza
        return full_check(graph,size,true_size);
    }
    if (!provider_network(graph,top_p,size,list_top,count_p,cycle)) return false;
    int start_node = list_top[0];//ha sempre um tier 1
    bool *discovered = (bool*)malloc(size*sizeof(bool));//ja foi descoberto

    // Inicializar os vetores
    for (int i = 0; i < size; i++) {
        discovered[i] = false;
    }
    //passa bfs
    Stack **FIFO = create_FIFO(create_element(start_node));
    Stack *auxS = NULL;
    List *arestas = NULL;
    int count = 1;
    discovered[start_node-1] = true;
    while (FIFO[0] != NULL){
        auxS = FIFO[0];
        arestas = graph[get_node(auxS)-1];
        while (arestas != NULL) {
            aux=check_root(cycle,arestas->vertices-1);//ve a raiz
            if(discovered[aux] == false && ((arestas->edges=='1')||(top_p[aux] && arestas->edges=='2'))){
                //verifica se ve a aresta e 1 ou 2 se for para um fornecedor
                    count++;
                    discovered[aux] = true;
                    FIFO = push_FIFO(FIFO, create_element(aux+1));
            }
            arestas = arestas->next;
        }
        if(count == true_size){//se vir todos
            erase_FIFO(FIFO);
            free(discovered);
            return true;
        }

        remove_FIFO(FIFO);
    }

    erase_FIFO(FIFO);
    free(discovered);
    return false;
}

bool full_check(List** graph,int size,int true_size){
    for(int i = 0; i<size;i++){
        if(graph[i]!=NULL) if(!BFS_C(graph,size,i+1,true_size)) return false;
    }
    return true;
}

bool g_connected(List** graph, int size, int true_size){
    // Função que verifica se o grafo é conexo

    int *parent = NULL;
    bool res = true; // true se for conexo
    int count = 1, aux = 0;

    // Ciclo for para detetar um primeiro vértice para começar a BFS
    for (int i = 0; i < size; ++i) {
        if(graph[i] != NULL) {
            aux = i+1;
            break;
        }
    }

    parent = BFS(graph, size, aux);

    // Verificar se a BFS chegou a todos os vértices
    for (int i = 0; i < size; ++i) {
        if(parent[i] != -1) {
            count++;
        }
    }

    if(count != true_size)
        res = false; // Se algum vértice não tiver sido alcançado, o grafo não é conexo

    free(parent);

    return res;
}