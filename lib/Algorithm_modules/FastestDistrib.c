//
// Created by joped on 05/11/2020.
//

#include "FastestDistrib.h"
#include <stdlib.h>
#include <stdio.h>
int* BigBoyDijkstra(List** graph, int* cumulative, int node, int dest, int size)
{
    printf("\n");
    int vertice,cvalue;
    int** index=(int**)malloc(sizeof(int*)*3);
    int* result=(int*)malloc(sizeof(int)*size);
    Heap *Curr = NULL, **heap = (Heap**)malloc(sizeof(Heap*)*3);
    int* hsize = (int*)malloc(sizeof(int)*3),edgea,end=0;
    List *arestas = NULL;
    int* r=(int*)malloc(sizeof(int)*2);
    for (int i = 0; i < size; ++i) {
        result[i]=-1;
    }
    node--;
    dest--;
    for (int i = 0; i < 3; ++i) {

        heap[i] = createHeap(size);
        index[i]=(int*)malloc(sizeof(int)*size);
        for (int u = 0; u < size; ++u) {
            index[i][u] = -1;
        }
        hsize[i]=0;
        hsize[i]=insertHeap(heap[i], hsize[i], index[i], node,0);


    }
    Curr = createUnit();

    for (int i = 2; i>=0;i--) {

        while (!isEmpty(heap[i])) {
            hsize[i] = removeHeap(heap[i], Curr, hsize[i],
                                  index[i]); // remove o ponto mais prioritario do acervo e atualiza o current
            cvalue = get_hvalue(Curr, 0);
            node = get_hnode(Curr, 0);
            if ((result[node] != -1) && (cvalue) > result[node]) {
                continue;
            }
            index[i][node] = -2;
            if (result[node] == -1) {
                result[node] = cvalue;
                cumulative[cvalue]++;
            }
            if (node == dest) {
                r[0]=3-i;
                r[1]=result[dest];
                end=1;
                break;
            }
            arestas = graph[node];

            // Ciclo for que percorre os adjacentes do Current e, em caso válido, os insere no acervo
            while (arestas != NULL) {
                vertice = arestas->vertices - 1;
                edgea = arestas->edges - '0'-1;
                if (index[edgea][vertice] == -2) {
                    arestas = arestas->next;
                    continue;
                }
                if ((edgea < i || (edgea == i && i != 1))) {
                    cvalue = get_hvalue(Curr, 0);
                    if ((cvalue + 1) < result[vertice]) {
                        arestas = arestas->next;
                        continue;
                    } else if (index[edgea][vertice] == -1)
                        hsize[edgea] = insertHeap(heap[edgea], hsize[edgea], index[edgea], vertice, cvalue + 1);
                    else if ((get_hvalue(heap[edgea], vertice)) <= (cvalue + 1)) {
                        arestas = arestas->next;
                        continue;
                    } else
                        setValue(heap[edgea], vertice, cvalue + 1, index[edgea]);
                }
                arestas = arestas->next;
            }
        }
        if(end) break;
    }
    for (int i = 0; i < 3; ++i) {
        free(index[i]);
        eraseHeap(heap[i]);
    }
    free(hsize);
    free(index);
    free(heap);
    free(Curr);
    free(result);
    return r;
}