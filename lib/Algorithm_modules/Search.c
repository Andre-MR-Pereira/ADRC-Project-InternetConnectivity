#include "Search.h"

int* BFS(List** graph, int size, int start_node){
    // Vetores auxiliares
    bool *discovered = (bool*)malloc(size*sizeof(bool));
    int *parent = (int*)malloc(size*sizeof(int));

    // Inicializar os vetores
    for (int i = 0; i < size; i++) {
        discovered[i] = false;
        parent[i] = -1;
    }

    Stack **FIFO = create_FIFO(create_element(start_node));
    Stack *auxS = NULL;
    List *arestas = NULL;
    int count = 1;
    discovered[start_node-1] = true;
    while (FIFO[0] != NULL){
        auxS = FIFO[0];
        arestas = graph[get_node(auxS)-1];
        while (arestas != NULL) {
            if(discovered[arestas->vertices-1] == false){
                count++;
                discovered[arestas->vertices-1] = true;
                parent[arestas->vertices-1] = get_node(auxS);
                FIFO = push_FIFO(FIFO, create_element(arestas->vertices));
            }
            arestas = arestas->next;
        }
        if(count == size) break; //duvidoso
        remove_FIFO(FIFO);
    }

    erase_FIFO(FIFO);
    free(discovered);

    return parent;
}

void DFS_Cycle(List** graph, int node, bool* discovered, bool* finished, bool* cycle, int* flag){
    // Recursive DFS to find cycles -- Needs a start function
    bool aux = false;

    discovered[node - 1] = true; // Node was discovered

    List *a = graph[node - 1]; // pointer to navigate the edges

    while ((a != NULL) && ((*flag) == -1)) {

        if (a->edges != '1') { // check the type of connection
            a = a->next; // navigate to next edge
            continue;
        }

        if (discovered[a->vertices - 1] == false) {
            DFS_Cycle(graph, a->vertices, discovered, finished, cycle, flag);
        } else if (finished[a->vertices - 1] == false) {
            (*flag) = 0; // Found a cycle!!
            aux = true;
            cycle[node - 1] = true;
            cycle[a->vertices - 1] = true;
        }

        a = a->next; // navigate to next edge
    }

    finished[node - 1] = true; // Node is finished

    if (((*flag) == 0) && (aux == false)) { // Check if cycle already closed
        if (cycle[node - 1] == true)
            (*flag) = 1; // Cycle closed
        else
            cycle[node - 1] = true; // Cycle not closed
    }
}

void c_cycle(List** graph, int size) {

    // Creating auxiliar variables
    int flag = -1;
    bool* discovered = (bool*)malloc(size*sizeof(bool));
    bool* finished = (bool*)malloc(size*sizeof(bool));
    bool* cycle = (bool*)malloc(size*sizeof(bool));
    if ((discovered == NULL) || (finished == NULL) || (cycle == NULL))
        EXIT_FAILURE;

    // Initializing at default values
    for (int i = 0; i < size; i++) {
        discovered[i] = false;
        finished[i] = false;
        cycle[i] = false;
    }

    // Global DFS - because it isn't known if the graph is connected
    for (int i = 0; i < size; ++i) {
        if(((flag) == -1) && (graph[i] != NULL) && (discovered[i] == false)) {
            DFS_Cycle(graph, i+1, discovered, finished, cycle, &flag);
        }
    }

    // Print response
    print_cycle(cycle, flag, size);

    // Free allocated memory
    free(discovered);
    free(finished);
    free(cycle);

}

void print_cycle(bool* cycle, int flag, int size) {

    // Check if a cycle was found
    if(flag == -1)
        printf("The input internet is commercially acyclic.\n");
    else {
        printf("The input internet has a provider-customer cycle through nodes: ");
        for (int i = 0; i < size; ++i) {
            if(cycle[i] == true)
                printf("%d ", i+1);
        }
    }
}
