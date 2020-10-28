#ifndef _ISPs_H
#define _ISPs_H

#include "graph.h"

#include <stdio.h>

List** read_ISP(FILE *fp_preview,FILE *fp,int* max_node_value,int **top_f,int **list_top,int *count_f,int*);
FILE* open_ISP(FILE* file_pointer,int argc,char const *argv[]);
void close_ISP(FILE *file_pointer);

#endif  