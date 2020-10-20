#ifndef SEARCH_H
#define SEARCH_H

#include "../Graph_module/graph.h"
#include "../Graph_module/Stacks.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int* BFS(List** , int , int );
void DFS_Cycle(List** , int , bool* , bool* , bool*, int*);
void c_cycle(List** , int );
void print_cycle(bool* , int , int );

#endif //SEARCH_H
