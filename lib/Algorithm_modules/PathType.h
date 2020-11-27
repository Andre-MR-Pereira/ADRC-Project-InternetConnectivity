#ifndef _PATHTYPE_H
#define _PATHTYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Graph_module/graph.h"
#include "../Graph_module/Heap.h"
#include "../Graph_module/Stacks.h"

int path_type(List**,int,int,int*,int,int);
int BGP_dijkstra_connected(List**,int,int,int*,int*,Stack*,Stack*);
int BGP_dijkstra_not_connected(List**,int,int,int*,int*,Stack*,Stack*);

#endif