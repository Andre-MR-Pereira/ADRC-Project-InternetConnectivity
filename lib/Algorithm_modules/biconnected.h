#ifndef _BICONNECTED_H
#define _BICONNECTED_H

#include <stdbool.h>

#include "../Graph_module/Stacks.h"
#include "../Graph_module/graph.h"

void link_biconnected(List**,int);
int articulation_bridge(List** ,int* ,bool* ,int* ,int* ,int,int*);

#endif