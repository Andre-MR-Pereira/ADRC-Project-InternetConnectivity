#ifndef _PATHTYPE_H
#define _PATHTYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Graph_module/graph.h"
#include "../Graph_module/Heap.h"

void path_type(List**,int,int,int**,int*);
void BGP_dijkstra(List**,int,Heap*,int*,int**,int*,int*);

#endif