//
// Created by joped on 05/11/2020.
//

#include "FastestDistrib.h"
#include <stdlib.h>
#include <stdio.h>
int* BigBoyDijkstra(List** graph, int* cumulative,int* r, int node, int dest, int size)
{
    int vertice,cvalue;
    int** index=(int**)malloc(sizeof(int*)*3);
    int* result=(int*)malloc(sizeof(int)*size);
    Heap *Curr = NULL, **heap = (Heap**)malloc(sizeof(Heap*)*3);
    int* hsize = (int*)malloc(sizeof(int)*3),edgea,end=0;
    List *arestas = NULL;
    for (int i = 0; i < size; ++i) {
        result[i]=-1;
    }
    node--;
    dest--;
    if(node!=-1) {
        r = (int*)malloc(sizeof(int)*size);
        r[0]=-1;
        r[1]=-1;
    }
    for (int i = 0; i < 3; ++i) {

        heap[i] = createHeap(size);//3 heaps um para cada tipo
        index[i]=(int*)malloc(sizeof(int)*size);//guarda o index em cada uma das heaps
        for (int u = 0; u < size; ++u) {
            index[i][u] = -1;
        }
        hsize[i]=0;
        hsize[i]=insertHeap(heap[i], hsize[i], index[i], node,0);


    }
    Curr = createUnit();//recebe o q foi removido

    for (int i = 2; i>=0;i--) {//corre 3 dijktras um para cada tipo

        while (!isEmpty(heap[i])) {
            hsize[i] = removeHeap(heap[i], Curr, hsize[i],
                                  index[i]); // remove o ponto mais prioritario do acervo e atualiza o current
            cvalue = get_hvalue(Curr, 0);
            node = get_hnode(Curr, 0);
            index[i][node] = -2;
            if ((result[node] != -1) && (cvalue) > result[node]) {// se for buscar um no q ja saiu doutra fila com custo mais baixo nao o vai usar
                continue;
            }

            if (result[node] == -1) {//se ainda nao acabou
                result[node] = cvalue;
                cumulative[cvalue]++;
            }
            if (node == dest) {//se e o destino
                r[0]=3-i;
                r[1]=result[dest];
                end=1;
                break;
            }
            arestas = graph[node];
            // Ciclo for que percorre os adjacentes do Current e, em caso válido, os insere no acervo
            while (arestas != NULL) {
                vertice = arestas->vertices - 1;//no destino da aresta
                edgea = arestas->edges - '0'-1;//tipo da aresta

                if (index[edgea][vertice] == -2) {//se o no ja saiu da fila
                    arestas = arestas->next;
                    continue;
                }
                if ((edgea < i || (edgea == i && i != 1))) {//se o caminho e valido
                    cvalue = get_hvalue(Curr, 0);
                    if ((cvalue + 1) > result[vertice] && result[vertice]!=-1) {//se o q vai ser colucado e pior q o resultado desse no
                        arestas = arestas->next;
                        continue;
                    }
                    if (index[edgea][vertice] == -1)// se o no nunca esteve na heap insere
                        hsize[edgea] = insertHeap(heap[edgea], hsize[edgea], index[edgea], vertice, cvalue + 1);
                    else if ((get_hvalue(heap[edgea], index[edgea][vertice])) <= (cvalue + 1)) {//se o caminho q encontra e pior
                        arestas = arestas->next;
                        continue;
                    } else {
                        setValue(heap[edgea], index[edgea][vertice], cvalue + 1, index[edgea]);//se o caminho q encontra e melhor muda a prioridade
                    }
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