#ifndef ADRC_PROJECT_INTERNETCONNECTIVITY_CONNECTED_H
#define ADRC_PROJECT_INTERNETCONNECTIVITY_CONNECTED_H
#include "../Graph_module/graph.h"
#include "../Graph_module/Stacks.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Search.h"

bool provider_network(List**,int*, int,int*,int);
bool c_connected(List**,int*, int,int*,int,int);
bool full_check(List** ,int ,int);
bool g_connected(List**, int, int);
#endif //ADRC_PROJECT_INTERNETCONNECTIVITY_CONNECTED_H
