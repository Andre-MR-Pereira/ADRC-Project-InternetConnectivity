#ifndef _MENUS_H
#define _MENUS_H

#include "lib/Graph_module/graph.h"
#include "lib/Graph_module/Stacks.h"
#include "lib/Graph_module/ISPs.h"
#include "lib/Algorithm_modules/Search.h"
#include "lib/Algorithm_modules/Connected.h"
#include "lib/Algorithm_modules/biconnected.h"
#include "lib/Algorithm_modules/FindCycles.h"
#include "lib/Algorithm_modules/PathType.h"
#include "lib/Algorithm_modules/PathLength.h"
#include "lib/Algorithm_modules/printFile.h"
#include "lib/Algorithm_modules/FastestDistrib.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void showInitMenu (List**,int*, int,int*,int,int);

#endif