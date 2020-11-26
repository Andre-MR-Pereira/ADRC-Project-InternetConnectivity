#ifndef _PATHLENGTH_H
#define _PATHLENGTH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Graph_module/graph.h"
#include "../Graph_module/Heap.h"
#include "../Graph_module/Stacks.h"

int* lengths(List** , int);
int single_length(List**, int, int, int);

#endif
