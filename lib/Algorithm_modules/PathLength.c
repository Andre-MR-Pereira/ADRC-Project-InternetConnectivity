#include "PathLength.h"

int* lengths(List** graph, int max_node_value, int source, int destination, int* result)
{
    Heap* heap = createHeap(max_node_value);
    int* index = (int*) malloc(max_node_value*sizeof(int));
    int* length = (int*) malloc(max_node_value*sizeof(int));
    if((index == NULL) || (length == NULL))
        exit(EXIT_FAILURE);

    int h_size = 0, value = 0, node = 0, type = 0, new_type = 0, l = 0, new_value = 0;
    Heap* aux = createUnit();
    List* edges = NULL;
    bool flag = false;

    for (int i = 0; i < max_node_value; i++)
        length[i] = 0;

    int comparison_matrix[3][3] = {
            {1, 0, 0},
            {2, 0, 0},
            {3, 3, 3}
    };

    for (int i = 0; i < 100; i++) {
        if(graph[i] != NULL) {
            if(destination - 1 == i)
                flag = true;
            else
                flag = false;

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
                if((source - 1 == node) && (flag == true))
                    (*result) = l;
                index[node] = -2;

                edges = graph[node];
                while (edges != NULL) {
                    if (type == 0)
                        new_type = '4' - edges->edges;
                    else
                        new_type = 4 - comparison_matrix['4' - edges->edges-1][type - 1];

                    new_value = (new_type << 16) + l + 1;
                    if((new_type != 4) && (index[edges->vertices - 1] != -2)) {
                        if (index[edges->vertices - 1] == -1) {
                            h_size = insertHeap(heap, h_size, index, edges->vertices - 1, new_value);
                        } else if(get_hvalue(heap, index[edges->vertices-1]) > new_value)
                            setValue(heap, index[edges->vertices-1], new_value, index);
                    }

                    edges = edges->next;
                }
            }
        }
    }

    free(index);
    eraseHeap(heap);

    return length;
}
