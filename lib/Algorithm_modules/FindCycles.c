//
// Created by joped on 25/10/2020.
//

#include "FindCycles.h"

int DFS_Cycles(List** graph, int node, int* discovered, bool* finished, int* cycle,int* cycle_ids,int* count_d,bool* has_cycle,Stack** Stack){
    // Recursive DFS to find cycles -- Needs a start function
    bool aux = false;
    int au =0;
    (*count_d)++;
    discovered[node - 1] = (*count_d); // coloca quando foi descoberto
    *Stack=push_LIFO(*Stack,create_element(node - 1));
    List *a = graph[node - 1]; //

    while ((a != NULL)) {

        if (a->edges != '1') { // check the type of connection vai passar so por arestas 1
            a = a->next; // navigate to next edge
            continue;
        }

        if (discovered[a->vertices - 1] == false) {
            au=DFS_Cycles(graph, a->vertices, discovered, finished, cycle,cycle_ids,count_d,has_cycle,Stack);
            if(discovered[au]<discovered[cycle_ids[node-1]]) cycle_ids[node-1]=au; //se tiver visto um mais antigo e o novo ciclo deste no
        } else if (finished[cycle_ids[a->vertices - 1]] == false) {// se vir um no descoberto mas q nao acabou
            has_cycle[node-1]=true;//o no atual e o fim o que viu fazem parte do ciclo
            has_cycle[a->vertices - 1]=true;
            if (discovered[a->vertices - 1]<discovered[cycle_ids[node-1]]) cycle_ids[node-1] = a->vertices - 1; //se tiver visto um mais antigo e o novo ciclo deste no
            aux = true;
        }

        a = a->next;
    }

    finished[node - 1] = true; // Node is finished
    if(aux==false){
        if (cycle_ids[node-1]!=node-1) {
            has_cycle[node-1]=true;
        }
        else{//se o mais antigo for ele mesmo mas fizer parte de um ciclo e o fim da zona
            au=remove_LIFO(Stack);
            while(au!=cycle[node-1]){//coloca toda a zona com a mesma raiz
                cycle[au]=node-1;
                au=remove_LIFO(Stack);
            }
        }
    }

    return cycle_ids[node-1];//retorna o no mais antigo que viu
}

int* check_cycle(List** graph, int size,bool* has_cycle) {

    // Creating auxiliar variables
    int* discovered = (int*)malloc(size*sizeof(int));//quando foi descoberto
    bool* finished = (bool*)malloc(size*sizeof(bool));//ja acabou
    int* cycle = (int*)malloc(size*sizeof(int));//valores finais de ciclo
    int* cycle_ids = (int*)malloc(size*sizeof(int));//valores medios de ciclo
    if ((discovered == NULL) || (finished == NULL) || (cycle == NULL))
        EXIT_FAILURE;
    int count_d=0;//conta quando e foi descoberto
    Stack* Stack=NULL;
    // inicializa variaveis
    for (int i = 0; i < size; i++) {
        discovered[i] = 0;
        finished[i] = false;
        cycle[i] = i;
        cycle_ids[i] = i;
    }



    // Global DFS
    for (int i = 0; i < size; ++i) {
        if((graph[i] != NULL) && (discovered[i] == false)) {
            DFS_Cycles(graph, i+1, discovered, finished, cycle,cycle_ids,&count_d,has_cycle,&Stack);
        }
    }

    free(discovered);
    free(finished);
    free(cycle_ids);
    return cycle;

}

int check_root(int* id,int p){
    return id[p];//verifica a raiz da zona fortemente conexa
}



List* insertList(List* edges,int *p_forn,int curr,int* cycle,List* insert){//copia as arestas para outra posição
    List *aux=insert;
    List * new_node=NULL;
    while(edges!=NULL){
        if(check_root(cycle,edges->vertices-1)!=curr){//se a aresta nao for para dentro do proprio ciclo vai copiar
            new_node=(List*)malloc(sizeof(struct Node));
            new_node->vertices=edges->vertices;
            new_node->edges=edges->edges;
            aux=insertHeadList(aux,new_node);
            if(edges->edges=='3')(*p_forn=0);//Nao e fornecedor

        }
        edges=edges->next;
    }
    return aux;
}

bool cycle_graph(List** graph, int size,int* top_f,int*list_top,int count_f,int true_size){//cria super nos e verfica conectividade
    List** c_graph=create_graph(size);//grafo copia
    Stack* LIFO=NULL;
    List* aux2,*next;
    bool connected;// e connexa
    bool* has_cycle=(bool*)malloc(sizeof(bool)*size);
    int aux;
    int p_forn =0;

    int* check = (int*)malloc(sizeof(int)*size);//verifica se já foi considerado não fornecedor
    for (int i=0;i<size;i++){
        check[i]=0;
        has_cycle[i]=false;
    }
    int* cycle=check_cycle(graph,size,has_cycle);


    for (int i=0;i<size;i++) {
        p_forn =1;  //pode ser forncedor
        if (has_cycle[i]) {
            aux = check_root(cycle, i);//vai buscar a raiz
            c_graph[aux] = insertList(graph[i], &p_forn,aux,cycle,c_graph[aux]);//copia as arestas
            if(aux!=i) true_size--;//o elemento faz parte dum super no o numero de nos diminui
            if (p_forn && check[aux] == 0) {//a raiz pode ser forncedora
                check[aux] = 1;//ja sabe qual e a raiz
                LIFO = push_LIFO(LIFO, create_element(aux));
            } else if (!p_forn) check[aux] = -1;//nao e forncedor

        } else c_graph[i] = graph[i];//se nao for loop apenas aponta pro mesmo sitio
    }

    while(LIFO!=NULL){
        aux=remove_LIFO(&LIFO);
        if(check[aux]==1){//se o super no for fornecedor
            top_f[aux]=1;
            list_top[count_f]=aux+1;
            count_f++;
        }
    }

    connected=c_connected(c_graph,top_f,size,list_top,count_f,true_size,cycle);//verifica conectividade

    for (int i = 0; i < size; ++i) {
        if(c_graph[i]!=graph[i]) {//se for uma copia
            for (aux2 = c_graph[i]; aux2 != NULL; aux2 = next) {
                next = aux2->next;
                free(aux2);
            }
        }
    }

    free(cycle);
    free(c_graph);
    free(has_cycle);
    free(check);


    return connected;
}