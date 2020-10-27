//
// Created by joped on 25/10/2020.
//

#include "FindCycles.h"

int DFS_Cycles(List** graph, int node, int* discovered, bool* finished, int* cycle,int* sizec,int* cycle_ids,int* count_d,bool* has_cycle){
    // Recursive DFS to find cycles -- Needs a start function
    bool aux = false;
    int au =0;
    (*count_d)++;
    discovered[node - 1] = (*count_d); // Node was discovered

    List *a = graph[node - 1]; // pointer to navigate the edges

    while ((a != NULL)) {

        if (a->edges != '1') { // check the type of connection
            a = a->next; // navigate to next edge
            continue;
        }

        if (discovered[a->vertices - 1] == false) {
            au=DFS_Cycles(graph, a->vertices, discovered, finished, cycle,sizec,cycle_ids,count_d,has_cycle);
            if(discovered[au]<discovered[cycle_ids[node-1]]) cycle_ids[node-1]=au;
        } else if (finished[cycle_ids[a->vertices - 1]] == false) {
            connect_cycle(sizec,cycle,a->vertices - 1,node - 1);
            has_cycle[node-1]=true;
            has_cycle[a->vertices - 1]=true;
            if (discovered[a->vertices - 1]<discovered[cycle_ids[node-1]]) cycle_ids[node-1] = a->vertices - 1;
            aux = true;
        }

        a = a->next; // navigate to next edge
    }

    finished[node - 1] = true; // Node is finished

    if (cycle_ids[node-1]!=node-1&&aux==false) {
        connect_cycle(sizec,cycle,node - 1,cycle_ids[node-1]);
        has_cycle[node-1]=true;
        has_cycle[cycle_ids[node-1]]=true;
    }

    return cycle_ids[node-1];
}

int* check_cycle(List** graph, int size,bool* has_cycle) {

    // Creating auxiliar variables
    int* discovered = (int*)malloc(size*sizeof(int));
    bool* finished = (bool*)malloc(size*sizeof(bool));
    int* cycle = (int*)malloc(size*sizeof(int));
    int* sizec = (int*)malloc(size*sizeof(int));
    int* cycle_ids = (int*)malloc(size*sizeof(int));
    if ((discovered == NULL) || (finished == NULL) || (cycle == NULL))
        EXIT_FAILURE;
    int count_d=0;
    // Initializing at default values
    for (int i = 0; i < size; i++) {
        discovered[i] = 0;
        finished[i] = false;
        cycle[i] = i;
        sizec[i]=1;
        cycle_ids[i] = i;
    }



    // Global DFS - because it isn't known if the graph is connected
    for (int i = 0; i < size; ++i) {
        if((graph[i] != NULL) && (discovered[i] == false)) {
            DFS_Cycles(graph, i+1, discovered, finished, cycle,sizec,cycle_ids,&count_d,has_cycle);
        }
    }

    // Free allocated memory
    free(discovered);
    free(finished);
    free(sizec);
    free(cycle_ids);
    return cycle;

}
int connect_cycle(int* sz, int* id ,int p, int q){
    int i ,j,t,x;
    for (i = p; i != id[i]; i = id[i]);
    for (j = q; j != id[j]; j = id[j]);
    if (i == j) t = i;
    else if (sz[i] < sz[j]) {
        id[i] = j; sz[j] += sz[i]; t = j;
    } else {
        id[j] = i; sz[i] += sz[j]; t = i;
    }
    for (i = p; i != id[i]; i = x) {x = id[i]; id[i] = t;}
    for (j = q; j != id[j]; j = x) {x = id[j]; id[j] = t;}
    return 0;
}
int check_fix_root(int* id,int p){
    int i,x,t;
    for (i = p; i != id[i]; i = id[i]);
    t=i;
    for (i = p; i != id[i]; i = x) {x = id[i]; id[i] = t;}
    return i;
}
int check_root(int* id,int p){
    int i;
    for (i = p; i != id[i]; i = id[i]);
    return i;
}



List* insertList(List* edges,int *p_forn,int curr,int* cycle,List* insert){
    List *aux=insert;
    List * new_node=NULL;
    while(edges!=NULL){
        if(check_fix_root(cycle,edges->vertices-1)!=curr){
            new_node=(List*)malloc(sizeof(struct Node));
            new_node->vertices=edges->vertices;
            new_node->edges=edges->edges;
            aux=insertHeadList(aux,new_node);
        }
        edges=edges->next;
    }

    return aux;
}

bool cycle_graph(List** graph, int size,int* top_f,int*list_top,int count_f,int true_size){
    List** c_graph=create_graph(size);
    Stack* LIFO=NULL;
    List* aux2,*next;
    bool connected;
    bool* has_cycle=(bool*)malloc(sizeof(bool)*size);
    int aux;
    int p_forn =0;

    int* check = (int*)malloc(sizeof(int)*size);
    for (int i=0;i<size;i++){
        check[i]=0;
        has_cycle[i]=false;
    }
    int* cycle=check_cycle(graph,size,has_cycle);


    for (int i=0;i<size;i++) {
        p_forn =1;
        if (has_cycle[i]) {
            aux = check_fix_root(cycle, i);
            c_graph[aux] = insertList(graph[i], &p_forn,aux,cycle,c_graph[aux]);
            if(aux!=i) true_size--;
            if (p_forn && check[aux] == 0) {
                check[aux] = 1;
                LIFO = push_LIFO(LIFO, create_element(aux));
            } else if (!p_forn) check[aux] = -1;

        } else c_graph[i] = graph[i];
    }
    //print_graph(c_graph,size);
    while(LIFO!=NULL){
        aux=remove_LIFO(&LIFO);
        if(check[aux]==1){
            top_f[aux]=1;
            list_top[count_f]=aux+1;
            count_f++;
        }
    }

    connected=c_connected(c_graph,top_f,size,list_top,count_f,true_size,cycle);

    for (int i = 0; i < size; ++i) {
        if(c_graph[i]!=graph[i]) {
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