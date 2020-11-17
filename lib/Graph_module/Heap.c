#include "Heap.h"
#include <stdlib.h>
#include <stdio.h>

struct _Heap {
    int node;
    int value;
};

Heap* createHeap(int n){
    Heap* heap=(Heap*)malloc(sizeof(Heap)*n);
    for (int i = 0; i < n; ++i) {
        heap[i].value= -1;
    }
    return heap;
}
int get_hnode (Heap *heap, int index)
{
    return heap[index].node;
}
int get_hvalue (Heap *heap, int index)
{
    return heap[index].value;
}

void FixUp(Heap* heap,int n,int* index){
    Heap trade;
    int new;
    while (n!=0 && heap[n].value<heap[(n-1)/2].value){
        new = (n-1)/2;
        index[heap[n].node]=new;
        index[heap[new].node]=n;
        trade=heap[new];
        heap[new]=heap[n];
        heap[n]=trade;
        n=(n-1)/2;
    }
}

void Fixdown(Heap* heap,int i, int n,int* index)
{
    Heap trade;
    int aux;
    while((2*i) < (n-1)){
        aux = 2*i + 1;
        if((aux < (n-1)) && (heap[aux].value > heap[aux+1].value))
            aux++;
        if(heap[i].value < heap[aux].value)
            break;
        index[heap[i].node]=aux;
        index[heap[aux].node]=i;
        trade = heap[aux];
        heap[aux] = heap[i];
        heap[i] = trade;
        i = aux;
    }
}

void setValue(Heap *heap, int n, int value, int* index)
{
    heap[n].value = value;
    FixUp(heap, n, index);
}

int insertHeap(Heap* heap,int max,int* index,int new,int value){
    heap[max].node=new;
    heap[max].value=value;
    index[new]=max;
    FixUp(heap,max,index);
    max++;
    return max;
}

Heap* createUnit()
{
    Heap *h= (Heap *) malloc(sizeof(Heap));
    h->node = -1;
    h->value = -1;

    return h;
}

int removeHeap(Heap *heap, Heap *removed, int max,int* index)
{
    Heap trade;

    max--;
    *removed = heap[0];
    heap[0].value = -1;
    trade = heap[0];
    heap[0] = heap[max];
    heap[max] = trade;

    Fixdown(heap, 0, max, index);

    return max;
}

void printHeap(Heap*heap,int n){
    for (int i = 0; i < n; ++i) {
        printf("%d:%i,%i\n",i,heap[i].node,heap[i].value);
    }
}

Heap* eraseHeap(Heap *heap)
{
    free(heap);

    return NULL;
}

int isEmpty(Heap *heap)
{
    if(heap[0].value == -1)
        return 1;
    else
        return 0;
}
