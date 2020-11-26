#include "PathLength.h"

/* Algoritmo implementado com LIFOs
int* lengths(List** graph, int max_node_value)
{
    Stack*** lifo = (Stack***) malloc(3*sizeof(Stack**));
    List* edges = NULL;
    int node = 0, vertice = 0, new_type = 0;
    bool* discovered = (bool*) malloc(max_node_value*sizeof(bool));
    int* length = (int*) malloc(max_node_value*sizeof(int));
    if((discovered == NULL) || (length == NULL))
        exit(EXIT_FAILURE);

    for (int i = 0; i < 3; ++i) {
        lifo[i] = (Stack**) malloc(max_node_value*sizeof(Stack*));
        if(lifo[i] == NULL)
            exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < max_node_value; ++j)
            lifo[i][j] = NULL;

    for (int i = 0; i < max_node_value; i++)
        length[i] = 0;

    for (int i = 0; i < max_node_value; i++) {
        if (graph[i] != NULL) {

            // Inicializar valores
            for (int j = 0; j < max_node_value; j++)
                discovered[j] = false;

            lifo[2][0] = push_LIFO(lifo[2][0], create_element(i));
            for (int j = 2; j >= 0 ; j--) {
                for (int k = 0; k < max_node_value; ++k) {
                    while (lifo[j][k] != NULL) {
                        // Remover um nó da fila
                        node = remove_LIFO(&lifo[j][k]);
                        // Verificar se o nó já foi retirado
                        if(discovered[node] == true)
                            continue;
                        discovered[node] = true; // Assinalar que o nó foi retirado
                        if(node != i)
                            length[k]++; // Somar a distância obtida no vetor final

                        edges = graph[node];
                        while (edges != NULL) {
                            // Registar os dados da aresta
                            vertice = edges->vertices - 1;
                            new_type = edges->edges - '0' - 1;

                            // Verificar se o caminho é válido e se o vértice já saiu da fila
                            if((new_type < j || new_type == j && j != 1) && (discovered[vertice] == false))
                                lifo[new_type][k+1] = push_LIFO(lifo[new_type][k+1], create_element(vertice));

                            edges = edges->next;
                        }
                    }
                }
            }
        }
    }

    free(discovered);

    return length;
}
*/

// Algoritmo implementado com uma Heap
int* lengths(List** graph, int max_node_value)
{
    Heap* heap = createHeap(max_node_value);
    int* index = (int*) malloc(max_node_value*sizeof(int));
    int* length = (int*) malloc(max_node_value*sizeof(int));
    if((index == NULL) || (length == NULL))
        exit(EXIT_FAILURE);

    int h_size = 0, value = 0, node = 0, type = 0, new_type = 0, l = 0, new_value = 0;
    List* edges = NULL;
    Heap* aux = createUnit();

    for (int i = 0; i < max_node_value; i++)
        length[i] = 0;

    int comparison_matrix[3][3] = {
            {1, 0, 0},
            {2, 0, 0},
            {3, 3, 3}
    };

    for (int i = 0; i < max_node_value; i++) {
        if(graph[i] != NULL) {
            // Inicializar valores
            for (int j = 0; j < max_node_value; j++)
                index[j] = -1;

            // Run Dijkstra
            h_size = insertHeap(heap, h_size, index, i, 0);
            while (!isEmpty(heap)) {
                h_size = removeHeap(heap, aux, h_size, index);
                value = get_hvalue(aux, 0);
                type = value>>16;
                l = value%(1<<16);
                length[l]++;

                node = get_hnode(aux, 0);
                index[node] = -2;

                edges = graph[node];

                while (edges != NULL) {
                    if (type == 0)
                        new_type = '4' - edges->edges;
                    else
                        new_type = comparison_matrix['4' - edges->edges-1][type - 1];

                    new_value = (new_type << 16) + l + 1;
                    if((new_type != 0) && (index[edges->vertices - 1] != -2)) {
                        if (index[edges->vertices - 1] == -1) {
                            h_size = insertHeap(heap, h_size, index, edges->vertices - 1, new_value);
                        } else if(get_hvalue(heap, index[edges->vertices-1]) > new_value) {
                            setValue(heap, index[edges->vertices - 1], new_value, index);
                        }
                    }
                    edges = edges->next;
                }
            }
        }
    }

    free(aux);
    free(index);
    heap = eraseHeap(heap);

    return length;
}

int single_length(List** graph, int max_node_value, int dest, int source)
{
    int result = 0;
    Heap* heap = createHeap(max_node_value);
    int* index = (int*) malloc(max_node_value*sizeof(int));
    if(index == NULL)
        exit(EXIT_FAILURE);

    int h_size = 0, value = 0, node = 0, type = 0, new_type = 0, l = 0, new_value = 0;
    List* edges = NULL;
    Heap* aux = createUnit();

    int comparison_matrix[3][3] = {
            {1, 0, 0},
            {2, 0, 0},
            {3, 3, 3}
    };

    // Inicializar index
    for (int j = 0; j < max_node_value; j++)
        index[j] = -1;

    // Run Dijkstra
    h_size = insertHeap(heap, h_size, index, dest-1, 0);
    while (!isEmpty(heap)) {
        h_size = removeHeap(heap, aux, h_size, index);
        value = get_hvalue(aux, 0);
        type = value>>16;
        l = value%(1<<16);

        node = get_hnode(aux, 0);
        index[node] = -2;

        if(node == source-1)
            break;

        edges = graph[node];
        while (edges != NULL) {
            if (type == 0)
                new_type = '4' - edges->edges;
            else
                new_type = comparison_matrix['4' - edges->edges-1][type - 1];

            new_value = (new_type << 16) + l + 1;
            if((new_type != 0) && (index[edges->vertices - 1] != -2)) {
                if (index[edges->vertices - 1] == -1)
                    h_size = insertHeap(heap, h_size, index, edges->vertices - 1, new_value);
                else if(get_hvalue(heap, index[edges->vertices-1]) > new_value)
                    setValue(heap, index[edges->vertices - 1], new_value, index);
            }
            edges = edges->next;
        }
    }

    free(aux);
    free(index);
    heap = eraseHeap(heap);

    return result;
}
