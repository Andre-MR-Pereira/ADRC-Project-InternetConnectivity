#include "PathLength.h"

int* lengths(List** ISP_graph, int max_node_value, int source, int destination, int* result)
{
    Heap* queue;

    bool* discovered = (bool*) malloc(max_node_value*sizeof(bool));
    int* parent = (int*) malloc(max_node_value*sizeof(int));
    int* path = (int*) malloc(max_node_value*sizeof(int));
    int* index = (int*) malloc(max_node_value*sizeof(int));
    int* length = (int*) malloc(max_node_value*sizeof(int));
    if((discovered == NULL) || (parent == NULL) || (path == NULL) || (index == NULL) || (length == NULL))
        exit(EXIT_FAILURE);

    // Inicializar valores
    queue = createHeap(max_node_value);
    for (int i = 0; i < max_node_value; i++) {
        parent[i] = -1;
        discovered[i] = false;
        index[i] = -1;
        path[i] = -1;
    }

}
