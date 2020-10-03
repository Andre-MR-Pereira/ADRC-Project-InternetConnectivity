#ifndef _ISPs_H
#define _ISPs_H

#include "graph.h"

#include <stdio.h>

List** read_ISP(FILE *fp_preview,FILE *fp,int* max_node_value);
FILE* open_ISP(FILE* file_pointer);
void close_ISP(FILE *file_pointer);

#endif