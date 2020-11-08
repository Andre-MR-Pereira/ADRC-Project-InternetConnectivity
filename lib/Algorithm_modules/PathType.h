#ifndef _PATHTYPE_H
#define _PATHTYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Graph_module/graph.h"
#include "../Graph_module/Heap.h"

char path_type(List**,int,int,int);
int BGP_dijkstra(List**,int,int,bool*,int*,Heap*,int*,int*);

#endif