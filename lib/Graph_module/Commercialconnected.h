
#ifndef ADRC_PROJECT_INTERNETCONNECTIVITY_COMMERCIALCONNECTED_H
#define ADRC_PROJECT_INTERNETCONNECTIVITY_COMMERCIALCONNECTED_H
#include "graph.h"
#include "Stacks.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Search.h"

bool provider_network(List**,int*, int,int*,int);
bool c_connected(List**,int*, int,int*,int,int);
bool g_connected(List**, int, int*, int);
#endif //ADRC_PROJECT_INTERNETCONNECTIVITY_COMMERCIALCONNECTED_H
