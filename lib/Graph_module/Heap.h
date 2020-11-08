//
// Created by joped on 05/11/2020.
//

#ifndef ADRC_PROJECT_INTERNETCONNECTIVITY_HEAP_H
#define ADRC_PROJECT_INTERNETCONNECTIVITY_HEAP_H
typedef struct _Heap Heap;
Heap* createHeap(int n);
int get_hnode (Heap *heap, int index);
int get_hvalue (Heap *heap, int index);
void FixUp(Heap* heap,int n,int* index);
void Fixdown(Heap* heap,int i, int n,int* index);
int insertHeap(Heap* heap,int max,int* index,int new,int value);
int removeHeap(Heap *heap, Heap *removed, int max,int* index);
void printHeap(Heap*heap,int n);
Heap* createUnit();
void setValue(Heap *heap, int n, int value, int* index);
Heap* eraseHeap(Heap *heap);
int isEmpty(Heap *heap);
#endif //ADRC_PROJECT_INTERNETCONNECTIVITY_HEAP_H
