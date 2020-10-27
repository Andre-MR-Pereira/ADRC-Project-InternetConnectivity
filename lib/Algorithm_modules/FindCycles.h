//
// Created by joped on 25/10/2020.
//

#ifndef ADRC_PROJECT_INTERNETCONNECTIVITY_FINDCYCLES_H
#define ADRC_PROJECT_INTERNETCONNECTIVITY_FINDCYCLES_H
#include "../Graph_module/graph.h"
#include "../Graph_module/Stacks.h"
#include "../Algorithm_modules/Connected.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int DFS_Cycles(List**,int,int*,bool*, int*,int*,int*,int*,bool*);
int* check_cycle(List**,int,bool*);
int connect_cycle(int*,int*,int,int);
int check_root(int*,int);
List* insertList(List*,int *,int,int*,List*);
bool cycle_graph(List**,int,int*,int*,int,int);


#endif //ADRC_PROJECT_INTERNETCONNECTIVITY_FINDCYCLES_H
